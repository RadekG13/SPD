// jg.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

//#include "pch.h"

#include <queue>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <chrono>
using namespace std;
int  time2, time3, time4, time5, time6;
int rozmiar;

class problem {
public:
	int r;
	int p;
	int q;
	int numer_zadania = 0;

};
std::vector < problem > G;
std::vector < problem > N;
std::vector < problem > TMP;




bool cmp_r(const problem& a, const problem& b)
{
	// smallest comes first
	return a.r < b.r;
}

bool cmp_q(const problem& a, const problem& b)
{
	// smallest comes first
	return a.q > b.q;
}


//DRUGA WERSJA, BO ROBILIŚMY OSOBNO I LOGIKI DZIAŁAJĄ ODWROTNIE
bool cmp_r2(const problem& a, const problem& b)
{

	return a.r > b.r;
}

bool cmp_q2(const problem& a, const problem& b)
{

	return a.q < b.q;
}




ostream& operator<< (ostream& wyjscie, const problem& pom) {
	return wyjscie << "r: " << pom.r << "p: " << pom.p << "q: " << pom.q << endl;
}




struct Compare_R {
	bool operator()(problem const& p1, problem const& p2)
	{
		// return "true" if "p1" is ordered  
		// before "p2", for example: 
		return p1.r > p2.r;
	}
};
struct Compare_Q {
	bool operator()(problem const& p1, problem const& p2)
	{
		// return "true" if "p1" is ordered  
		// before "p2", for example: 
		return p1.q < p2.q;
	}
};



std::vector <problem> G1;
std::priority_queue <  problem, vector<problem>, Compare_R > N1;
std::priority_queue <  problem, vector<problem>, Compare_Q > TMP1;
std::priority_queue <  problem, vector<problem>, Compare_R > N2;


int schrag2(int n, vector <problem>& tab) {
	int czas = 0;
	int czas2 = 0;
	int czas_q = 0;
	problem pom1;

	for (int i = 0; i < n; i++) N1.push(tab[i]);



	G1.push_back(N1.top());
	N1.pop();
	pom1 = G1[0];
	czas = pom1.r + pom1.p;



	while (G1.size() < n) {
		int a = 0;
		while (!N1.empty()) {

			if (N1.top().r <= czas) { //Bierzemy elementy o r mniejszym od p
				TMP1.push(N1.top()); //Wrzucamy do tymczasowej
				N1.pop();
				a = 1;

			}
			else if (N1.top().r > czas) {
				N2.push(N1.top());
				N1.pop();

			}

		}
		if (a == 0 && TMP1.size() == 0) {
			TMP1.push(N2.top());
			N2.pop();
		}
		swap(N2, N1);


		G1.push_back(TMP1.top());
		czas = czas + TMP1.top().p;

		TMP1.pop();

	}




	czas_q = G1[n - 1].q;



	int ostatni_el = G1.size() - 2;

	for (int i = 0; i < G1.size() - 2; i++) {
		int czas3 = 0;
		for (int j = 0; j < i + 1; j++) { czas3 = czas3 + G1[G1.size() - 1 - j].p; }

		czas2 = G1[ostatni_el - i].q - czas3;
		if (czas2 > czas_q) czas_q = czas2;


	}
	czas = czas + czas_q;

	return czas;
}


int naturalne(int n, vector <problem>& tab);


//ALGORYTM SCHRAGE Z PRZERWANIAMI
int schrage_przerwania(int n, vector <problem> tab) {
	int czas;
	problem  l, e;
	l.q = 0; //inicjalizacja
	int cmax = 0;
	vector<problem> N2; //lokalnie, ponieważ nadpisywało się ze zwykłym schrage 
	vector<problem> G2;
	sort(tab.begin(), tab.end(), cmp_r2); // Sortujemy po r rosnaco



	for (int i = 0; i < n; i++)
	{
		N2.push_back(tab[i]);
	}

	czas = N2.back().r;

	while (!G2.empty() || !N2.empty())
	{
		while (!N2.empty() && (N2.back().r <= czas))
		{

			e = N2.back();
			G2.push_back(e); //przeniesienie nieuszeregowane -> gotowe 
			N2.pop_back();	//
			if (e.q > l.q)
			{
				l.p = czas - e.r; //usunięcie czasu czesci juz zrobionego zadania
				czas = e.r;
				if (l.p > 0) //czy cale skonczone
				{
					G2.push_back(l);
				}
			}
		}
		if (!G2.empty())
		{
			sort(G2.begin(), G2.end(), cmp_q2); //sortowanie po q 
			czas = czas + G2.back().p; //czas 
			cmax = max(cmax, czas + G2.back().q); //pełny czas
			l = G2.back();
			G2.pop_back(); //zrobione
		}
		else
		{
			czas = N2.back().r;
		}

	}

	return cmax;
}


//ALGORYTM SCHRAGE Z PRZERWANIAMI PRZY UŻYCIU KOLEJEK PRIORYTETOWYCH
int schrage_przerwania2(int n, vector <problem>& tab) {
	int czas;
	problem  l, e;
	l.q = 0;
	int cmax = 0;
	std::priority_queue <  problem, vector<problem>, Compare_R > N;
	std::priority_queue <  problem, vector<problem>, Compare_Q > G;




	for (int i = 0; i < n; i++)
	{
		N.push(tab[i]);
	}

	czas = N.top().r;

	while (!G.empty() || !N.empty())
	{
		while (!N.empty() && (N.top().r <= czas))
		{

			e = N.top();
			G.push(e);
			N.pop();
			if (e.q > l.q)
			{
				l.p = czas - e.r;
				czas = e.r;
				if (l.p > 0)
				{
					G.push(l);
				}
			}
		}
		if (!G.empty())
		{
			czas = czas + G.top().p;
			cmax = max(cmax, czas + G.top().q);
			l = G.top();
			G.pop();
		}
		else
		{
			czas = N.top().r;
		}

	}

	return cmax;
}






/*

//Carlier

*/















int schrag(int n, vector <problem>& tab) {
	int czas;
	int czas2 = 0;
	int czas_q = 0;
	problem pom1;

	N = tab;
	sort(N.begin(), N.end(), cmp_r); // Sortujemy po r rosnaco
	// Bierzemy pierwszy element i wrzucamy go do vectora G po czym usuwamy z N


	G.push_back(N[0]);

	pom1 = G[0];
	czas = pom1.r + pom1.p;

	N.erase(N.begin());
	//for (int i = 0; i < N.size(); i++) cout << N[i] << endl;
	while (G.size() < n) {
		int a = 0;
		int k = 0;
		while (k < N.size()) {

			if (N[k].r < czas) { //Bierzemy elementy o r mniejszym od p
				TMP.push_back(N[k]); //Wrzucamy do tymczasowej
				N.erase(N.begin() + k);
				a = 1;
			}
			else k++;
		}
		if (a == 0 && TMP.size() == 0) {
			TMP.push_back(N[0]);
			N.erase(N.begin());
		}

		sort(TMP.begin(), TMP.end(), cmp_q);

		G.push_back(TMP[0]);
		czas = czas + TMP[0].p;
		//for (int i = 0; i < TMP.size(); i++) cout << TMP[i] << endl;
		//cout << "-------"<<endl;
		TMP.erase(TMP.begin());

	}
	//cout << czas;
	czas_q = G[n - 1].q;

	//for (int i = 0; i < G.size(); i++) cout << G[i] << endl;

	int ostatni_el = G.size() - 2;

	for (int i = 0; i < G.size() - 2; i++) {
		int czas3 = 0;
		for (int j = 0; j < i + 1; j++) { czas3 = czas3 + G[G.size() - 1 - j].p; }

		czas2 = G[ostatni_el - i].q - czas3;
		if (czas2 > czas_q) czas_q = czas2;


	}
	czas = czas + czas_q;

	return czas;
}







int naturalne(int n, vector <problem>& tab) {
	problem t1 = tab[0];
	problem t2;
	int S = t1.r;
	int C = S + t1.p;
	int cmax = C + t1.q;

	for (int i = 1; i < n; i++) {

		t2 = tab[i];

		S = max(t2.r, C);
		C = S + t2.p;
		cmax = max(cmax, C + t2.q);

	}

	return cmax;


}

std::vector < problem > tab;


int main()
{
	string linia;
	fstream plik;
	int liczba_zadan = 0;
	string pomoc;
	plik.open("data200.txt", ios::in);
	if (plik.good() == true)
	{



		plik >> liczba_zadan >> pomoc;


		for (int i = 0; i < liczba_zadan; ++i)
		{
			problem tmp;
			plik >> tmp.r >> tmp.p >> tmp.q;
			tab.push_back(tmp);
		}


		plik.close();


	}




	int time1;


	time1 = naturalne(liczba_zadan, tab);

	time3 = schrag(liczba_zadan, tab);

	time4 = schrag2(liczba_zadan, tab);

	time5 = schrage_przerwania(liczba_zadan, tab);

	time6 = schrage_przerwania2(liczba_zadan, tab);

	sort(tab.begin(), tab.end(), cmp_r);
	time2 = naturalne(liczba_zadan, tab);





	cout << "Czas naturalne: " << time1 << endl;
	cout << "Czas po sortowaniu: " << time2 << endl;
	cout << "czas schrage:" << time3 << endl;
	cout << "czas schrage na kolejce :" << time4 << endl;
	cout << "czas schrage z przerwaniami:" << time5 << endl;
	cout << "czas schrage z przerwaniami na kolejce:" << time6 << endl;
}

// -------- INSTRUKCJE DO MIERZENIA CZASU NA POTEM DO SPRAWKA ------- //
	  //auto start = std::chrono::system_clock::now(); // pomiar czasu - poczatek
	  //auto end = std::chrono::system_clock::now(); // pomiar czasu - stop
	  //std::chrono::duration<double> elapsed_seconds = end - start; // wynik - czas
	  //cout << " " << elapsed_seconds.count() << " "; // wyswietlenie czasu