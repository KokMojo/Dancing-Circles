#include <stdio.h>
#include "raylib.h"
#include "Liste.h"
#include "Daire.h"
#include <time.h>
﻿;


void mesafecizdirme(Liste* pListe) {
    Iterator* pIterator = IteratorYarat(pListe);
    float eskiX = 1200 / 2 + IteratorBilgi(pIterator)->x;
    float eskiY = 800 / 2 + IteratorBilgi(pIterator)->y;
    while (IteratorNext(pIterator)) {          //başa geldiğinde 0 verip döngüyü bitirenzi (aynı zamanda diğer iteratore de atlıyor)
        float yeniX = 1200 / 2 + IteratorBilgi(pIterator)->x;
        float yeniY = 800 / 2 + IteratorBilgi(pIterator)->y;
        DrawLine(eskiX, eskiY, yeniX, yeniY, BLACK);
        eskiX = yeniX;                     
        eskiY = yeniY;                  //eskilerin yerine yeniler kondu ki her merkez kendinden bir öncekiyle bağlansın(yoksa hepsi başlangıçla bağlı olurdu)
    
    }
    free(pIterator);

    
}

void dairecizdirme(Liste* pListe) {
    Iterator* pIterator = IteratorYarat(pListe);
    do {
        DrawCircle(600 + IteratorBilgi(pIterator)->x, 400 + IteratorBilgi(pIterator)->y, IteratorBilgi(pIterator)->radius, IteratorBilgi(pIterator)->color);

    } while (IteratorNext(pIterator));        //bütün merkezlere tek tek uğrayıp içerdikleri bilgilere göre daireyi  çizdirdik, listenin başına gelince de döngüyü kırdık
    free(pIterator);
}



void Action(Liste* pListe, float zaman) {
    Iterator* pIterator = IteratorYarat(pListe);            //başlangıç dairesini yarattık(yeri sabit)
    float beforeX = pIterator->pMerkez->pDairebilgi->x;
    float beforeY = pIterator->pMerkez->pDairebilgi->y;
    while (IteratorNext(pIterator)) {
        Daireinfo* pDaire = IteratorBilgi(pIterator);
        pDaire->angle = fmod(pDaire->angle + (pDaire->w * zaman),( 2 * PI));
        float afterX = beforeX + (cos(pDaire->angle) * pDaire->mesafe);
        float afterY = beforeY + (sin(pDaire->angle) * pDaire->mesafe);
        pDaire->x = afterX;                                 //her zaman aralığı için dairelerin verilerini güncelliyoruz
        pDaire->y = afterY;
        beforeX = afterX;
        beforeY = afterY;
    }
    free(pIterator);
}
void DaireEkle(Liste* pListe, Color color, float radius, float mesafe, float w) {
    float beforeX = 0.0f;
    float beforeY = 0.0f;
    if (pListe->elemansayısı != 0) {                      //dairenin verileri kendinden bir önceki daireye bağımlı
        beforeX = pListe->pFinish->pDairebilgi->x;
        beforeY = pListe->pFinish->pDairebilgi->y;
    }
    Daireinfo* pDaire = CircleCreate(color, radius, mesafe, w, beforeX, beforeY);
    ListeyeEkle(pListe, pDaire);
}

void DaireCıkar(Liste* pListe) {
    if (pListe->elemansayısı > 1) {                     
        ListedenCıkar(pListe);
    }

}


int main() {
    double lastTime = GetTime();  // Başlangıç zamanı
    double deltaT = 0;

    
    
    Color colors[19] = {
            BLACK,
            RED,
            GREEN,
            BLUE,
            YELLOW,
            ORANGE,
            PURPLE,
            MAROON,
            LIME,
            BROWN,
            PINK,
            VIOLET,
            BEIGE,
            GRAY,
            DARKGRAY,
            SKYBLUE,
            GOLD,
            MAGENTA,
            DARKBLUE
    };


    InitWindow(1200, 800, "Selim Emir Erol's Project");
    SetTargetFPS(60);
    Liste* pListe = ListeYarat();
    DaireEkle(pListe, GRAY, 10, 0, 0);

    deltaT = 0;

    while (!WindowShouldClose()) {
        DrawText("Press \"SPACE\" to Add Circle", 10, 10, 20, BLACK);
        DrawText("Press \"ENTER\" to Remove Circle", 10, 40, 20, BLACK);
        double currentTime = GetTime();
        deltaT = currentTime - lastTime;  // Zaman farkını hesapla
        lastTime = currentTime;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Action(pListe, deltaT);
        dairecizdirme(pListe);
        mesafecizdirme(pListe);

        if (IsKeyPressed(KEY_SPACE)) {
            Color randomColor = colors[rand() % (sizeof(colors) / sizeof(colors[0]))];
            float randomRadius = (rand() % 50 + 10) / 1.0f; // 10 ile 50 arasında yarıçap
            float randomMesafe = (rand() % 150 + 50) / 1.0f; // 50 ile 150 arasında mesafe
            float randomW = (rand() % 46 + 5) / 10.0f;  // 0.5 ile 5.0 arasında


            DaireEkle(pListe, randomColor, randomRadius, randomMesafe, randomW);

        }
        if (IsKeyPressed(KEY_ENTER)) {
            DaireCıkar(pListe);
        }

            
        
              
        EndDrawing();
        


    }
    CloseWindow();
    free(pListe);
    
    return 0;
}