#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include "world.h"
#include "lighting.h"
#include "noise.h"

#define TERRAIN_WIDTH 1000.0f
#define TERRAIN_LENGTH 1000.0f

Model terrain_model;

void GenerateMap(void)
{


    Image height_map = GenImageColor(1000, 1000, BLACK);

    float scale = 100.0f;

    for (int y = 0; y < height_map.height; y++)
    {
        for (int x = 0; x < height_map.width; x++)
        {
            float xf = x / scale;
            float yf = y / scale;

            float val = Perlin(xf, yf);
            unsigned char color = (unsigned char)(((val + 1.0f) * 0.5f) * 255);
            ((Color *)height_map.data)[y * height_map.width + x] = (Color){color, color, color, 255};
        }
    }

    ExportImage(height_map, "noise.png");

    Mesh terrain_mesh = GenMeshHeightmap(height_map, (Vector3){TERRAIN_WIDTH, 100.0f, TERRAIN_LENGTH});
    terrain_model = LoadModelFromMesh(terrain_mesh);

    ApplyLightingShader(&terrain_model);

    UnloadImage(height_map);
}

void InitWorld(void)
{
    GenerateMap();
}

void DrawWorldTerrain(void)
{
    DrawModel(terrain_model, (Vector3){-(TERRAIN_WIDTH / 2.0f), 0.0f, -(TERRAIN_LENGTH / 2.0f)}, 1.0f, WHITE);
}

void DisposeWorld(void)
{
    UnloadModel(terrain_model);
}