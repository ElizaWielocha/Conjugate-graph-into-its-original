#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<iterator>
#include<algorithm>
#include <cstdlib>
using namespace std;


vector<vector<int>> wierzcholki;     // lista wierzcholkow g. wejsc.
vector<vector<int>> krawedzie;       // oryginalny graf

int counter = 0; // do zliczania wierzcholkow g. wejsc.
int zmiana = 1; // do nadania wartosci g. oryginal.

void wyswietl()
{
    int p = 1;     // pozycja
    for(int i = 0; i < counter; i++)
    {
        cout << p << " --> ";
        for(int j = 1; j < wierzcholki[i].size(); j++)
        {
            cout << wierzcholki[i][j] << " ";
        }
        p++;
        cout << endl;
    }
}

void wczytaj(string f)
{
    fstream plik1;
    string p1 = f + ".txt";     // plik wejsciowy

    vector <int> nastepniki;    // lista nastepnikow danego wierzcholka

    plik1.open(p1, ios::in);
    int kontener;

    if(plik1.good() == false)
    {
        cout << "Brak pliku do odczytu" << endl;
    }

    while (plik1.good() == true)
    {
        plik1 >> kontener;      // wczytuje po jednej liczbie

        while (kontener != 0)
        {
            nastepniki.push_back(kontener);     // dodaje do nastepnikow

            plik1 >> kontener;
            if(kontener == 0)
            {
                counter++;
                wierzcholki.push_back(nastepniki);  // nastepniki dodaje do danego wierzcholka
                nastepniki.clear();
                break;
            }
        }
        if(kontener == '|')
        {
            plik1.close();
        }

    }

    cout << endl << "Liczba wierzcholkow grafu wejsciowego: " << counter << endl;   // wyswoetla ile wierzcholkow ma graf
    cout << endl;
}

int czy_sprzezony()
{
	int w1, w2;           //
	int blad;
	int taki_sam = 0;     // z
	cout << "Czy graf jest sprzezony?" << endl;

	for (int i = 0; i < counter; i++)
    {
		for (int j = i+1; j < counter; j++)   //
		{
			for (int a = 1; a < wierzcholki[i].size(); a++)
			{
				for(int b = 1; b < wierzcholki[j].size(); b++)  //
				{
					if (wierzcholki[i][a] == wierzcholki[j][b])  //
					{
						w1 = i;
						w2 = j;    //
						if (wierzcholki[w1].size() == wierzcholki[w2].size())
						{
							for(int y = 1; y < wierzcholki[w1].size(); y++)
							{
                                blad = wierzcholki[w1][y];
                                for(int x = 1; x < wierzcholki[w2].size(); x++)
                                {
                                    if (blad == wierzcholki[w2][x])   //
                                    {
                                        taki_sam = 1;
                                    }
                                }
							}
							if (taki_sam == 0)
							{
								cout << "NIE :(" << endl;  //
                                return 0;
							}

						}
						else  //
						{
							cout << "NIE :(" << endl;  //
							return 0;
						}
					}
				}
			}
		}
    }
    cout << "TAK :)" << endl;
    return 1;

}

bool czy_liniowy()
{

    int nastepnik1;
    int nastepnik2;
    cout << "Czy graf jest liniowy?" << endl;

	for (int i = 0; i < counter; i++)
	{
		for (int j = 1; j < wierzcholki[i].size()-1; j++)
		{
			for (int k = 2; k < wierzcholki[i].size(); k++)  //
			{
				if (wierzcholki[i][j] && wierzcholki[i][k])
				{
					nastepnik1 = wierzcholki[i][j];
					nastepnik2 = wierzcholki[i][k];    //

					for (int a = 1; a <= wierzcholki[nastepnik1 - 1].size()-1; a++)
					{
						for (int b = 1; b <= wierzcholki[nastepnik2 - 1].size()-1; b++)   //
						{
							if (wierzcholki[nastepnik1-1][a] == wierzcholki[nastepnik2-1][b]) //
							{
								cout << "NIE :(" << endl;
								return false;
							}
						}
					}
				}
			}
		}
	}
/*
    int zmienna1;
   // int zmienna2;

    // trzecia struktura
    for(int i = 0; i < counter; i++)
    {
        for(int j = 1 ;j < wierzcholki[i].size(); j++)
        {
            zmienna1= wierzcholki[i][j];        // zapisuje nastepnik do zmiennej
            for(int x = 0; x < wierzcholki[zmienna1-1].size(); x++)   // przechodzi po wierzcholku nastepnika - 1
            {
                if(wierzcholki[zmienna1-1][x] == wierzcholki[i][0])
                {
                    for(int y = 0; y < wierzcholki[i].size(); y++)
                    {
                        if(wierzcholki[i][y] == wierzcholki[i][0])
                        {
                            for(int z = 0; z < wierzcholki[zmienna1-1].size(); z++)
                            {
                                if(wierzcholki[zmienna1].size() == wierzcholki[zmienna1-1][0])
                                {
                                    cout << "NIE :(" << endl;
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
    } */

	cout << "TAK :)"<< endl;
	return true;
}


int czy_one()
{
    cout << "Czy to jest jeden - graf?" << endl;
	int blad;
	for (int i = 0; i < counter; i++)
	{
		for (int j = 1; j < wierzcholki[i].size()-1; j++)
		{
			for (int k = j + 1; k < wierzcholki[i].size(); k++)
			{
				if (wierzcholki[i][j] == wierzcholki[i][k])  // sprawdza czy sa dwa takie same nastepniki w jednym wierzcholku
				{
					cout << "NIE :(" << endl;
					return 0;
				}

			}
		}
	}
	cout << "TAK :)" << endl;
	return 1;
}

void transformacja()
{
	int a = 1;
	int b = 1;
	int c = 2;

	for (int i = 0; i < counter; i++)  //
	{
		vector <int> pomocnicza;
		pomocnicza.push_back(a);
		pomocnicza.push_back(b);
		pomocnicza.push_back(c);

		krawedzie.push_back(pomocnicza);


		a++;
		b = b + 2;
		c = c + 2;

	}



	int w1, w2, w3;

	for (int i = 0; i < counter; i++)
    {
		for (int j = 1; j < wierzcholki[i].size(); j++)
		{
			w1 = wierzcholki[i][j];    //
			w3 = krawedzie[i][2];
			w2 = krawedzie[w1 - 1][1];  //
			krawedzie[w1 - 1][1] = w3;                    //

			for (int k = 0; k < counter; k++)   //
            {
                if (krawedzie[k][1] == w2)
                {
                    krawedzie[k][1] = w3;
                }
                if (krawedzie[k][2] == w2)
                {
                    krawedzie[k][2] = w3;
                }
            }
		}
    }

    // zmiana = 1;
	for (int i = 0; i < counter; i++)
	{
		for (int j = 1; j < krawedzie[i].size(); j++)
		{
		    if(krawedzie[i][j] == zmiana)
            {
                zmiana++;
            }
			if (krawedzie[i][j] > zmiana)
			{
				int schowek = krawedzie[i][j];
				for (int a = 0; a < counter; a++)
				{
					for (int b = 1; b <= 2; b++)
					{
						if (krawedzie[a][b] == schowek)
						{
							krawedzie[a][b] = zmiana;
						}
					}
				}
				zmiana++;
			}
		}
	}

	cout << "Transformacja: " << endl;
	for (int i = 1; i < zmiana; i++)
		{
			cout << i << " --> ";
			for (int j = 0; j < counter; j++)
			{
				if (krawedzie[j][1] == i)
				{
					cout << krawedzie[j][2] << " ";
				}
			}
			cout << endl;
		}

}

void zapisz()
{

	ofstream plik2;
	string p2;

	cout << endl << "Podaj nazwe pliku do zapisania: ";
	cin >> p2;                                               // plik do zapisu
	p2 += ".txt";
	plik2.open(p2.c_str());

	if (plik2.good() == true)
	{

		for (int i = 1; i < zmiana; i++)    // zmiana = ilosc wierzcholkow w grafie oryginalnym
		{
			plik2 << i << " ";

			for (int j = 0; j < counter; j++)
			{
				if (krawedzie[j][1] == i)
				{
					plik2 << krawedzie[j][2] << " ";
				}

			}
			plik2 << "0" << endl;
		}
		plik2 << "|" << endl;

		cout << "GOTOWE!" << endl;
		cout << "Zapisano w pliku " << p2 <<endl;
	}
	else cout << "Blad! " << endl;

}


int main()
{
    string f;

    cout << "Podaj nazwe pliku do odczytu: ";
    cin >> f;
    wczytaj(f);
    wyswietl();
    cout << endl;
    czy_one();
    cout << endl;
    if(czy_sprzezony() == 1)
    {
        cout << endl;
        czy_liniowy();
        cout << endl;
        transformacja();
        cout << endl;
        zapisz();
    }
	else
    {
        cout << endl;
        cout << "Nie mozna transformowac!" << endl;
        exit(0);
    }


}
