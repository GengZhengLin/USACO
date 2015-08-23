/*
ID: gzl80421
PROG: combo
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
	Solution() :fin("combo.in"), fout("combo.out"){}
private:
	struct combo
	{
		int n1, n2, n3;
		combo() :n1(0), n2(0), n3(0){}
		combo(int nn1, int nn2, int nn3) : n1(nn1), n2(nn2), n3(nn3){}
	};
	struct combo_compare
	{
		bool operator() (const combo& lhs, const combo& rhs) const
		{
			if (lhs.n1 != rhs.n1) return lhs.n1 < rhs.n1;
			else if (lhs.n2 != rhs.n2) return lhs.n2 < rhs.n2;
			else if (lhs.n3 != rhs.n3) return lhs.n3 < rhs.n3;
			else return false;
		}
	};
	int N;
	combo John_combo;
	combo master_combo;
	set<combo, combo_compare> combo_set;
	void Input()
	{
		fin >> N;
		fin >> John_combo.n1 >> John_combo.n2 >> John_combo.n3;
		fin >> master_combo.n1 >> master_combo.n2 >> master_combo.n3;
	}

	inline int GetComboLegalNum(int num)
	{
		return (num + N) % N;
	}
	void AddKeysFromCombo(combo key)
	{
		for (int n1 = -2; n1 <= 2; n1++)
			for (int n2 = -2; n2 <= 2; n2++)
				for (int n3 = -2; n3 <= 2; n3++)
				{
					combo temp(GetComboLegalNum(n1 + key.n1), GetComboLegalNum(n2 + key.n2), GetComboLegalNum(n3 + key.n3));
					combo_set.insert(temp);
				}
	}
public:
	void run()
	{
		Input();
		AddKeysFromCombo(John_combo);
		AddKeysFromCombo(master_combo);
		fout << combo_set.size() << endl;
	}
};

int main()
{
	Solution s;
	s.run();
	return 0;
}

