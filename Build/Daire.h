#pragma once
#include <stdlib.h>
#include <math.h>
#include "raylib.h"

typedef struct Daireinfo {
	Color color;
	float radius;
	float mesafe;
	float w;
	float angle;
	float x;
	float y;
}Daireinfo;

Daireinfo* CircleCreate(Color color, float radius, float mesafe, float w, float parentX, float parentY);
