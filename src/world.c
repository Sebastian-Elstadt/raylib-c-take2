#include "raylib.h"

#include "world.h"
#include "lighting.h"
#include "noise.h"

#define TERRAIN_WIDTH 10000.0f
#define TERRAIN_LENGTH 10000.0f

Model terrain_model;

void GenerateMap(void)
{
    Image height_map = GenImageColor(2048, 2048, BLACK);

    int grid_size = 250;

    for (int y = 0; y < height_map.height; y++)
    {
        for (int x = 0; x < height_map.width; x++)
        {
            float val = 0.0f;
            float freq = 1.0f;
            float amp = 1.0f;

            for (int i = 0; i < 12; i++)
            {
                val += Perlin(x * freq / grid_size, y * freq / grid_size) * amp;
                freq *= 1.5f;
                amp /= 2.0f;
            }

            val *= 0.8f; // contrast

            if (val > 1.0f)
            {
                val = 1.0f;
            }
            else if (val < -1.0f)
            {   
                val = -1.0f;
            }

            unsigned char color = (unsigned char)(((val + 1.0f) * 0.5f) * 255);

            ((Color *)height_map.data)[y * height_map.width + x] = (Color){color, color, color, 255};
        }
    }

    ExportImage(height_map, "noise.png");

    Mesh terrain_mesh = GenMeshHeightmap(height_map, (Vector3){TERRAIN_WIDTH, 1000.0f, TERRAIN_LENGTH});
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