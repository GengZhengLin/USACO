/*
ID: gzl80421
PROG: skidesign
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
	Solution() :fin("skidesign.in"), fout("skidesign.out"){}
private:
	int N;
	vector<int> elevations;
	int min_elevation;
	int max_elevation;
	int min_changes;
	void Input()
	{
		fin >> N;
		for (int i = 0; i < N; i++)
		{
			int temp;
			fin >> temp;
			elevations.push_back(temp);
		}
	}

	void FindMinElevation()
	{
		min_elevation = elevations[0];
		for (int i = 0; i < N; i++)
		{
			if (elevations[i] < min_elevation)
				min_elevation = elevations[i];
		}
	}

	void FindMaxElevation()
	{
		max_elevation = elevations[0];
		for (int i = 0; i < N; i++)
		{
			if (elevations[i] > max_elevation)
				max_elevation = elevations[i];
		}
	}

	int CalculateCostByMinHeight(int min_height)
	{
		int cost = 0;
		for (int i = 0; i < N; i++)
		{
			int diff = elevations[i] - min_height;
			if (diff < 0)
			{
				cost += diff * diff;
			}
			if (diff > 17)
			{
				cost += (diff - 17) * (diff - 17);
			}
		}
		return cost;
	}

	int CalculateMinCost()
	{
		int min_cost = CalculateCostByMinHeight(min_elevation);
		for (int i = min_elevation + 1;  i <= max_elevation; i++)
		{
			int cost = CalculateCostByMinHeight(i);
			if (cost < min_cost)
			{
				min_cost = cost;
			}
		}
		return min_cost;
	}
public:
	void run()
	{
		Input();
		FindMinElevation();
		FindMaxElevation();
		fout << CalculateMinCost() << endl;
	}
};

int main()
{
	Solution s;
	s.run();
	return 0;
}

