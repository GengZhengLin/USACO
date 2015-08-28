/*
ID: gzl80421
PROG: ariprog
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
	Solution() :fin("ariprog.in"), fout("ariprog.out"){}
private:
	int N;
	int M;
	bool *is_bisquares;
	vector<int> bisquares;
	void Input()
	{
		fin >> N >> M;
	}

	void GenerateBisquares()
	{
		int n = M * M * 2;
		is_bisquares = new bool[n];
		for (int i = 0; i < n; i++)
			is_bisquares[i] = false;
		for (int p = 0; p <= M; p++)
		{
			for (int q = 0; q <= M; q++)
			{
				int temp = p * p + q * q;
				is_bisquares[temp] = true;
			}
		}

		int length = M * M * 2;
		for (int i = 0; i < length; i++)
		{
			if (is_bisquares[i])
				bisquares.push_back(i);
		}
	}

	bool TestAriProgFromStartWithStep(int start, int step)
	{
		int max_bisquare = M * M * 2;
		for (int i = 0, cur = start; i < N; i++, cur += step)
		{
			if (cur > max_bisquare || !is_bisquares[cur])
				return false;
		}
		return true;
	}
	
	bool found_ariprog;
	void FindAllAriProg()
	{
		found_ariprog = false;
		int max_step = M * M * 2 / (N - 1) + 1;
		int n = bisquares.size();
		for (int step = 1; step <= max_step; step++)
		{
			for (int i = 0; i < n; i++)
			{
				if (TestAriProgFromStartWithStep(bisquares[i], step))
				{
					fout << bisquares[i] << " " << step << endl;
					found_ariprog = true;
				}
			}
		}
	}
public:
	void run()
	{
		Input();
		GenerateBisquares();
		FindAllAriProg();
		if (!found_ariprog)
			fout << "NONE" << endl;
	}
};

int main()
{	
	Solution s;
	s.run();
	return 0;
}

