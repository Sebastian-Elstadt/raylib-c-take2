#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "raylib.h"

#include "entity.h"
#include "player.h"
#include "world.h"
#include "lighting.h"

void Initialize(void)
{
    InitLighting();
    InitEntities();
    InitPlayer();
    InitWorld();
}

void Update(void)
{
    UpdatePlayer();

    UpdateEntities();

    UpdatePlayerCamera();
    UpdateLighting(&player.camera);
}

void Draw(void)
{
    BeginDrawing();

    ClearBackground(BLUE);

    BeginMode3D(player.camera);

    UpdateProjectionMatrix();
    DrawWorldTerrain();

    EndMode3D();

    DrawFPS(10, 10);

    EndDrawing();
}

void Dispose(void)
{   
    DisposeWorld();
    DisposeLighting();
}

int main(void)
{
    srand((unsigned int)time(NULL));

    InitWindow(800, 600, "rpgray");
    SetTargetFPS(144);
    DisableCursor();

    Initialize();

    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }

    Dispose();

    CloseWindow();
    return 0;
}