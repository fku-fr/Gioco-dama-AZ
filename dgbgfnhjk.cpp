/*Breve presentazione: Il codice di un semplice videogioco (dama) programmato interamente in c++. È un gioco da tavolo strategico implementato al computer, che permette al giocatore di sfidare un "bot". E' organizzato per
funzioni in modo da facilitare eventuali modifiche e renderlo più comprensibile.
Breve relazione: Ho optato per questo progetto per diverse ragioni. Primariamente, la dama costituisce una sfida stimolante dal punto di vista della programmazione che mi ha permesso di migliorare le mie competenze in c++.
In particolare l'uso delle funzioni, delle strutture, del colore dell'output, del casting, dei cicli iterativi, della gestione di file di testo, controlli efficaci degli input, gestione di numeri casuali e numerose altre
conoscenze.
Inoltre, il progetto mi ha permesso di sviluppare competenze trasversali (soft skills) come il problem solving, la capacità di pianificazione e organizzazione del lavoro, e l'attenzione ai dettagli.
Organizzare e il gioco nel suo complesso è stata, forse, una delle parti più complicate, così come risolvere i numerosissimi problemi che si sono verificati durante la programmazione. Ho cercato di creare un'applicazione
sia educativa che divertente usando logica e creatività.
Per provare il videogioco, è necessario inserire questo codice in un compilatore (disponibile anche online)*/
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <limits>
#include <random>
#include <time.h>
using namespace std;
const int nct=10;
struct mossa
{
int col;
int rig;
};
/*
ABBREVIAZIONI:
m_da = mossa da
m_a = mossa a
nct = numero caselle totale (+ bordi)
col = colonna
rig = riga
pla = giocatore (player)
bot = computer
GIOCATORE: char(169) = dama, char(79) = pedina
COMPUTER: char(184) = dama, char(157) = pedina
BORDO: char(158)
VUOTO: char(255)
*/
/*Funzione che controlla se una casella è nera (blu in output) o bianca*/
bool contr_nerobianco(int rig, int col)
{
	if ((rig % 2 == 0 && col % 2 == 0) || (rig % 2 == 1 && col % 2 == 1))
	{
		return true; /* casella nera*/
	}
	else
	{
		return false; /* casella bianca*/
	}
}

/* Funzione che stampa in output la scacchiera a colori*/
void stampascacchiera_vis(char scacchiera_o[][nct], HANDLE col)
{
	for (int i = 1; i < nct - 1; i++)
	{
		cout << "   " << i;
	}
	cout << endl;

	for (int i = 1; i < nct - 1; i++)
	{
		cout << "  ";
		for (int j = 1; j < nct - 1; j++)
		{
			if (contr_nerobianco(i, j) == true)
			{
				SetConsoleTextAttribute(col, 3);
			}
			else
			{
				SetConsoleTextAttribute(col, 7);
			}
			cout << char(218) << char(196) << char(191) << " ";
		}

		SetConsoleTextAttribute(col, 7);
		cout << endl;
		cout << i << " ";

		for (int j = 1; j < nct - 1; j++)
		{
			if (contr_nerobianco(i, j) == true)
			{
				SetConsoleTextAttribute(col, 3);
			}
			else
			{
				SetConsoleTextAttribute(col, 7);
			}
			cout << char(179);

			if (scacchiera_o[i][j] == char(79) || scacchiera_o[i][j] == char(169))
			{
				SetConsoleTextAttribute(col, 2);
			}
			else if ((scacchiera_o[i][j] == char(157) || scacchiera_o[i][j] == char(184)))
			{
				SetConsoleTextAttribute(col, 4);
			}
			else if (contr_nerobianco(i, j) == true)
			{
				SetConsoleTextAttribute(col, 3);
			}
			else
			{
				SetConsoleTextAttribute(col, 7);
			}
			cout << scacchiera_o[i][j];

			if (contr_nerobianco(i, j) == true)
			{
				SetConsoleTextAttribute(col, 3);
			}
			else
			{
				SetConsoleTextAttribute(col, 7);
			}
			cout << char(179) << " ";
		}
		cout << endl;
		cout << "  ";

		for (int j = 1; j < nct - 1; j++)
		{
			if (contr_nerobianco(i, j) == true)
			{
				SetConsoleTextAttribute(col, 3);
			}
			else
			{
				SetConsoleTextAttribute(col, 7);
			}
			cout << char(192) << char(196) << char(217) << " ";
		}
		cout << endl;
		SetConsoleTextAttribute(col, 7);
	}
}

/* Funzione che controlla, dato un array di mosse, se una determinata mossa gli appartiene*/
bool controlla_mossa_obbligata(char scacchiera[][nct], mossa m_tot[], int n, int rig, int col)
{
	for (int i = 0; i < n; i++)
	{
		if (m_tot[i].rig == rig && m_tot[i].col == col)
		{
			return true;
		}
	}
	return false;
}

/* Funzione che controlla se una posizione di input dell'utente è effettivamente la posizione di una sua pedina o dama*/
bool controlla_input2_pla(char scacchiera[][nct], int rig, int col)
{
	if (contr_nerobianco(rig, col) == true && (scacchiera[rig][col] == char(169) || scacchiera[rig][col] == char(79)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* Funzione che controlla se una pedina o dama non si può muovere*/
bool controlla_bloccato(char scacchiera[][nct], int rig, int col)
{
	if (scacchiera[rig][col] == char(79))
	{
		if ((scacchiera[rig - 1][col + 1] == char(250) || scacchiera[rig - 1][col - 1] == char(250)) || (scacchiera[rig - 1][col + 1] == char(157) && scacchiera[rig - 2][col + 2] == char(250)) || (scacchiera[rig - 1][col - 1] == char(157) && scacchiera[rig - 2][col - 2] == char(250)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (scacchiera[rig][col] == char(169))
	{
		if ((scacchiera[rig + 1][col + 1] == char(250) || scacchiera[rig + 1][col - 1] == char(250) || scacchiera[rig - 1][col + 1] == char(250) || scacchiera[rig - 1][col - 1] == char(250)) || (scacchiera[rig + 1][col + 1] == char(157) && scacchiera[rig + 2][col + 2] == char(250)) || (scacchiera[rig + 1][col - 1] == char(157) && scacchiera[rig + 2][col - 2] == char(250)) || (scacchiera[rig - 1][col + 1] == char(157) && scacchiera[rig - 2][col + 2] == char(250)) || (scacchiera[rig - 1][col - 1] == char(157) && scacchiera[rig - 2][col - 2] == char(250)) || (scacchiera[rig + 1][col + 1] == char(184) && scacchiera[rig + 2][col + 2] == char(250)) || (scacchiera[rig + 1][col - 1] == char(184) && scacchiera[rig + 2][col - 2] == char(250)) || (scacchiera[rig - 1][col + 1] == char(184) && scacchiera[rig - 2][col + 2] == char(250)) || (scacchiera[rig - 1][col - 1] == char(184) && scacchiera[rig - 2][col - 2] == char(250)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (scacchiera[rig][col] == char(157))
	{
		if ((scacchiera[rig + 1][col + 1] == char(250) || scacchiera[rig + 1][col - 1] == char(250)) || (scacchiera[rig + 1][col + 1] == char(79) && scacchiera[rig + 2][col + 2] == char(250)) || (scacchiera[rig + 1][col - 1] == char(79) && scacchiera[rig + 2][col - 2] == char(250)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if ((scacchiera[rig + 1][col + 1] == char(250) || scacchiera[rig + 1][col - 1] == char(250) || scacchiera[rig - 1][col + 1] == char(250) || scacchiera[rig - 1][col - 1] == char(250)) || (scacchiera[rig + 1][col + 1] == char(79) && scacchiera[rig + 2][col + 2] == char(250)) || (scacchiera[rig + 1][col - 1] == char(79) && scacchiera[rig + 2][col - 2] == char(250)) || (scacchiera[rig - 1][col + 1] == char(79) && scacchiera[rig - 2][col + 2] == char(250)) || (scacchiera[rig - 1][col - 1] == char(79) && scacchiera[rig - 2][col - 2] == char(250)) || (scacchiera[rig + 1][col + 1] == char(169) && scacchiera[rig + 2][col + 2] == char(250)) || (scacchiera[rig + 1][col - 1] == char(169) && scacchiera[rig + 2][col - 2] == char(250)) || (scacchiera[rig - 1][col + 1] == char(169) && scacchiera[rig - 2][col + 2] == char(250)) || (scacchiera[rig - 1][col - 1] == char(169) && scacchiera[rig - 2][col - 2] == char(250)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

/* Funzione che controlla se una pedina o dama del giocatore può mangiare qualcosa*/
bool controlla_mangiare_pla(char scacchiera[][nct], int rig, int col)
{
	bool mangiare = false;
	if (scacchiera[rig][col] == char(79))
	{
		if ((scacchiera[rig - 1][col - 1] == char(157) && scacchiera[rig - 2][col - 2] == char(250)) || (scacchiera[rig - 1][col + 1] == char(157) && scacchiera[rig - 2][col + 2] == char(250)))
		{
			mangiare = true;
		}
	}
	else if (scacchiera[rig][col] == char(169))
	{
		if ((scacchiera[rig - 1][col - 1] == char(157) && scacchiera[rig - 2][col - 2] == char(250)) || (scacchiera[rig - 1][col + 1] == char(157) && scacchiera[rig - 2][col + 2] == char(250)) || (scacchiera[rig + 1][col - 1] == char(157) && scacchiera[rig + 2][col - 2] == char(250)) || (scacchiera[rig + 1][col + 1] == char(157) && scacchiera[rig + 2][col + 2] == char(250)) || (scacchiera[rig - 1][col - 1] == char(184) && scacchiera[rig - 2][col - 2] == char(250)) || (scacchiera[rig - 1][col + 1] == char(184) && scacchiera[rig - 2][col + 2] == char(250)) || (scacchiera[rig + 1][col - 1] == char(184) && scacchiera[rig + 2][col - 2] == char(250)) || (scacchiera[rig + 1][col + 1] == char(184) && scacchiera[rig + 2][col + 2] == char(250)))
		{
			mangiare = true;
		}
	}
	return mangiare;
}

/* Funzione che permette al giocatore di selezionare una pedina da spostare*/
mossa input_selezione_pla(char scacchiera[][nct], HANDLE col)
{
	mossa m_da;

	int n_obbligate = 0;
	for (int i = 1; i < nct - 1; i++)
	{
		for (int j = 1; j < nct - 1; j++)
		{
			if (controlla_mangiare_pla(scacchiera, i, j) == true)
			{
				n_obbligate++;
			}
		}
	}

	mossa m_obbligate[n_obbligate];
	cin.clear();

	if (n_obbligate == 0)
	{
		do
		{
			cout << "Inserire la riga della casella in cui si trova la pedina che si desidera spostare: ";
			while (!(cin >> m_da.rig) || m_da.rig < 1 || m_da.rig > nct - 2)
			{
				SetConsoleTextAttribute(col, 4);
				cout << "Non valido. Inserire un numero intero da 1 a 8: ";
				SetConsoleTextAttribute(col, 7);

				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			cout << "Inserire la colonna della casella in cui si trova la pedina che si desidera spostare: ";
			while (!(cin >> m_da.col) || m_da.col < 1 || m_da.col > nct - 2)
			{
				SetConsoleTextAttribute(col, 4);
				cout << "Non valido. Inserire un numero intero da 1 a 8: ";
				SetConsoleTextAttribute(col, 7);

				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			SetConsoleTextAttribute(col, 4);
			if (controlla_input2_pla(scacchiera, m_da.rig, m_da.col) == false)
			{
				cout << "Non valido. Inserire la posizione di una pedina o dama del giocatore" << endl;
			}
			else if (controlla_bloccato(scacchiera, m_da.rig, m_da.col) == false)
			{
				cout << "Non valido. Pedina bloccata" << endl;
			}
			SetConsoleTextAttribute(col, 7);
		} while (controlla_input2_pla(scacchiera, m_da.rig, m_da.col) == false || controlla_bloccato(scacchiera, m_da.rig, m_da.col) == false);

		return m_da;
	}
	else
	{
		int n2 = 0;
		for (int i = 1; i < nct - 1; i++)
		{
			for (int j = 1; j < nct - 1; j++)
			{
				if (controlla_mangiare_pla(scacchiera, i, j) == true)
				{
					m_obbligate[n2].rig = i;
					m_obbligate[n2].col = j;
					n2++;
				}
			}
		}

		if (n_obbligate == 1)
		{
			SetConsoleTextAttribute(col, 14);
			cout << "Il giocatore deve mangiare. L'unica pedina selezionabile risulta essere quella in riga " << m_obbligate[0].rig << " e colonna " << m_obbligate[0].col << endl;
			m_da.rig = m_obbligate[0].rig;
			m_da.col = m_obbligate[0].col;
			SetConsoleTextAttribute(col, 7);
		}
		else
		{
			SetConsoleTextAttribute(col, 14);
			cout << "Il giocatore deve mangiare. Ci sono " << n_obbligate << " mosse disponibili. Inserirne una." << endl;
			SetConsoleTextAttribute(col, 7);

			do
			{
				cout << "Inserire la riga della casella in cui si trova la pedina che si desidera spostare: ";
				while (!(cin >> m_da.rig) || m_da.rig < 1 || m_da.rig > nct - 2)
				{
					SetConsoleTextAttribute(col, 14);
					cout << "Non valido. Inserire un numero intero da 1 a 8: ";
					SetConsoleTextAttribute(col, 7);

					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				cout << "Inserire la colonna della casella in cui si trova la pedina che si desidera spostare: ";
				while (!(cin >> m_da.col) || m_da.col < 1 || m_da.col > nct - 2)
				{
					SetConsoleTextAttribute(col, 4);
					cout << "Non valido. Inserire un numero intero da 1 a 8: ";
					SetConsoleTextAttribute(col, 7);

					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				SetConsoleTextAttribute(col, 4);
				if (controlla_input2_pla(scacchiera, m_da.rig, m_da.col) == false)
				{
					cout << "Non valido. Inserire la posizione di una pedina o dama del giocatore" << endl;
				}
				else if (controlla_mossa_obbligata(scacchiera, m_obbligate, n_obbligate, m_da.rig, m_da.col) == false)
				{
					cout << "Non valido. Inserire la posizione di una pedina o dama che possa mangiare una pedina avversaria" << endl;
				}
				SetConsoleTextAttribute(col, 7);
			} while (controlla_input2_pla(scacchiera, m_da.rig, m_da.col) == false || controlla_mossa_obbligata(scacchiera, m_obbligate, n_obbligate, m_da.rig, m_da.col) == false);
		}

		return m_da;
	}
}
/*Funzione che permette al giocatore di inserire la posizione in cui vuole spostare la pedina*/
mossa input_mossa_pla(char scacchiera[][nct], int rig1, int col1, HANDLE col)
{
	mossa m_a;

	if (controlla_mangiare_pla(scacchiera, rig1, col1) == true)
	{
		if (scacchiera[rig1][col1] == char(169))
		{
			do
			{
				cout << "Inserire la riga dove si desidera spostare la dama: ";
				while (!(cin >> m_a.rig) || m_a.rig < 1 || m_a.rig > nct - 2)
				{
					SetConsoleTextAttribute(col, 4);
					cout << "Non valido. Inserire un numero intero da 1 a 8: ";
					SetConsoleTextAttribute(col, 7);
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				cout << "Inserire la colonna dove si desidera spostare la pedina: ";
				while (!(cin >> m_a.col) || m_a.col < 1 || m_a.col > nct - 2)
				{
					SetConsoleTextAttribute(col, 4);
					cout << "Non valido. Inserire un numero intero da 1 a 8: ";
					SetConsoleTextAttribute(col, 7);
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				if (scacchiera[(rig1 + m_a.rig) / 2][(col1 + m_a.col) / 2] != char(184) && scacchiera[(rig1 + m_a.rig) / 2][(col1 + m_a.col) / 2] != char(157))
				{
					SetConsoleTextAttribute(col, 4);
					cout << "Il giocatore deve mangiare." << endl;
					SetConsoleTextAttribute(col, 7);
				}
			} while ((m_a.rig != rig1 + 2 && m_a.rig != rig1 - 2) || (scacchiera[m_a.rig][m_a.col] < char(250) || scacchiera[m_a.rig][m_a.col] > char(250)) || contr_nerobianco(m_a.rig, m_a.col) == false || (col1 != m_a.col - 2 && col1 != m_a.col + 2) || (scacchiera[(rig1 + m_a.rig) / 2][(col1 + m_a.col) / 2] != char(184) && scacchiera[(rig1 + m_a.rig) / 2][(col1 + m_a.col) / 2] != char(157)));
		}
		else
		{
			do
			{
				cout << "Inserire la riga dove si desidera spostare la pedina: ";
				while (!(cin >> m_a.rig) || m_a.rig < 1 || m_a.rig > nct - 2)
				{
					SetConsoleTextAttribute(col, 4);
					cout << "Non valido. Inserire un numero intero da 1 a 8: ";
					SetConsoleTextAttribute(col, 7);
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				cout << "Inserire la colonna dove si desidera spostare la pedina: ";
				while (!(cin >> m_a.col) || m_a.col < 1 || m_a.col > nct - 2)
				{
					SetConsoleTextAttribute(col, 4);
					cout << "Non valido. Inserire un numero intero da 1 a 8: ";
					SetConsoleTextAttribute(col, 7);
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				if (scacchiera[(rig1 + m_a.rig) / 2][(col1 + m_a.col) / 2] != char(157))
				{
					SetConsoleTextAttribute(col, 4);
					cout << "Il giocatore deve mangiare." << endl;
					SetConsoleTextAttribute(col, 7);
				}
			} while (m_a.rig != rig1 - 2 || (scacchiera[m_a.rig][m_a.col] < char(250) || scacchiera[m_a.rig][m_a.col] > char(250)) || contr_nerobianco(m_a.rig, m_a.col) == false || col1 != m_a.col + 2 && col1 != m_a.col - 2 || scacchiera[(rig1 + m_a.rig) / 2][(col1 + m_a.col) / 2] != char(157));
		}

		return m_a;
	}
	else
	{
		if (scacchiera[rig1][col1] == char(169))
		{
			do
			{
				cout << "Inserire la riga dove si desidera spostare la dama: ";
				while (!(cin >> m_a.rig) || m_a.rig < 1 || m_a.rig > nct - 2)
				{
					SetConsoleTextAttribute(col, 4);
					cout << "Non valido. Inserire un numero intero da 1 a 8: ";
					SetConsoleTextAttribute(col, 7);
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				cout << "Inserire la colonna dove si desidera spostare la pedina: ";
				while (!(cin >> m_a.col) || m_a.col < 1 || m_a.col > nct - 2)
				{
					SetConsoleTextAttribute(col, 4);
					cout << "Non valido. Inserire un numero intero da 1 a 8: ";
					SetConsoleTextAttribute(col, 7);
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				if ((m_a.rig != rig1 + 1 && m_a.rig != rig1 - 1) || (scacchiera[m_a.rig][m_a.col] < char(250) || scacchiera[m_a.rig][m_a.col] > char(250)) || contr_nerobianco(m_a.rig, m_a.col) == false || (col1 + 1 != m_a.col && col1 - 1 != m_a.col))
				{
					SetConsoleTextAttribute(col, 4);
					cout << "Mossa non valida." << endl;
					SetConsoleTextAttribute(col, 7);
				}
			} while ((m_a.rig != rig1 + 1 && m_a.rig != rig1 - 1) || (scacchiera[m_a.rig][m_a.col] < char(250) || scacchiera[m_a.rig][m_a.col] > char(250)) || contr_nerobianco(m_a.rig, m_a.col) == false || (col1 + 1 != m_a.col && col1 - 1 != m_a.col));
		}
		else
		{
			do
			{
				cout << "Inserire la riga dove si desidera spostare la pedina: ";
				while (!(cin >> m_a.rig) || m_a.rig < 1 || m_a.rig > nct - 2)
				{
					SetConsoleTextAttribute(col, 4);
					cout << "Non valido. Inserire un numero intero da 1 a 8: ";
					SetConsoleTextAttribute(col, 7);
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				cout << "Inserire la colonna dove si desidera spostare la pedina: ";
				while (!(cin >> m_a.col) || m_a.col < 1 || m_a.col > nct - 2)
				{
					SetConsoleTextAttribute(col, 4);
					cout << "Non valido. Inserire un numero intero da 1 a 8: ";
					SetConsoleTextAttribute(col, 7);
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				if (m_a.rig != rig1 - 1 || (scacchiera[m_a.rig][m_a.col] < char(250) || scacchiera[m_a.rig][m_a.col] > char(250)) || contr_nerobianco(m_a.rig, m_a.col) == false || (col1 != m_a.col + 1 && col1 != m_a.col - 1))
				{
					SetConsoleTextAttribute(col, 4);
					cout << "Mossa non valida." << endl;
					SetConsoleTextAttribute(col, 7);
				}
			} while (m_a.rig != rig1 - 1 || (scacchiera[m_a.rig][m_a.col] < char(250) || scacchiera[m_a.rig][m_a.col] > char(250)) || contr_nerobianco(m_a.rig, m_a.col) == false || (col1 != m_a.col + 1 && col1 != m_a.col - 1));
		}

		return m_a;
	}
}

/* Funzione che esegue la mossa selezionata dal giocatore*/
void esecuzione_mossa_pla(char s[][nct], mossa mda, mossa ma)
{
    if (s[mda.rig][mda.col] == char(169))
    {
        if (controlla_mangiare_pla(s, mda.rig, mda.col) == true)
        {
            s[mda.rig][mda.col] = char(250);
            s[ma.rig][ma.col] = char(169);
            s[(mda.rig + ma.rig) / 2][(mda.col + ma.col) / 2] = char(250);
        }
        else
        {
            s[mda.rig][mda.col] = char(250);
            s[ma.rig][ma.col] = char(169);
        }
    }
    else
    {
        if (controlla_mangiare_pla(s, mda.rig, mda.col) == true)
        {
            s[mda.rig][mda.col] = char(250);
            s[ma.rig][ma.col] = char(79);
            s[(mda.rig + ma.rig) / 2][(mda.col + ma.col) / 2] = char(250);
        }
        else
        {
            s[mda.rig][mda.col] = char(250);
            s[ma.rig][ma.col] = char(79);
        }
    }

    if (ma.rig == 1) /* fa diventare dame le pedine in base avversaria*/
    {
        s[ma.rig][ma.col] = char(169);
    }
}

/* Funzione che gestisce il turno del giocatore, facendogli mangiare fino a 3 volte con 1 pedina o dama se necessario*/
void turno_pla(char scacchiera[][nct], HANDLE col)
{
    mossa m_da, m_a;

    m_da = input_selezione_pla(scacchiera, col);
    m_a = input_mossa_pla(scacchiera, m_da.rig, m_da.col, col);

    if (controlla_mangiare_pla(scacchiera, m_da.rig, m_da.col) == true)
    {
        esecuzione_mossa_pla(scacchiera, m_da, m_a);
        stampascacchiera_vis(scacchiera, col);

        if (controlla_mangiare_pla(scacchiera, m_a.rig, m_a.col) == true)
        {
            SetConsoleTextAttribute(col, 14);
            cout << "Il giocatore deve mangiare nuovamente con il pezzo in riga " << m_a.rig << " e colonna " << m_a.col << endl;
            SetConsoleTextAttribute(col, 7);
            m_da.rig = m_a.rig;
            m_da.col = m_a.col;
            m_a = input_mossa_pla(scacchiera, m_da.rig, m_da.col, col);
            esecuzione_mossa_pla(scacchiera, m_da, m_a);
            stampascacchiera_vis(scacchiera, col);

            if (controlla_mangiare_pla(scacchiera, m_a.rig, m_a.col) == true)
            {
                SetConsoleTextAttribute(col, 14);
                cout << "Il giocatore deve mangiare nuovamente con il pezzo in riga " << m_a.rig << " e colonna " << m_a.col << endl;
                SetConsoleTextAttribute(col, 7);
                m_da.rig = m_a.rig;
                m_da.col = m_a.col;
                m_a = input_mossa_pla(scacchiera, m_da.rig, m_da.col, col);
                esecuzione_mossa_pla(scacchiera, m_da, m_a);
                stampascacchiera_vis(scacchiera, col);
            }
        }
    }
    else
    {
        esecuzione_mossa_pla(scacchiera, m_da, m_a);
        stampascacchiera_vis(scacchiera, col);
    }
}
/* Funzione che controlla se una posizione di input computer è effettivamente la posizione di una sua pedina o dama*/
bool controlla_input2_bot(char scacchiera[][nct], int rig, int col)
{
    if (contr_nerobianco(rig, col) == true && (scacchiera[rig][col] == char(157) || scacchiera[rig][col] == char(184)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* Funzione che controlla se una pedina o dama del computer può mangiare*/
bool controlla_mangiare_bot(char scacchiera[][nct], int rig, int col)
{
    bool mangiare = false;

    if (scacchiera[rig][col] == char(157))
    {
        if ((rig + 2 < nct && col - 2 >= 0 && scacchiera[rig + 1][col - 1] == char(79) && scacchiera[rig + 2][col - 2] == char(250)) ||(rig + 2 < nct && col + 2 < nct && scacchiera[rig + 1][col + 1] == char(79) && scacchiera[rig + 2][col + 2] == char(250)))
        {
            mangiare = true;
        }
    }
    else if (scacchiera[rig][col] == char(184))
    {
        if ((rig - 2 >= 0 && col - 2 >= 0 && scacchiera[rig - 1][col - 1] == char(79) && scacchiera[rig - 2][col - 2] == char(250)) ||(rig - 2 >= 0 && col + 2 < nct && scacchiera[rig - 1][col + 1] == char(79) && scacchiera[rig - 2][col + 2] == char(250)) ||(rig + 2 < nct && col - 2 >= 0 && scacchiera[rig + 1][col - 1] == char(79) && scacchiera[rig + 2][col - 2] == char(250)) ||(rig + 2 < nct && col + 2 < nct && scacchiera[rig + 1][col + 1] == char(79) && scacchiera[rig + 2][col + 2] == char(250)) ||(rig - 2 >= 0 && col - 2 >= 0 && scacchiera[rig - 1][col - 1] == char(169) && scacchiera[rig - 2][col - 2] == char(250)) ||(rig - 2 >= 0 && col + 2 < nct && scacchiera[rig - 1][col + 1] == char(169) && scacchiera[rig - 2][col + 2] == char(250)) ||(rig + 2 < nct && col - 2 >= 0 && scacchiera[rig + 1][col - 1] == char(169) && scacchiera[rig + 2][col - 2] == char(250)) ||(rig + 2 < nct && col + 2 < nct && scacchiera[rig + 1][col + 1] == char(169) && scacchiera[rig + 2][col + 2] == char(250)))
        {
            mangiare = true;
        }
    }

    return mangiare;
}

/* Funzione che permette al computer di selezionare una pedina o dama*/
mossa selezione_bot(char scacchiera[][nct])
{
    mossa m_da;
    int n_obbligate = 0;
    for (int i = 1; i < nct - 1; i++)
    {
        for (int j = 1; j < nct - 1; j++)
        {
            if ((scacchiera[i][j] == char(157) || scacchiera[i][j] == char(184)) && controlla_mangiare_bot(scacchiera, i, j) == true)
            {
                n_obbligate++;
            }
        }
    }
    mossa m_obbligate[n_obbligate];

    do
    {
        if (n_obbligate == 0)
        {
            for (int i = 1; i < nct - 2; i++)
            {
                if (scacchiera[nct - 3][i] == char(157) && controlla_bloccato(scacchiera, nct - 3, i) == true)
                {
                    m_da.rig = nct - 3;
                    m_da.col = i;
                    return m_da;
                }
            } /* se c'è una pedina vicino alla base del giocatore, la muove in base per fare una dama*/
            do
            {
                m_da.rig = rand() % (nct - 2) + 1; 
                m_da.col = rand() % (nct - 2) + 1;
            } while (controlla_input2_bot(scacchiera, m_da.rig, m_da.col) == false || controlla_bloccato(scacchiera, m_da.rig, m_da.col) == false);
        }
        else
        {
            int n2 = 0;
            for (int i = 1; i < nct - 1; i++)
            {
                for (int j = 1; j < nct - 1; j++)
                {
                    if (controlla_mangiare_bot(scacchiera, i, j) == true)
                    {
                        m_obbligate[n2].rig = i;
                        m_obbligate[n2].col = j;
                        n2++;
                    }
                }
            }

            if (n_obbligate == 1)
            {
                m_da.rig = m_obbligate[0].rig;
                m_da.col = m_obbligate[0].col;
            }
            else
            {
                m_da.rig = m_obbligate[rand() % n_obbligate].rig;
                m_da.col = m_obbligate[rand() % n_obbligate].col;
            }
        }
    } while (scacchiera[m_da.rig][m_da.col] != char(184) && rand() % 2 == 1); /* se non seleziona una dama ma una pedina, c'è un 50% di probabilità che rifaccia il processo*/
    return m_da;
}

/* Funzione che permette al computer selezionare la posizione in cui spostare la pedina o dama*/
mossa mossa_bot(char scacchiera[][nct], int rig, int col)
{
    mossa m_a;
    if (controlla_mangiare_bot(scacchiera, rig, col) == true)
    {
        cout << "Il computer mangia" << endl;
        if (scacchiera[rig][col] == char(184))
        {
            do
            {
                m_a.rig = rig + ((rand() % 2) * 2 - 1) * 2;
                m_a.col = col + ((rand() % 2) * 2 - 1) * 2;
            } while ((scacchiera[m_a.rig][m_a.col] < char(250) || scacchiera[m_a.rig][m_a.col] > char(250)) || m_a.rig > nct - 2 || m_a.rig < 1 || m_a.col > nct - 2 || m_a.col < 1 || (scacchiera[(rig + m_a.rig) / 2][(col + m_a.col) / 2] != char(79) && scacchiera[(rig + m_a.rig) / 2][(col + m_a.col) / 2] != char(169)));
        }
        else
        {
            do
            {
                m_a.rig = rig + 2;
                m_a.col = col + ((rand() % 2) * 2 - 1) * 2;
            } while ((scacchiera[m_a.rig][m_a.col] < char(250) || scacchiera[m_a.rig][m_a.col] > char(250)) || m_a.rig > nct - 2 || m_a.rig < 1 || m_a.col > nct - 2 || m_a.col < 1 || scacchiera[(rig + m_a.rig) / 2][(col + m_a.col) / 2] != char(79));
        }
        return m_a;
    }
    else
    {
        cout << "Il computer non mangia e muove" << endl;
        if (scacchiera[rig][col] == char(184))
        {
            do
            {
                m_a.rig = rig + ((rand() % 2) * 2 - 1);
                m_a.col = col + ((rand() % 2) * 2 - 1);
                if (scacchiera[m_a.rig + 1][m_a.col + 1] == char(169) || scacchiera[m_a.rig + 1][m_a.col - 1] == char(169) || scacchiera[m_a.rig - 1][m_a.col + 1] == char(169) || scacchiera[m_a.rig - 1][m_a.col - 1] == char(169))
                {
                    m_a.rig = rig + ((rand() % 2) * 2 - 1);
                    m_a.col = col + ((rand() % 2) * 2 - 1);
                } /* abbassa la probabilità di mosse "suicide"*/
            } while ((scacchiera[m_a.rig][m_a.col] < char(250) || scacchiera[m_a.rig][m_a.col] > char(250)) || m_a.rig > nct - 2 || m_a.rig < 1 || m_a.col > nct - 2 || m_a.col < 1);
        }
        else
        {
            do
            {
                m_a.rig = rig + 1;
                m_a.col = col + ((rand() % 2) * 2 - 1);
                if (scacchiera[m_a.rig + 1][m_a.col + 1] == char(169) || scacchiera[m_a.rig + 1][m_a.col - 1] == char(169) || scacchiera[m_a.rig - 1][m_a.col + 1] == char(169) || scacchiera[m_a.rig - 1][m_a.col - 1] == char(169) || scacchiera[m_a.rig - 1][m_a.col + 1] == char(79) || scacchiera[m_a.rig - 1][m_a.col - 1] == char(79))
                {
                    m_a.rig = rig + 1;
                    m_a.col = col + ((rand() % 2) * 2 - 1);
                } /* abbassa leggermente la probabilità di mosse "suicide"*/
            } while ((scacchiera[m_a.rig][m_a.col] < char(250) || scacchiera[m_a.rig][m_a.col] > char(250)) || m_a.rig > nct - 2 || m_a.rig < 1 || m_a.col > nct - 2 || m_a.col < 1);
        }
        return m_a;
    }
}

/* Funzione che esegue la mossa del computer muovendo la pedina o dama*/
void esecuzione_mossa_bot(char s[][nct], mossa mda, mossa ma)
{
    if (s[mda.rig][mda.col] == char(184))
    {
        if (controlla_mangiare_bot(s, mda.rig, mda.col) == true)
        {
            s[mda.rig][mda.col] = char(250);
            s[ma.rig][ma.col] = char(184);
            s[(mda.rig + ma.rig) / 2][(mda.col + ma.col) / 2] = char(250);
        }
        else
        {
            s[mda.rig][mda.col] = char(250);
            s[ma.rig][ma.col] = char(184);
        }
    }
    else
    {
        if (controlla_mangiare_bot(s, mda.rig, mda.col) == true)
        {
            s[mda.rig][mda.col] = char(250);
            s[ma.rig][ma.col] = char(157);
            s[(mda.rig + ma.rig) / 2][(mda.col + ma.col) / 2] = char(250);
        }
        else
        {
            s[mda.rig][mda.col] = char(250);
            s[ma.rig][ma.col] = char(157);
        }
    }

    if (ma.rig == nct - 2) /* fa diventare le pedine in base avversaria dame*/
        s[ma.rig][ma.col] = char(184);
}

/* Funzione che gestisce il turno del bot, mangiando fino a 3 volte con lo stesso pezzo se necessario*/
void turno_bot(char scacchiera[][nct])
{
    mossa m_da, m_a;
    m_da = selezione_bot(scacchiera);
    m_a = mossa_bot(scacchiera, m_da.rig, m_da.col);
    if (controlla_mangiare_bot(scacchiera, m_da.rig, m_da.col) == true)
    {
        esecuzione_mossa_bot(scacchiera, m_da, m_a);
        if (controlla_mangiare_bot(scacchiera, m_a.rig, m_a.col) == true)
        {
            m_da.rig = m_a.rig;
            m_da.col = m_a.col;
            m_a = mossa_bot(scacchiera, m_da.rig, m_da.col);
            esecuzione_mossa_bot(scacchiera, m_da, m_a);
            if (controlla_mangiare_bot(scacchiera, m_a.rig, m_a.col) == true)
            {
                m_da.rig = m_a.rig;
                m_da.col = m_a.col;
                m_a = mossa_bot(scacchiera, m_da.rig, m_da.col);
                esecuzione_mossa_bot(scacchiera, m_da, m_a);
            }
        }
    }
    else
    {
        esecuzione_mossa_bot(scacchiera, m_da, m_a);
    }
}

/* Funzione verifica se il giocatore o il computer non ha più pezzi in scacchiera e determina se qualcuno ha vinto*/
int condizione_fine(char scacchiera[][nct])
{
    bool giocatore = true;
    bool bot = true;

    for (int i = 1; i < nct - 1; i++)
    {
        for (int j = 1; j < nct - 1; j++)
        {
            if (scacchiera[i][j] == char(184) || scacchiera[i][j] == char(157))
            {
                giocatore = false;
            }

            if (scacchiera[i][j] == char(79) || scacchiera[i][j] == char(169))
            {
                bot = false;
            }
        }
    }

    if (giocatore == true) /* vince il giocatore*/
    {
        return 1;
	}
    else if (bot == true) /* vince il bot*/
    {
        return 2;
	}
    else/* nessuno ha ancora vinto*/
	{
        return 0;
	}
}
/* Funzione che apre un file dati.txt. Se non esiste lo crea. Lo legge e estrae il valore del precedente record e il suo autore. Se il giocatore ha ottenuto un nuovo record lo sostituisce a quello precedente. Informa inoltre il giocatore di ciò*/
void record(string nickname, int tempo, HANDLE col)
{
    ifstream file1;
    string nome1;
    int tempo1;
    file1.open("datirecord.txt");
    if (file1.good()) { /* Verifica se il file esiste e può essere letto*/
        file1 >> tempo1;
        file1 >> nome1;
    } else {
        nome1 = ""; /* Se il file non esiste o è vuoto, inizializza a stringa vuota*/
        tempo1 = -1; /* Inizializza a un valore non significativo*/
    }
    SetConsoleTextAttribute(col, 2);
    file1.close();
    if (tempo1 == -1 || nome1 == "")
    {
        ofstream file2("datirecord.txt");
        file2 << tempo << " " << nickname << endl;
        cout << "Congratulazioni " << nickname << "! Hai vinto in " << tempo << " secondi.";
        file2.close();
    }
    else if (tempo < tempo1)
    {
        ofstream file2;
        file2.open("datirecord.txt");
        file2 << tempo << " " << nickname << endl;
        cout << "Congratulazioni " << nickname << "! Hai vinto in " << tempo << " secondi, battendo il precedente record di " << tempo1 << " secondi, ottenuto da " << nome1;
        file2.close();
    }
    else
    {
        cout << "Congratulazioni " << nickname << "! Hai vinto in " << tempo << " secondi. Il record attuale risulta essere di " << tempo1 << " secondi, ottenuto da " << nome1;
    }
    SetConsoleTextAttribute(col, 7);
}

/* Funzione che gestisce l'alternarsi di turni tra giocatore e computer e gestisce la fine della partite. Fa inserire un nickname e calcola il tempo di esecuzione*/
void gioco(char scacchiera[][nct], HANDLE col)
{
    clock_t start, end;
    cout << "Inserire un nickname: ";
    string nickname;
    cin >> nickname;
    start = clock(); /*prende tempo inizio*/
    do
    {
        turno_pla(scacchiera, col);

        cout << "Premere INVIO per continuare...";
        cin.ignore();

        while (getchar() != '\n');
        if (condizione_fine(scacchiera) == 0)
        {

            turno_bot(scacchiera);
            stampascacchiera_vis(scacchiera, col);
        }
    } while (condizione_fine(scacchiera) == 0);
    if (condizione_fine(scacchiera) == 1)
    {
        end = clock(); /*prende tempo fine*/
        int tempo = ((double)(end - start)) / CLOCKS_PER_SEC; /*trova i secondi di esecuzione del programma*/
        record(nickname, tempo, col);
    }
    else
    {
        end = clock();
        cout << "Vince il computer";
    }
}

/* Funzione che "vuota" la scacchiera riempiendola di caratteri "bordo"*/
void vuotascacchiera(char scacchiera_o[][nct])	
{
    for (int i = 0; i < nct; i++)
    {
        for (int j = 0; j < nct; j++)
        {
            scacchiera_o[i][j] = char(158);
		}
	}
}

/* Funzione che posiziona le pedine e gli spazi vuoti nella scacchiera*/
void iniziascacchiera(char scacchiera_o[][nct])	
{
    for (int i = 1; i < nct - 1; i++)
    {

        for (int j = 1; j < nct - 1; j++)
        {
            if (contr_nerobianco(i, j) == true && i >= 6)
            {
                scacchiera_o[i][j] = char(79);
            }
            else if (contr_nerobianco(i, j) == true && i <= 3)
            {
                scacchiera_o[i][j] = char(157);
            }
            else
            {
                scacchiera_o[i][j] = char(250);
            }

        }	
	}
}

int main ()
{
    HANDLE col;
    col = GetStdHandle(STD_OUTPUT_HANDLE);
    char scacchiera[nct][nct];
    srand((unsigned)time(0));

    vuotascacchiera(scacchiera);
    iniziascacchiera(scacchiera);

    stampascacchiera_vis(scacchiera, col);
    gioco(scacchiera, col);
    return 0;
}
