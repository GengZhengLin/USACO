/*
ID: gzl80421
PROG: barn1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
	ofstream fout;
	ifstream fin;
public:
	Solution() :fin("barn1.in"), fout("barn1.out"){}
private:
	struct Interval
	{
		int index;
		int stalls;
		Interval *next;
		Interval *prev;

		Interval(int i, int s) :index(i), stalls(s), next(NULL), prev(NULL){}
	};

	Interval *head;
	Interval *tail;

	int M; // M (1 <= M <= 50), the maximum number of boards that can be purchased
	int S; // S (1 <= S <= 200), the total number of stalls
	int C; // C (1 <= C <= S) the number of cows in the stalls

	int min_stall;
	int max_stall;
	int num_of_intervals;

	vector<int> cow_stalls;
	void Input()
	{
		head = tail = NULL;
		min_stall = max_stall = 0;
		num_of_intervals = 0;
		cow_stalls.clear();
		fin >> M >> S >> C;
		for (int i = 0; i < C; i++)
		{
			int temp; fin >> temp;
			cow_stalls.push_back(temp);
		}

		sort(cow_stalls.begin(), cow_stalls.end());
		min_stall = cow_stalls[0];
		max_stall = cow_stalls[C - 1];
	}

	void InsertInterval(int index, int stalls)
	{
		Interval *obj = new Interval(index, stalls);
		InsertToList(obj);
		RemoveExtra();
	}

	void InsertToHead(Interval *obj)
	{
		obj->next = head;
		obj->prev = NULL;
		if (head != NULL)
			head->prev = obj;
		head = obj;
	}

	void InsertToTail(Interval *obj)
	{
		obj->prev = tail;
		obj->next = NULL;
		if (tail != NULL)
			tail->next = obj;
		tail = obj;
	}

	void InsertBetween(Interval *obj, Interval *p1, Interval *p2)
	{
		if (p1 != NULL && p2 != NULL)
		{
			p1->next = obj;
			obj->prev = p1;
			p2->prev = obj;
			obj->next = p2;
		}
		else
		{
			if (p1 == NULL) InsertToHead(obj);
			if (p2 == NULL) InsertToTail(obj);
		}
	}

	void UpdateGlobalsInsert(Interval *obj)
	{
		num_of_intervals++;
	}

	void UpdateGlobalsRemove(Interval *obj)
	{
		num_of_intervals--;
	}

	void InsertToList(Interval *obj)
	{
		Interval *cur = head;
		Interval *prev = NULL;
		bool inserted = false;
		while (cur != NULL && cur->stalls >= obj->stalls)
		{
			prev = cur;
			cur = cur->next;
		}
		// cur = first cur->stall < obj->stall

		// first node
		if (cur == NULL && prev == NULL)
		{
			InsertToHead(obj);
			InsertToTail(obj);
			inserted = true;
		}

		// insert head
		if (cur != NULL && prev == NULL)
		{
			InsertToHead(obj);
			inserted = true;
		}

		// normal situation
		if (cur != NULL && prev != NULL)
		{
			InsertBetween(obj, prev, cur);
			inserted = true;
		}

		// last node
		if (cur == NULL && prev != NULL)
		{
			if (num_of_intervals < M-1)
			{
				InsertToTail(obj);
				inserted = true;
			}
		}

		if (inserted)
		{
			UpdateGlobalsInsert(obj);
		}
	}

	void RemoveLast()
	{
		if (tail == NULL) return;
		Interval *temp = tail;
		tail = tail->prev;
		if (tail == NULL) return;
		tail->next = NULL;
		delete temp;
	}

	void RemoveExtra()
	{
		while (num_of_intervals > M-1)
		{
			// remove last
			UpdateGlobalsRemove(tail);
			RemoveLast();
		}
	}

	int GetIntervalStallsSum()
	{
		Interval *p = head;
		int sum = 0;
		while (p != NULL)
		{
			sum += p->stalls;
			p = p->next;
		}
		return sum;
	}
public:
	void run()
	{
		Input();
		// cows < boards
		if (C <= M)
		{
			fout << C << endl;
			return;
		}
		if (M == 1)
		{
			fout << max_stall - min_stall + 1 << endl;
			return;
		}
		// else
		int n = cow_stalls.size();
		for (int i = 0; i < n-1; i++)
		{
			InsertInterval(i, cow_stalls[i + 1] - cow_stalls[i] - 1);
		}
		int boards = max_stall - min_stall + 1 - GetIntervalStallsSum();
		fout << boards << endl;
	}
};

int main()
{
	Solution s;
	s.run();
	return 0;
}

