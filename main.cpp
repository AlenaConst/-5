#include <iostream>
#include <list>
#include <iterator>
//#include <utility>

using namespace std;

ostream& operator <<(ostream& out, list<pair<int, int>> pol)
{
	list<pair<int, int>>::iterator it = pol.begin();
	while(it != pol.end())
	{
		if ((*it).first != 0)
		{
			cout << (*it).first ;
			if ((*it).second != 0) { cout << "x^" << (*it).second; }
		}
		it++;
		if (it != pol.end()) { cout << '+'; }
	}
	cout << '\n';
	return out;
}

list<pair<int, int>> operator *(list<pair<int, int>> pol, pair<int, int> fac)
{
	list<pair<int, int>>::iterator it = pol.begin();
	while (it != pol.end() && (*it).first != 0)
	{
		(*it).first *= fac.first;
		(*it).second += fac.second;
		it++;
	}
	return pol;
}

list<pair<int, int>> operator +(list<pair<int, int>> pol1, list<pair<int, int>> pol2)
{
	list<pair<int, int>>::iterator it1 = pol1.begin();
	list<pair<int, int>>::iterator it2 = pol2.begin();
	list<pair<int, int>> pol3;
	while (it1 != pol1.end() && it2 != pol2.end() && (*it1).first != 0 && (*it2).first != 0)
	{
		if ((*it1).second > (*it2).second)
		{
			pol3.push_back(*it1);
			it1++;
		}
		else if ((*it1).second < (*it2).second)
		{
			pol3.push_back(*it2);
			it2++;
		}
		else
		{
			pol3.push_back(pair<int, int>((*it1).first + (*it2).first, (*it1).second));
			it1++;
			it2++;
		}
	}
	while (it1 != pol1.end() && (*it1).first != 0)
	{
		pol3.push_back(*it1);
		it1++;
	}
	while (it2 != pol2.end() && (*it2).first != 0)
	{
		pol3.push_back(*it2);
		it2++;
	}
	//if ((*pol3.end()).first == 0)
	//{
	//	pol3.pop_pack();
	//}
	return pol3;
}

int main()
{
	list<pair<int, int>> A[11];
	A[0].push_front(pair<int, int>(0, 0));
	A[1].push_front(pair<int, int>(1, 0));
	for (int i = 2; i < 11; i++)
	{
		A[i] = A[i - 1] * pair<int, int>(1, 1) + A[i - 2];
	}
	int k;
	cout << "Choose command:\n" << "1. Cout element[i]\n" << "2. Exit\n\n";
	while (1)
	{
		cout << "Enter the command: ";
		cin >> k;
		if (k == 1)
		{
			int i;
			cout << "Enter i: ";
			cin >> i;
			cout << A[i];
		}
		else
		{
			break;
		}
	}
//	cout << A[10];
	//pol.push_back(pair<int, int>(12, 12));
	//show(A[0]);
	//show(A[1]);
	return 0;
}
