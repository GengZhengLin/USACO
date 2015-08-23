/*
ID: gzl80421
PROG: crypt1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Solution
{
	ofstream fout;
	ifstream fin;
public:
	Solution() :fin("crypt1.in"), fout("crypt1.out"){}
private:
	int N; // N, the number of digits that will be used
	vector<int> num_set;
	int num_of_solutions;
	void Input()
	{
		num_of_solutions = 0;

		fin >> N;
		for (int i = 0; i < N; i++)
		{
			int temp; fin >> temp;
			num_set.push_back(temp);
		}		
	}

	string NumToStr(int num)
	{
		stringstream ss;
		ss << num;
		return ss.str();
	}

	bool IsInNumSet(int x)
	{
		for (int i = 0; i < N; i++)
		{
			if (x == num_set[i]) return true;
		}
		return false;
	}

	bool IsLegalNum(int num)
	{
		string str = NumToStr(num);
		for (int i = 0; i < str.length(); i++)
		{
			if (!IsInNumSet(str[i] - '0'))
				return false;
		}
		return true;
	}

	bool Test5Nums(int x1, int x2, int x3, int y1, int y2)
	{
		int x = x1 * 100 + x2 * 10 + x3;
		int m1 = x * y1;
		if (m1 >= 1000 || !IsLegalNum(m1))
			return false;
		int m2 = x * y2;
		if (m2 >= 1000 || !IsLegalNum(m2))
			return false;
		int r = m1 + m2 * 10;
		if (r >= 10000 || !IsLegalNum(r))
			return false;
		return true;
	}

	void Iterate5Nums()
	{
		int x1, x2, x3, y1, y2;
		int n = num_set.size();
		for (x1 = 0; x1 < n; x1++)
			for (x2 = 0; x2 < n; x2++)
				for (x3 = 0; x3 < n; x3++)
					for (y1 = 0; y1 < n; y1++)
						for (y2 = 0; y2 < n; y2++)
						{
							if (Test5Nums(num_set[x1], num_set[x2], num_set[x3], num_set[y1], num_set[y2]))
							{
								num_of_solutions++;
								// OutputSolution(num_set[x1], num_set[x2], num_set[x3], num_set[y1], num_set[y2]);
							}
								
						}
	}

	void OutputSolution(int x1, int x2, int x3, int y1, int y2)
	{
		fout << " " << x1 << x2 << x3 << endl;
		fout << "x" << " " << y1 << y2 << endl;
		int x = x1 * 100 + x2 * 10 + x3;
		int m1 = x * y1;
		int m2 = x * y2;
		int r = m1 + m2 * 10;
		fout << " " << m1 << endl;
		fout << m2 << endl;
		fout << r << endl;
	}
public:
	void run()
	{
		Input();
		Iterate5Nums();
		fout << num_of_solutions << endl;
	}
};

int main()
{
	Solution s;
	s.run();
	return 0;
}

