#pragma once
#include "Daire.h"
#include <stdlib.h>
typedef struct Merkez {
	struct Merkez* pBefore;
	struct Daireinfo* pDairebilgi;
	struct Merkez* pAfter;
}Merkez;
typedef struct Liste {
	Merkez* pStart;
	int elemansay�s�;
	Merkez* pFinish;
}Liste;
Liste* ListeYarat();
void ListeyeEkle(Liste* pListebilgi, Daireinfo* pDairebilgi);
void ListedenC�kar(Liste* pListebilgi);


typedef struct Iterator {
	Merkez* pMerkez;
	Liste* pListe;
}Iterator;
Iterator* IteratorYarat(Liste* pListe);
int IteratorNext(Iterator* pIterator);
int IteratorBefore(Iterator* pIterator);
Daireinfo* IteratorBilgi(Iterator* pIterator);