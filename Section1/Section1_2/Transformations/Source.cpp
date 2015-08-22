/*
ID: gzl80421
PROG: transform
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Solution
{
	ofstream fout;
	ifstream fin;
public:
	Solution() :fin("transform.in"), fout("transform.out"){}

	int N;
	char **mat1;
	char **mat2;
	char **mat_reflected;

	void Input()
	{
		fin >> N;
		// init 2d array
		mat1 = new char *[N];
		for (int i = 0; i < N; i++)
		{
			mat1[i] = new char[N];
		}
		Input2DArray(mat1);
		mat2 = new char *[N];
		for (int i = 0; i < N; i++)
		{
			mat2[i] = new char[N];
		}
		Input2DArray(mat2);
		mat_reflected = new char *[N];
		for (int i = 0; i < N; i++)
		{
			mat_reflected[i] = new char[N];
		}
	}

	void Input2DArray(char **p)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				fin >> p[i][j];
			}
		}
	}

	bool Check90Clockwise(char **mat1, char **mat2)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (mat1[i][j] != mat2[j][N - 1 - i])
					return false;
			}
		}
		return true;
	}

	bool Check180ClockWise(char **mat1, char **mat2)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (mat1[i][j] != mat2[N - 1 - i][N - 1 - j])
					return false;
			}
		}
		return true;
	}

	bool Check270ClockWise(char **mat1, char **mat2)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (mat1[i][j] != mat2[N - 1 - j][i])
					return false;
			}
		}
		return true;
	}

	bool CheckReflection(char **mat1, char **mat2)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (mat1[i][j] != mat2[i][N - 1 - j])
					return false;
			}
		}
		return true;
	}

	void Reflect(char **mat1, char **mat_reflected)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				mat_reflected[i][N - 1 - j] = mat1[i][j];
			}
		}
	}

	bool CheckCombination(char **mat1, char **mat2, char **mat_reflected)
	{
		Reflect(mat1, mat_reflected);
		return Check90Clockwise(mat_reflected, mat2) ||
			Check180ClockWise(mat_reflected, mat2) ||
			Check270ClockWise(mat_reflected, mat2);
	}

	bool CheckNoChange(char **mat1, char **mat2)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (mat1[i][j] != mat2[i][j])
					return false;
			}
		}
		return true;
	}
public:
	void run()
	{
		Input();
		int result = 0;
		if (Check90Clockwise(mat1, mat2)) result = 1;
		else if (Check180ClockWise(mat1, mat2)) result = 2;
		else if (Check270ClockWise(mat1, mat2)) result = 3;
		else if (CheckReflection(mat1, mat2)) result = 4;
		else if (CheckCombination(mat1, mat2, mat_reflected)) result = 5;
		else if (CheckNoChange(mat1, mat2)) result = 6;
		else result = 7;

		fout << result << endl;
	}
};

int main()
{
	Solution s;
	s.run();
	return 0;
}
