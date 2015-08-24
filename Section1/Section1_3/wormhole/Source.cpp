/*
ID: gzl80421
PROG: wormhole
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
	ofstream fout;
	ifstream fin;
public:
	Solution() :fin("wormhole.in"), fout("wormhole.out"){}
private:
	struct WarmHole
	{
		int x;
		int y;
		WarmHole() : x(0), y(0){}
		WarmHole(int wx, int wy) : x(wx), y(wy){}
	};

	int N; //2 <= N <= 12
	vector<WarmHole> warm_holes;
#define MAX_N 12
	int pair_info[MAX_N];
	bool start_have_been[MAX_N];
	bool start_tested[MAX_N];
	struct HorizontalLink
	{
		HorizontalLink *next;
		int x_axis;
		int index;
		HorizontalLink(int x, int i) :next(NULL), x_axis(x), index(i){}
	};
	struct HorizontalLinkHeader
	{
		HorizontalLink *head;
		int y_axis;
		HorizontalLinkHeader *next;
		HorizontalLinkHeader(int y) : head(NULL), y_axis(y), next(NULL){}
	};
	HorizontalLinkHeader *head_of_link_headers;
	HorizontalLinkHeader *tail_of_link_header;
	HorizontalLink *horizontal_info[MAX_N];

	void Input()
	{
		head_of_link_headers = tail_of_link_header = NULL;
		num_of_stuck_pairs = 0;
		fin >> N;
		for (int i = 0; i < N; i++)
		{
			int x, y;
			fin >> x >> y;
			AddWarmHole(x, y, i);
		}
	}

	void AddWarmHole(int x, int y, int index)
	{
		WarmHole wh(x, y);
		warm_holes.push_back(wh);
		InsertToHorizontalInfo(wh, index);
	}

	void InsertToHorizontalInfo(WarmHole wh, int index)
	{
		horizontal_info[index] = new HorizontalLink(wh.x, index);
		// find first header equal to wh.y
		HorizontalLinkHeader *p = head_of_link_headers;
		while (p != NULL && p->y_axis != wh.y)
		{
			p = p->next;
		}
		// add new header
		if (p == NULL)
		{
			HorizontalLinkHeader *lh = new HorizontalLinkHeader(wh.y);
			AppendToLastHeader(lh);
			p = lh;
		}
		// p = the header to insert
		InsertToHorizontalLink(p, horizontal_info[index]);
	}

	void AppendToLastHeader(HorizontalLinkHeader *lh)
	{
		// if none in link
		if (head_of_link_headers == NULL && tail_of_link_header == NULL)
		{
			head_of_link_headers = lh;
			tail_of_link_header = lh;
		}
		else
		{
			tail_of_link_header->next = lh;
			tail_of_link_header = lh;
		}
	}

	void InsertToHorizontalLink(HorizontalLinkHeader *header, HorizontalLink *obj)
	{
		HorizontalLink *p = header->head;
		HorizontalLink *prev = NULL;
		// find first p->x_axis > obj_x_axis
		while (p != NULL && p->x_axis <= obj->x_axis)
		{
			prev = p;
			p = p->next;
		}

		// none in the link
		if (p == NULL && prev == NULL)
		{
			header->head = obj;
		}
		// didn't find p, append to last
		else if (p == NULL)
		{
			prev->next = obj;
		}
		// insert to the head
		else if (prev == NULL)
		{
			obj->next = header->head;
			header->head = obj;
		}
		// normal situation, insert between prev and p
		else 
		{
			prev->next = obj;
			obj->next = p;
		}
	}

#define UNCHOSEN -1
#define UNABLE_TO_FIND -1
	int FindFirstUnchosenWarmHole()
	{
		for (int i = 0; i < N; i++)
		{
			if (pair_info[i] == UNCHOSEN)
				return i;
		}
		return UNABLE_TO_FIND;
	}

	void SetAsPair(int first, int second)
	{
		pair_info[first] = second;
		pair_info[second] = first;
	}

	void ResetPair(int first, int second)
	{
		pair_info[first] = UNCHOSEN;
		pair_info[second] = UNCHOSEN;
	}
	void IterateChooseOnePair()
	{
		int first = FindFirstUnchosenWarmHole();
		// unable to find
		if (first == UNABLE_TO_FIND)
		{
			TestStuckPairs();
			return;
		}
		int second = first + 1;
		for (; second < N; second++)
		{
			if (pair_info[second] == UNCHOSEN)
			{
				SetAsPair(first, second);
				IterateChooseOnePair();
				ResetPair(first, second);
			}
		}
	}

	void SetPairInfoAndTestPair()
	{
		for (int i = 0; i < N; i++)
		{
			pair_info[i] = UNCHOSEN;
		}
		IterateChooseOnePair();
	}

	int num_of_stuck_pairs;
	void TestStuckPairs()
	{
		for (int i = 0; i < N; i++)
		{
			start_tested[i] = false;
		}
		for (int i = 0; i < N; i++)
		{
			// have tested before
			if (start_tested[i])
				continue;
			start_tested[i] = true;
			if (TestStuckStartFrom(i))
			{
				num_of_stuck_pairs++;
				return;
			}
		}
	}

	bool TestStuckStartFrom(int index)
	{
		for (int i = 0; i < N; i++)
		{
			start_have_been[i] = false;
		}
		start_have_been[index] = true;
		int cur_pos = index;
		int next_pos;
		while (true)
		{
			// begin from left of current position
			// pass current position
			start_have_been[cur_pos] = true;
			start_tested[cur_pos] = true;
			// to the right of paired position
			cur_pos = pair_info[cur_pos];

			next_pos = FindFirstRightWarmHole(cur_pos);
			// unable to find
			if (next_pos == UNABLE_TO_FIND)
			{
				return false;
			}
			// have been before
			else if (start_have_been[next_pos])
			{
				return true;
			}
			else
			{
				// now left of next_pos
				cur_pos = next_pos;				
			}
		}
	}

	int FindFirstRightWarmHole(int index)
	{
		HorizontalLink *p = horizontal_info[index]->next;
		if (p == NULL)
		{
			return UNABLE_TO_FIND;
		}
		else
		{
			return p->index;
		}
	}

public:
	void run()
	{
		Input();
		SetPairInfoAndTestPair();
		fout << num_of_stuck_pairs << endl;
	}
};

int main()
{
	Solution s;
	s.run();
	return 0;
}

