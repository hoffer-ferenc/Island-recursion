// szigetek_rekurzio.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <time.h>
#include <iostream>

using namespace std;

int keres(int **tomb, int i, int j, int N, int m, int aktmeret) {
	tomb[i][j] = 2;			//a vizsgált elemeket átírjuk
	aktmeret++;
	// a túlindexelés érdekében kikötjük meddig mehet, ha találat van növelje az aktuális méret változót
	if (i - 1 >= 0 && tomb[i - 1][j] == 1) {			//északi irány vizsgálat
		aktmeret += keres(tomb, i - 1, j, N, m, 0);
	}
	if (i + 1 < N && tomb[i + 1][j] == 1) {				//déli irány vizsgálat
		aktmeret += keres(tomb, i + 1, j, N, m, 0);
	}
	if (j - 1 >= 0 && tomb[i][j - 1] == 1) {			//nyugati irány vizsgálat
		aktmeret += keres(tomb, i, j - 1, N, m, 0);
	}
	if (j + 1 < m && tomb[i][j + 1] == 1) {				//keleti irány vizsgálat
		aktmeret += keres(tomb, i, j + 1, N, m, 0);
	}
	return aktmeret;
}

int main() {

	setlocale(LC_ALL, "hun");			//magyarosítás
	srand(time(0));						//új random generálása
	double p;
	cout << "adja meg a méretet!" << endl;
	int N;
	cin >> N;							//adat bekérés (a valószínűséget ellenőrzötten)
	cout << "adja meg a valoszinuséget! 0-1" << endl;
	do
	{
		cin >> p;
		if (p < 0 || p > 1)
		{
			cout << "hibás adat, 0 és 1 közötti szám a valószínűség!" << endl;
		}
	} while (p < 0 || p > 1);

	//alap mátrix létrehozás
	int **tomb;
	tomb = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; ++i)
	{
		tomb[i] = (int*)malloc(N * sizeof(int));
	}
	// segédtömb létrehozás
	double **tomb2;
	tomb2 = (double**)malloc(N * sizeof(double*));

	for (int i = 0; i < N; ++i)
	{
		tomb2[i] = (double*)malloc(N * sizeof(double));
	}

	//tömb feltöltés 1-esekkel és 0-ákkal és kiíratás
	int egy = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			double val = (double)rand() / (double)RAND_MAX;		//0 és 1 közt generál double számot
																//és persze a segédtömbünkben tároljuk a random double értékeket
			tomb2[i][j] = val;									//és kicsit trükkös, de a generált szám a valószínűség
																//függvényében tölti fel az alap tömböt 0 és 1 közötti értékkel
			if (tomb2[i][j] > p)
			{
				tomb[i][j] = 0;
			}
			else if (tomb2[i][j] < p)
			{
				tomb[i][j] = 1;
			}
			cout << tomb[i][j] << "\t";

			//megszámlálás
			if (tomb[i][j] == 1)
			{
				egy++;
			}

		}
		cout << "\n";
	}
	cout << egy << ". egyes van benne" << endl;

	// terület mérés
	int maxterulet = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (tomb[i][j] == 1)
			{
				int aktmax = keres(tomb, i, j, N, N, 0); //metódus meghívás a meglévő értékekhez
				if (aktmax > maxterulet) { //maximum kiválasztás
					maxterulet = aktmax;
				}
			}
		}
	}
	cout << "legnagyobb összefüggő sziget --> " << maxterulet << "  egység területű. " << endl;
	system("pause");
	return 0;
}