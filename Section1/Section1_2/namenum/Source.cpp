/*
ID: gzl80421
PROG: namenum
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
	Solution() :fin("namenum.in"), fout("namenum.out"){}
	void run()
	{
		has_name = false;
		ReadDict();
		string num;
		fin >> num;
		GetNameFromNum(num);
		if (!has_name) fout << "NONE" << endl;
	}
private:
	vector<string> name_dic;

	void ReadDict()
	{
		ifstream dfin("dict.txt");
		while (dfin.good())
		{
			string name;
			dfin >> name;
			name_dic.push_back(name);
		}
	}

	char GetNumberFromChar(char c)
	{
		if (c >= 'A' && c <= 'C') return '2';
		if (c >= 'D' && c <= 'F') return '3';
		if (c >= 'G' && c <= 'I') return '4';
		if (c >= 'J' && c <= 'L') return '5';
		if (c >= 'M' && c <= 'O') return '6';
		if (c >= 'P' && c <= 'S') return '7';
		if (c >= 'T' && c <= 'V') return '8';
		if (c >= 'W' && c <= 'Y') return '9';
		return '0';
	}

	string GetNumFromName(string name)
	{
		string num = "";
		int n = name.length();
		for (int i = 0; i < n; i++)
		{
			num += GetNumberFromChar(name[i]);
		}
		return num;
	}

	bool has_name;
	void GetNameFromNum(string num)
	{
		int n = name_dic.size();
		for (int i = 0; i < n; i++)
		{
			if (GetNumFromName(name_dic[i]) == num)
			{
				fout << name_dic[i] << endl;
				has_name = true;
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

