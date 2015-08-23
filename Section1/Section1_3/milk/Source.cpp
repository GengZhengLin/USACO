/*
ID: gzl80421
PROG: milk
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
	Solution() :fin("milk.in"), fout("milk.out"){}
private:
	struct BoughtMilk
	{
		int price;
		int max_amount;
		int amount;
		BoughtMilk *next;
		BoughtMilk *prev;

		BoughtMilk(int p, int m) :price(p), max_amount(m), amount(0), next(NULL), prev(NULL){}
	};

	BoughtMilk *head;
	BoughtMilk *tail;
	int N; // amount of milk wanted
	int M; // number of farmers

	int total_price;
	int bought_milk;
	
	void Input()
	{
		head = tail = NULL;
		total_price = bought_milk = 0;
		fin >> N >> M;
	}

	void InsertFarmer(int price, int max_amount)
	{
		BoughtMilk *obj = new BoughtMilk(price, max_amount);
		InsertToList(obj);
		RemoveExtra();
	}

	void InsertToHead(BoughtMilk *obj)
	{
		obj->next = head;
		obj->prev = NULL;
		if (head != NULL)
			head->prev = obj;
		head = obj;
	}

	void InsertToTail(BoughtMilk *obj)
	{
		obj->prev = tail;
		obj->next = NULL;
		if (tail != NULL)
			tail->next = obj;
		tail = obj;
	}

	void InsertBetween(BoughtMilk *obj, BoughtMilk *p1, BoughtMilk *p2)
	{		
		if (p1 != NULL && p2 != NULL)
		{
			p1->next = obj;
			obj->prev = p1;
			p2->prev = obj;
			obj->next = p2;
		}
		else
		{
			if (p1 == NULL) InsertToHead(obj);
			if (p2 == NULL) InsertToTail(obj);
		}
	}

	void UpdateGlobalsInsert(BoughtMilk *obj)
	{
		obj->amount = obj->max_amount;
		bought_milk += obj->amount;
		total_price += obj->amount * obj->price;
	}

	void UpdateGlobalsRemove(BoughtMilk *obj)
	{
		bought_milk -= obj->amount;
		total_price -= obj->amount * obj->price;
	}

	void UpdateGlobalRemovePart(BoughtMilk *obj)
	{
		int to_remove = bought_milk - N;
		obj->amount -= to_remove;
		bought_milk = N;
		total_price -= obj->price * to_remove;
	}

	void InsertToList(BoughtMilk *obj)
	{
		BoughtMilk *cur = head;
		BoughtMilk *prev = NULL;
		bool inserted = false;
		while (cur != NULL && cur->price <= obj->price)
		{
			prev = cur;
			cur = cur->next;
		}
		// cur = first cur->price > obj->price

		// first node
		if (cur == NULL && prev == NULL)
		{
			InsertToHead(obj);
			InsertToTail(obj);
			inserted = true;
		}

		// insert head
		if (cur != NULL && prev == NULL)
		{
			InsertToHead(obj);
			inserted = true;
		}

		// normal situation
		if (cur != NULL && prev != NULL)
		{
			InsertBetween(obj, prev, cur);
			inserted = true;
		}

		// last node
		if (cur == NULL && prev != NULL)
		{
			if (bought_milk < N)
			{
				InsertToTail(obj);
				inserted = true;
			}
		}

		if (inserted)
		{
			UpdateGlobalsInsert(obj);
		}
	}

	void RemoveLast()
	{
		if (tail == NULL) return;
		BoughtMilk *temp = tail;
		tail = tail->prev;
		if (tail == NULL) return;
		tail->next = NULL;
		delete temp;
	}

	void RemoveExtra()
	{
		while (bought_milk > N)
		{
			// remove last
			if (bought_milk - tail->amount > N)
			{
				UpdateGlobalsRemove(tail);
				RemoveLast();				
			}
			else
			{
				UpdateGlobalRemovePart(tail);
			}
		}
	}
public:
	void run()
	{
		Input();
		for (int i = 0; i < M; i++)
		{
			int price = 0;
			int max_amount = 0;
			fin >> price >> max_amount;
			InsertFarmer(price, max_amount);
		}
		fout << total_price << endl;
	}
};

int main()
{	
	Solution s;
	s.run();
	return 0;
}

