#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "raymath.h"

#include "noise.h"

Vector2 V2_RandomGradient(int xi, int yi)
{
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = xi, b = yi;
    a *= 3284157443;

    b ^= a << s | a >> w - s;
    b *= 1911520717;

    a ^= b << s | b >> w - s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]

    // Create the vector from the angle
    Vector2 v;
    v.x = sin(random);
    v.y = cos(random);

    return v;
}

float DotGridGradient(int xi, int yi, float x, float y)
{
    Vector2 gradient = V2_RandomGradient(xi, yi);

    float dx = x - (float)xi;
    float dy = y - (float)yi;

    return (dx * gradient.x + dy * gradient.y);
}

float Interpolate(float a0, float a1, float w)
{
    return (a1 - a0) * (3.0f - w * 2.0f) * w * w + a0;
}

float Perlin(float x, float y)
{
    int x0 = (int)x;
    int y0 = (int)y;
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    float xf = x - (float)x0;
    float yf = y - (float)y0;

    float n0 = DotGridGradient(x0, y0, x, y);
    float n1 = DotGridGradient(x1, y0, x, y);
    float xi0 = Interpolate(n0, n1, xf);

    n0 = DotGridGradient(x0, y1, x, y);
    n1 = DotGridGradient(x1, y1, x, y);
    float xi1 = Interpolate(n0, n1, xf);

    float value = Interpolate(xi0, xi1, yf);
    return value;
}