#ifndef GAME_MATH_H
#define GAME_MATH_H

#include "raylib.h"
#include "raymath.h"

Vector3 V3_CalculateForward(Vector3 pos, Vector3 target);
Vector3 V3_CalculateRight(Vector3 forward, Vector3 up);

#endif // GAME_MATH_H