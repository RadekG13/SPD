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
#include <chrono>
using namespace std;





class problem {
public:
	int lp=0;//numer zadania
	int r=0;
	int p=0;
	int q=0;
	

};
std::vector < problem > G;
std::vector < problem > N;
std::vector < problem > TMP;

struct zwrot {
	int czas;
	vector <int> perm;
};

zwrot z1, z2, z3, z4, z5, z6;

bool cmp_r(const problem& a, const problem& b)
{
	
	return a.r < b.r;
}

bool cmp_q(const problem& a, const problem& b)
{
	
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


void przypisz(vector<int>& w1, vector<problem>& w2) {

	for (int i = 0; i < w2.size(); i++) w1.push_back(w2[i].lp);
}

/*
void przypisz2(vector<problem>& w1, vector<problem>& w2) {

	for (int i = 0; i < w2.size(); i++) w1.push_back(w2[i]);
}
*/

ostream& operator<< (ostream& wyjscie, const problem& pom) {
	return wyjscie << "r: " << pom.r << "p: " << pom.p << "q: " << pom.q << endl;
}

int naturalne(int n, vector <problem>& tab);


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


zwrot schrag2(int n, vector <problem>& tab, vector <problem>& perm ) { //perm mial byc uzyty do alg Carliera
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
	z1.czas = czas;
	
	przypisz(z1.perm, G1);
	//przypisz2(perm, G1);//do Carliera
	return z1;
}






int schrage_przerwania(int n, vector <problem> tab) {
	int czas;
	problem  l, e;
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
			G2.push_back(e);//przeniesienie nieuszeregowane -> gotowe 
			N2.pop_back();//
			if (e.q > l.q)
			{
				l.p = czas - e.r;//usunięcie czasu czesci juz zrobionego zadania
				czas = e.r;
				if (l.p > 0)//czy cale skonczone
				{
					G2.push_back(l);
				}
			}
		}
		if (!G2.empty())
		{
			sort(G2.begin(), G2.end(), cmp_q2); //sortowanie po q 
			czas = czas + G2.back().p;//czas
			cmax = max(cmax, czas + G2.back().q);//pełny czas
			l = G2.back();
			G2.pop_back();//zrobione
		}
		else
		{
			czas = N2.back().r;
		}

	}
	return cmax;
	
	
	
}



int schrage_przerwania2(int n, vector <problem>& tab) { //schrage_przerwania na kolejkach priotytetowych
	int czas;
	problem  l, e;

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
			G.push(e);//przeniesienie nieuszeregowane -> gotowe 
			N.pop();
			if (e.q > l.q)
			{
				l.p = czas - e.r;//usunięcie czasu czesci juz zrobionego zadania
				czas = e.r;
				if (l.p > 0)//czy cale skonczone
				{
					G.push(l);
				}
			}
		}
		if (!G.empty())
		{
			czas = czas + G.top().p;//czas
			cmax = max(cmax, czas + G.top().q);//pelny czas
			l = G.top();
			G.pop();//zrobione
		}
		else
		{
			czas = N.top().r;
		}

	}

	return cmax;

}






/*

//Carlier - none yet

*/












zwrot schrag(int n, vector <problem>& tab) {
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
	z2.czas = czas;
	przypisz(z2.perm, G);
	return z2;
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




int main()
{
	
	fstream plik;
	int liczba_zadan = 0;
	string pomoc;
	vector<problem> PI; //carlier
	vector < problem > tab;
	int time1, time2, time3, time4, time5, time6;
	plik.open("data10.txt", ios::in);
	if (plik.good() == true)
	{



		plik >> liczba_zadan >> pomoc;


		for (int i = 0; i < liczba_zadan; ++i)
		{
			problem tmp;
			plik >> tmp.r >> tmp.p >> tmp.q;
			tmp.lp = i;
			tab.push_back(tmp);
		}


		plik.close();


	}






	//auto start1 = std::chrono::system_clock::now(); // POMIAR CZASU
	time1 = naturalne(liczba_zadan, tab);
	//auto end1 = std::chrono::system_clock::now();
	//std::chrono::duration<double> cz1 = end1 - start1;
	//cout << "Czas wykonywania zwyklego " << cz1.count() << endl;
	cout << "Czas naturalne: " << time1 << endl;

	//auto start2 = std::chrono::system_clock::now();
	z2.czas = schrag(liczba_zadan, tab).czas;
	//auto end2 = std::chrono::system_clock::now();
	//std::chrono::duration<double> cz2 = end2 - start2;
	//cout << "Czas wykonywania schrage " << cz2.count() << endl;
	cout << "czas schrage:" << z2.czas << endl;
	cout << "permutacja: " << endl;
	for (int i = 0; i < z2.perm.size(); i++) cout << z2.perm[i] <<",";
	cout << endl;
	//auto start3 = std::chrono::system_clock::now();
	z1.czas = schrag2(liczba_zadan, tab,PI).czas;
	//for (int i = 0; i < PI.size(); i++) cout << PI[i].lp << ",";
	//auto end3 = std::chrono::system_clock::now();
	//std::chrono::duration<double> cz3 = end3 - start3;
	//cout << "Czas wykonywania schrage na kolejce " << cz3.count() << endl;
	cout << "czas schrage na kolejce :" << z1.czas << endl;
	//for (int i = 0; i < z2.perm.size(); i++) cout << z1.perm[i] << endl;
	//auto start4 = std::chrono::system_clock::now();
	z3.czas = schrage_przerwania(liczba_zadan, tab);
	//auto end4 = std::chrono::system_clock::now();
	//std::chrono::duration<double> cz4 = end4 - start4;
	//cout << "Czas wykonywania schrage z przerwaniami " << cz4.count() << endl;
	cout << "czas schrage z przerwaniami:" << z3.czas << endl;

	//auto start5 = std::chrono::system_clock::now();
	z4.czas = schrage_przerwania2(liczba_zadan, tab);
	//auto end5 = std::chrono::system_clock::now();
	//std::chrono::duration<double> cz5 = end5 - start5;
	//cout << "Czas wykonywania schrage z przerwaniami na kolejce" << cz5.count() << endl;
	cout << "czas schrage z przerwaniami na kolejce:" << z4.czas << endl;

	//auto start6 = std::chrono::system_clock::now();
	sort(tab.begin(), tab.end(), cmp_r);
	time2 = naturalne(liczba_zadan, tab);
	//auto end6 = std::chrono::system_clock::now();
	//std::chrono::duration<double> cz6 = end6 - start6;
	//cout << "Czas po sortowaniu" << cz6.count() << endl;

	cout << "Czas po sortowaniu R:" << time2 << endl;







}

