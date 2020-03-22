// jg.cpp : Ten plik zawiera funkcjê „main”. W nim rozpoczyna siê i koñczy wykonywanie programu.
//

//#include "pch.h"


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
	bool operator ()( problem x,  problem y)const
	{	
		
			
			
			return x.r < y.r;
	}
}myobject;

ostream& operator<< (ostream& wyjscie, const problem& pom) {
	return wyjscie << "r: " << pom.r << "p: " << pom.p << "q: " << pom.q << endl;
}

std::vector < problem > tab;

int naturalne(int n, vector <problem>& tab) {
	problem t1 = tab[0];
	problem t2;
	int S = t1.r;  
	int C=S+t1.p;
	int cmax=C+t1.q;
	
	for (int i = 1; i < n-1; i++) {
		
		t2 = tab[i];
		
		S = max(t2.r, C);
		C = S + t2.p;
		cmax = max(cmax, C + t2.q);
		
	}

	return cmax;


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


		
		string pomoc;
		plik >> pomoc;
		while (!plik.eof())
		{
			problem tmp;
			plik >> tmp.r >> tmp.p >> tmp.q;
			tab.push_back(tmp);

		}
		
		rozmiar = tab.size();
		plik.close();
		

	}
	tab.erase(tab.end() - 1);// USUWANIE OSTATNIEGO ELEMENTU TABLICY, BO DWA RAZY CZYTA£ 
	

	time = naturalne(rozmiar, tab);
	cout << "Czas pierwszy: " << time << endl;
	

	sort(tab.begin(), tab.end(), myobject);

	
	time2 = naturalne(rozmiar, tab);
	cout << "Czas drugi: " << time2 << endl;
}

