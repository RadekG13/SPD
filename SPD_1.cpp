// jg.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
int time, time2;
int rozmiar;
struct problem {
	int r;
	int p;
	int q;
	bool operator < (const problem& x)const
	{
		return r < x.r;
	}
};

ostream& operator<< (ostream& wyjscie, const problem& pom) {
	return wyjscie << "r: " << pom.r << "p: " << pom.p << "q: " << pom.q << endl;
}

std::vector < problem > tab;

int naturalne(int n, vector <problem>& tab) {
	problem t1 = tab[0];
	problem t2;
	problem t3;
	int czas = t1.r;
	int czas2;
	for (int i = 0; i < n; i++) {
		t2 = tab[i];

		czas = czas + t2.p;

		if (i < n - 1) {
			t3 = tab[i + 1];
			czas2 = t2.q - t3.p;

			if (czas2 < 0) czas2 = 0;


			if (t3.r > czas) {
				czas = czas + (t3.r - czas);
			}
		}
		if (czas2 == 0) czas2 = t2.q;
	}
	czas = czas + czas2;

	return czas;
}

int main()
{
	string linia;
	fstream plik;
	int liczba;

	plik.open("data10.txt", ios::in);
	if (plik.good() == true)
	{
		plik >> liczba;


		//int n = 0;
		string pomoc;
		plik >> pomoc;
		while (!plik.eof())
		{
			problem tmp;
			plik >> tmp.r >> tmp.p >> tmp.q;
			tab.push_back(tmp);

		}
		for (int i = 0; i < tab.size(); i++) {
			cout << tab[i] << endl;
		}
		rozmiar = tab.size();
		plik.close();

	}
	time = naturalne(rozmiar, tab);
	cout << "Czas pierwszy: " << time << endl;
	sort(tab.begin(), tab.end());
	for (int i = 0; i < tab.size(); i++) {
		cout << tab[i] << endl;
	}
	time2 = naturalne(rozmiar, tab);
	cout << "Czas drugi: " << time2 << endl;
}

