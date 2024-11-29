#include "Liste.h"
Liste* ListeYarat() {
	Liste* pYeniListe = malloc(sizeof(Liste));
	pYeniListe->elemansay�s� = 0;
		return pYeniListe;
}
void ListeyeEkle(Liste* pListebilgi, Daireinfo* pDairebilgi) {
	Merkez* pYeniDaire = malloc(sizeof(Merkez));
	if (pListebilgi->elemansay�s� == 0) {
		pListebilgi->pStart = pYeniDaire;             //listenin ba��,sonu ve b�y�kl���n� ayarland�
		pListebilgi->pFinish = pYeniDaire;
		pListebilgi->elemansay�s� = 1;

		pYeniDaire->pBefore = pYeniDaire;
		pYeniDaire->pAfter = pYeniDaire;             //ba��yla sonunu ba�lad�k ve bilgilerini girdik
		pYeniDaire->pDairebilgi = pDairebilgi;
	}

	else {
		pYeniDaire->pAfter = pListebilgi->pStart;
		pYeniDaire->pBefore = pListebilgi->pFinish;   //yenidairemizi listeye ba�lad�k
		pYeniDaire->pDairebilgi = pDairebilgi;

		pListebilgi->pStart->pBefore = pYeniDaire;
		pListebilgi->pFinish->pAfter = pYeniDaire;     //listenin ba��yla sonunu yani daireye ba�lad�k(circular)



		pListebilgi->pFinish = pYeniDaire;           //listenin son eleman� yap�d� ve eleman say�s� artt�r�ld�
		pListebilgi->elemansay�s� += 1;



	}




}

void ListedenC�kar(Liste* pListebilgi) {
	if (pListebilgi->elemansay�s� == 0) {
		return 0;
	}
	else if (pListebilgi->elemansay�s� == 1) {
		free(pListebilgi->pFinish);
		pListebilgi->elemansay�s� = 0;
		pListebilgi->pFinish = 0;
		pListebilgi->pStart = 0;
	}
	else {
		Merkez* pDecoy = pListebilgi->pFinish;
		

		pListebilgi->pFinish = pDecoy->pBefore;
		pDecoy->pBefore->pAfter = pDecoy->pAfter;
		pDecoy->pAfter->pBefore = pDecoy->pBefore;               //buraya bi tur daha bak
		pListebilgi->elemansay�s� -= 1;

		free(pDecoy);
	}
}


Iterator* IteratorYarat(Liste* pListe) {
	Iterator* pYeniIterator = malloc(sizeof(Iterator));

	pYeniIterator->pListe = pListe;
	pYeniIterator->pMerkez = pYeniIterator->pListe->pStart;
	return pYeniIterator;
}

Daireinfo* IteratorBilgi(Iterator* pIterator) {
	return pIterator->pMerkez->pDairebilgi;
}
int IteratorNext(Iterator* pIterator) {
	pIterator->pMerkez = pIterator->pMerkez->pAfter;
	if (pIterator->pMerkez == pIterator->pListe->pStart) {
		return 0;
	}
	else {
		return 1;
	}
}
int IteratorBefore(Iterator* pIterator) {
	pIterator->pMerkez = pIterator->pMerkez->pBefore;
	if (pIterator->pMerkez == pIterator->pListe->pFinish) {
		return 0;
	}
	else return 1;
}