#include "raylib.h"
#include "raymath.h"
#include "game_math.h"

Vector3 V3_CalculateForward(Vector3 pos, Vector3 target)
{
    return Vector3Normalize(Vector3Subtract(target, pos));
}

Vector3 V3_CalculateRight(Vector3 forward, Vector3 up)
{
    return Vector3Normalize(Vector3CrossProduct(forward, up));
}