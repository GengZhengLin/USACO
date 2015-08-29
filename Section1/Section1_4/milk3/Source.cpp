/*
ID: gzl80421
PROG: milk3
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

class Solution
{
	ofstream fout;
	ifstream fin;
public:
	Solution() :fin("milk3.in"), fout("milk3.out"){}
private:
	int milk_capacity[3];
	int milk_current[3];
#define A 0
#define B 1
#define C 2
	bool possible_CA[21][21];

	void Input()
	{
		for (int i = 0; i < 3; i++)
			fin >> milk_capacity[i];

		milk_current[A] = milk_current[B] = 0;
		milk_current[C] = milk_capacity[C];

		for (int i = 0; i <= 20; i++)
		{
			for (int j = 0; j <= 20; j++)
			{
				possible_CA[i][j] = false;
			}
		}
	}

	void PourFromTo(int from, int to)
	{
		int to_fill = milk_capacity[to] - milk_current[to];
		if (to_fill == 0) return;
		if (milk_current[from] < to_fill)
		{
			milk_current[to] += milk_current[from];
			milk_current[from] = 0;			
		}
		else
		{
			milk_current[from] -= to_fill;
			milk_current[to] = milk_capacity[to];
		}
	}

	void PushCurState()
	{
		possible_CA[milk_current[C]][milk_current[A]] = true;
	}

	bool IsEmpty(int index)
	{
		return milk_current[index] == 0;
	}

	void PourMilkIterateOneStep()
	{
		possible_CA[milk_current[C]][milk_current[A]] = true;
		for (int i = 0; i < 3; i++)
		{
			if (!IsEmpty(i))
			{
				for (int j = 1; j <= 2; j++)
				{
					int from = i;
					int to = (i + j) % 3;
					int cur_from = milk_current[from];
					int cur_to = milk_current[to];
					PourFromTo(from, to);
					if (!possible_CA[milk_current[C]][milk_current[A]])
					{
						PourMilkIterateOneStep();
					}
					milk_current[from] = cur_from;
					milk_current[to] = cur_to;
				}
			}
		}
	}

	void Output()
	{
		bool outputed = false;
		for (int i = 0; i <= 20; i++)
		{
			if (possible_CA[i][0])
			{
				if (outputed)
				{
					fout << " " << i;
				}
				else
				{
					fout << i; outputed = true;
				}			
			}
		}
		fout << endl;
	}


public:
	void run()
	{
		Input();
		PourMilkIterateOneStep();
		Output();
	}
};

int main()
{
	Solution s;
	s.run();
	return 0;
}

