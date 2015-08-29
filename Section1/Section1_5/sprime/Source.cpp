/*
ID: gzl80421
PROG: sprime
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int super_prime_table[8][16] = {
	{ 2, 3, 5, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 23, 29, 31, 37, 53, 59, 71, 73, 79, 0, 0, 0, 0, 0, 0, 0},
	{ 233, 239, 293, 311, 313, 317, 373, 379, 593, 599, 719, 733, 739, 797, 0, 0},
	{ 2333, 2339, 2393, 2399, 2939, 3119, 3137, 3733, 3739, 3793, 3797, 5939, 7193, 7331, 7333, 7393 },
	{ 23333, 23339, 23399, 23993, 29399, 31193, 31379, 37337, 37339, 37397, 59393, 59399, 71933, 73331, 73939, 0 },
	{ 233993, 239933, 293999, 373379, 373393, 593933, 593993, 719333, 739391, 739393, 739397, 739399, 0, 0, 0, 0 },
	{ 2339933, 2399333, 2939999, 3733799, 5939333, 7393913, 7393931, 7393933, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 23399339, 29399999, 37337999, 59393339, 73939133, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

class Solution
{
	ofstream fout;
	ifstream fin;
public:
	Solution() :fin("sprime.in"), fout("sprime.out"){}
private:
	vector<int> super_primes[8];
	int N;
	int *prime_nums;
	int binary_getter[32];

	void SetBinaryGetter()
	{
		binary_getter[0] = 1;
		for (int i = 1; i < 32; i++)
		{
			binary_getter[i] = binary_getter[i - 1] << 1;
		}
	}

	void Input()
	{
		fin >> N;

	}

#define MAX_N 100000000
	inline void RemoveBaseMultiFromPrimeNums(int base)
	{
		int step = base << 1;
		for (int num = (base << 1) + base; num <= MAX_N; num += step)
		{
			SetPrimeNum(num);
		}
	}

	inline void SetPrimeNum(int i)
	{
		int index = (i - 3) / 2;
		int x = index >> 5;
		int y = index & 31;
		prime_nums[x] |= binary_getter[y];
	}

	inline bool GetPrimeNum(int i)
	{
		int index = (i - 3) / 2;
		int x = index >> 5;
		int y = index & 31;
		return (prime_nums[x] & binary_getter[y]) == 0;
	}

	void SievePrimes()
	{

		int max_num = MAX_N / 32 + 1;
		prime_nums = new int[max_num];
		for (int i = 0; i < max_num; i++)
			prime_nums[i] = 0;
		int cur_num = 3;
		for (int j = 0; cur_num <= MAX_N; j++)
		{
			for (int i = 0; i < 32 && cur_num <= MAX_N; i++, cur_num += 2)
			{
				if ((prime_nums[j] & binary_getter[i]) == 0)
				{
					RemoveBaseMultiFromPrimeNums(cur_num);
				}
			}
		}
	}

	void InitSuperPrimes()
	{
		super_primes[0].push_back(2);
		super_primes[0].push_back(3);
		super_primes[0].push_back(5);
		super_primes[0].push_back(7);
	}

	void CalSuperPrimes(int length_1)
	{
		int n1 = super_primes[length_1 - 1].size();
		int prime_bits[] = { 1, 3, 7, 9 };
		for (int i = 0; i < n1; i++)
		{
			int temp = super_primes[length_1-1][i];
			for (int j = 0; j < 4; j ++)
			{
				int num = temp * 10 + prime_bits[j];
				if (GetPrimeNum(num))
				{
					super_primes[length_1].push_back(num);
				}
			}
		}
	}

	void Output()
	{
		//vector<int> r = super_primes[N - 1];
		//int n = r.size();
		//for (int i = 0; i < n; i++)
		//{
		//	fout << r[i] << endl;
		//}
		int max_n = 0;
		for (int i = 0; i < 8; i++)
		{
			int n = super_primes[i].size();
			if (n > max_n)
			{
				max_n = n;
			}
		}

		for (int i = 0; i < 8; i++)
		{
			vector<int> r = super_primes[i];
			int j = 0, n = r.size();
			for (j = 0; j < n; j++)
			{
				fout << r[j] << ", ";
			}
			while (j < max_n)
			{
				fout << "0, ";
				j++;
			}
			fout << endl;
		}
	}
public:
	void run()
	{
		Input();
		//SetBinaryGetter();
		//SievePrimes();
		//InitSuperPrimes();
		//for (int i = 1; i < N; i++)
		//{
		//	CalSuperPrimes(i);
		//}
		//Output();
		for (int i = 0; i < 16 && super_prime_table[N - 1][i] != 0; i++)
		{
			fout << super_prime_table[N - 1][i] << endl;
		}
	}
};

int main()
{
	Solution s;
	s.run();
	return 0;
}

