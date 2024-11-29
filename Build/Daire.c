#include "Daire.h"

Daireinfo* CircleCreate(Color color, float radius, float mesafe, float w, float parentX, float parentY) {
	Daireinfo* pYeniDaire = malloc(sizeof(Daireinfo));
	pYeniDaire->color = color;
	pYeniDaire->radius = radius;
	pYeniDaire->mesafe = mesafe;
	pYeniDaire->w = w * (PI / 2);
	pYeniDaire->angle = 0;
	pYeniDaire->x = parentX + mesafe * cos(pYeniDaire->angle);
	pYeniDaire->y = parentY + mesafe * sin(pYeniDaire->angle);
	return pYeniDaire;

}
	