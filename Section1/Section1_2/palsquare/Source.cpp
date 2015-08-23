/*
ID: gzl80421
PROG: palsquare
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
	Solution() :fin("palsquare.in"), fout("palsquare.out"){}
private:
	int B;
	char buffer[32];
	void Input()
	{
		fin >> B;
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
	string GetSquareStr(int n)
	{
		int x = n * n;
		return NumToStr(x, B);
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
public:
	void run()
	{
		Input();
		for (int i = 1; i <= 300; i++)
		{
			string square_str = GetSquareStr(i);
			if (IsPalindromic(square_str))
			{
				fout << NumToStr(i, B) << " " << square_str << endl;
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

