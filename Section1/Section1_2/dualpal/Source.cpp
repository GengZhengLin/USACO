/*
ID: gzl80421
PROG: dualpal
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

class Solution
{
	ofstream fout;
	ifstream fin;
public:
	Solution() :fin("dualpal.in"), fout("dualpal.out"){}
private:
	int N;
	int S;
	void Input()
	{
		fin >> N;
		fin >> S;
	}

	string NumToStr(int n, int B)
	{
		string num_str = "";
		while (n > 0)
		{
			int x = n % B;
			char c;
			if (x <= 9)
				c =  (x + '0');
			if (x >= 10)
				c = x - 10 + 'A';
			num_str = c + num_str;
			n = n / B;
		}
		return num_str;
	}

	bool IsPalindromic(string str)
	{
		int i = 0, j = str.length() - 1;
		while (i < j)
		{
			if (str[i] != str [j])
				return false;
			i ++; j --;
		}
		return true;
	}

	bool IsDualPal(int n)
	{
		int b;
		int dual_counter = 0;
		for (b = 2; b <= 10; b++)
		{
			if (IsPalindromic(NumToStr(n, b)))
				dual_counter ++;
			if (dual_counter >= 2)
				return true;
		}
		return false;
	}
public:
	void run()
	{
		Input();
		int dual_counter = 0;
		for (int i = S+1; ;i++)
		{
			if (IsDualPal(i))
			{
				fout << i << endl;
				dual_counter ++;
				if (dual_counter >= N)
					return;
			}
		}
	}
};

int main()
{	
	Solution s;
	s.run();
	return 0;
}

