#include "Liste.h"
Liste* ListeYarat() {
	Liste* pYeniListe = malloc(sizeof(Liste));
	pYeniListe->elemansayısı = 0;
		return pYeniListe;
}
void ListeyeEkle(Liste* pListebilgi, Daireinfo* pDairebilgi) {
	Merkez* pYeniDaire = malloc(sizeof(Merkez));
	if (pListebilgi->elemansayısı == 0) {
		pListebilgi->pStart = pYeniDaire;             //listenin başı,sonu ve büyüklüğünü ayarlandı
		pListebilgi->pFinish = pYeniDaire;
		pListebilgi->elemansayısı = 1;

		pYeniDaire->pBefore = pYeniDaire;
		pYeniDaire->pAfter = pYeniDaire;             //başıyla sonunu bağladık ve bilgilerini girdik
		pYeniDaire->pDairebilgi = pDairebilgi;
	}

	else {
		pYeniDaire->pAfter = pListebilgi->pStart;
		pYeniDaire->pBefore = pListebilgi->pFinish;   //yenidairemizi listeye bağladık
		pYeniDaire->pDairebilgi = pDairebilgi;

		pListebilgi->pStart->pBefore = pYeniDaire;
		pListebilgi->pFinish->pAfter = pYeniDaire;     //listenin başıyla sonunu yani daireye bağladık(circular)



		pListebilgi->pFinish = pYeniDaire;           //listenin son elemanı yapıdı ve eleman sayısı arttırıldı
		pListebilgi->elemansayısı += 1;



	}




}

void ListedenCıkar(Liste* pListebilgi) {
	if (pListebilgi->elemansayısı == 0) {
		return 0;
	}
	else if (pListebilgi->elemansayısı == 1) {
		free(pListebilgi->pFinish);
		pListebilgi->elemansayısı = 0;
		pListebilgi->pFinish = 0;
		pListebilgi->pStart = 0;
	}
	else {
		Merkez* pDecoy = pListebilgi->pFinish;
		

		pListebilgi->pFinish = pDecoy->pBefore;
		pDecoy->pBefore->pAfter = pDecoy->pAfter;
		pDecoy->pAfter->pBefore = pDecoy->pBefore;               //buraya bi tur daha bak
		pListebilgi->elemansayısı -= 1;

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