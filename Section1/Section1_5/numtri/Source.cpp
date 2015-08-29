/*
ID: gzl80421
PROG: numtri
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
	Solution() :fin("numtri.in"), fout("numtri.out"){}
private:
	int R;
	int **num_tri;
	int **num_path;
	int** Malloc2DArray(int n1, int n2)
	{
		int **to_return = new int *[n1];
		for (int i = 0; i < n1; i++)
		{
			to_return[i] = new int[n2];
		}
		return to_return;
	}

	void Input()
	{
		fin >> R;
		num_tri = Malloc2DArray(R, R);
		num_path = Malloc2DArray(R, R);

		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				fin >> num_tri[i][j];
			}
		}
	}
	
	void InitNumPath()
	{
		for (int i = 0; i < R; i++)
		{
			num_path[R - 1][i] = num_tri[R - 1][i];
		}
	}

	void CalNumPath()
	{
		InitNumPath();
		for (int i = R - 2; i >= 0; i--)
		{
			for (int j = 0; j <= i; j++)
			{
				int left = num_path[i + 1][j];
				int right = num_path[i + 1][j + 1];
				int bigger = left > right ? left : right;
				num_path[i][j] = num_tri[i][j] + bigger;
			}
		}
	}

	int CalLargestPath(int y, int x)
	{
		if (y == R - 1)
			return num_tri[y][x];
		int left = CalLargestPath(y + 1, x);
		int right = CalLargestPath(y + 1, x + 1);
		int bigger = left > right ? left : right;
		return bigger + num_tri[y][x];
	}

public:
	void run()
	{
		Input();
		CalNumPath();
		fout << num_path[0][0] << endl;
	}
};

int main()
{
	Solution s;
	s.run();
	return 0;
}

