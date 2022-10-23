#define _CRT_SECURE_NO_WARNINGS
#define duzineImenaIPrezimena 64
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

#pragma region Strukture
typedef struct Osoba* Sljedeca;
struct Osoba {
	char _ime[duzineImenaIPrezimena];
	char _prezime[duzineImenaIPrezimena];
	int _godina_rodenja;
	Sljedeca _sljedecaOsoba;
};
#pragma endregion

#pragma region Definicije funkcija
int DodajNaPocetak(char*, char*, int, Sljedeca);
int DodajNaPoziciju(char*, char*, int, Sljedeca);
int Ispisi(Sljedeca);
int DodajNaKraj(Sljedeca);
Sljedeca PronadjiUListiPoPrezimenu(char*, Sljedeca);
Sljedeca PronadjiUListiPokazivaNaPrezime(char*, Sljedeca);
int IzbrisiPoPrezimenu(char*, Sljedeca);
#pragma endregion

int main()
{
	struct Osoba Head;
	int izbor = 0;
	Head._sljedecaOsoba = NULL;
	char ime[duzineImenaIPrezimena] = "";
	char prezime[duzineImenaIPrezimena] = "";
	int godinaRodjenja = 0;
	printf("Izaberite koju funkciju zelite izabrati:\n1-Dodaj na pocetak\n2-Ispisi listu\n3-Dodaj na kraj\n4-Pronadi po prezimenu\n5-Obrisi iz liste\n Za izlaz izabrati 0\n");
	scanf("%d", &izbor);
	while (izbor) {
		switch (izbor) {
		case 1:
			printf("Upisi ime, prezime i godinu rodjenja osobe: ");
			scanf("%s %s %d", &ime, &prezime, &godinaRodjenja);
			if (DodajNaPocetak(ime, prezime, godinaRodjenja, &Head))
				printf("Osoba uspjesno dodana na pocetak liste\n");
			break;
		case 2:
			Ispisi(&Head);
			break;

		case 3:
			printf("Upisi ime, prezime i godinu rodjenja osobe: ");
			scanf("%s %s %d", &ime, &prezime, &godinaRodjenja);
			if (DodajNaKraj(ime, prezime, godinaRodjenja, &Head))
				printf("Osoba uspjesno dodana na kraj liste\n");
			break;
		case 4:
			printf("Upisi prezime osobe koje zelis pronaci: ");
			scanf("%s", prezime);
			if (PronadjiUListiPoPrezimenu(prezime, &Head) == NULL) {
				printf("Osoba koju trazite nije u listi!\n");
			}
			else {
				printf("Osoba koju trazite je u listi!\n");
			}
			break;
		case 5:
			printf("Upisi prezime osobe koje zelis pronaci: ");
			scanf("%s", prezime);
			IzbrisiPoPrezimenu(prezime, &Head);
			break;
		}
		printf("Izaberite koju funkciju zelite izabrati:\n1-Dodaj na pocetak\n2-Ispisi listu\n3-Dodaj na kraj\n4-Pronadi po prezimenu\n5-Obrisi iz liste\n Za izlaz izabrati 0\n");
		scanf("%d", &izbor);
	}
}

#pragma region Funkcije
int DodajNaPocetak(char* ime, char* prezime, int godina_rodenja, Sljedeca S) {
	if (!(S->_godina_rodenja > 1000 && S->_godina_rodenja < 9999))
		DodajNaPoziciju(ime, prezime, godina_rodenja, S);
	return 1;
}

int DodajNaPoziciju(char* ime, char* prezime, int godina_rodenja, Sljedeca S) {
	Sljedeca osoba = (Sljedeca)malloc(sizeof(struct Osoba));
	strncpy(osoba->_ime, ime, duzineImenaIPrezimena);
	osoba->_ime[duzineImenaIPrezimena - 1] = '\0';
	strncpy(osoba->_prezime, prezime, duzineImenaIPrezimena);
	osoba->_prezime[duzineImenaIPrezimena - 1] = '\0';
	osoba->_godina_rodenja = godina_rodenja;
	osoba->_sljedecaOsoba = S->_sljedecaOsoba;
	S->_sljedecaOsoba = osoba;
	return 0;
}

int Ispisi(Sljedeca S) {
	Sljedeca osoba = S->_sljedecaOsoba;
	if (S->_godina_rodenja > 1000 && S->_godina_rodenja < 9999)
		printf("%s %s %d \n", S->_ime, S->_prezime, S->_godina_rodenja);//"%s %s %d", S->_ime, S->_prezime, S->_godina_rodenja
	if (osoba != NULL) {
		Ispisi(osoba);
	}
	return 0;
}

int DodajNaKraj(char* ime, char* prezime, int godina_rodenja, Sljedeca S) {
	if (S->_sljedecaOsoba == NULL)
		DodajNaPoziciju(ime, prezime, godina_rodenja, S);
	else
		DodajNaKraj(ime, prezime, godina_rodenja, S->_sljedecaOsoba);
}

Sljedeca PronadjiUListiPoPrezimenu(char* prezime, Sljedeca S) {
	if (!strcmp(S->_prezime, prezime)) {
		return S;
	}
	else {
		if (S->_sljedecaOsoba != NULL) {
			PronadjiUListiPoPrezimenu(prezime, S->_sljedecaOsoba);
		}
		else {
			return NULL;
		}
	}
}

Sljedeca PronadjiUListiPokazivaNaPrezime(char* prezime, Sljedeca S) {
	if (!strcmp(S->_sljedecaOsoba->_prezime, prezime)) {
		return S;
	}
	else {
		if (S->_sljedecaOsoba != NULL) {
			PronadjiUListiPokazivaNaPrezime(prezime, S->_sljedecaOsoba);
		}
		else {
			return NULL;
		}
	}
}

int IzbrisiPoPrezimenu(char* prezime, Sljedeca S) {
	Sljedeca trazeni = PronadjiUListiPoPrezimenu(prezime, S);
	if (trazeni == NULL) {
		printf("Osoba sa tim prezimenom nije u listi\n!");
	}
	else {
		Sljedeca prijeTrazenoga = PronadjiUListiPokazivaNaPrezime(prezime, S);
		prijeTrazenoga->_sljedecaOsoba = trazeni->_sljedecaOsoba;
		trazeni->_sljedecaOsoba = NULL;
		printf("Osoba je izbrisana iz liste!\n");
	}
}
#pragma endregion
