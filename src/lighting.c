#include "raylib.h"
#include "lighting.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

Shader light_shader;

Light test;

void InitLighting(void)
{
    light_shader = LoadShader("shaders/lighting.vs", "shaders/lighting.fs");
    light_shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(light_shader, "viewPos");

    int ambient_light_loc = GetShaderLocation(light_shader, "ambient");
    SetShaderValue(light_shader, ambient_light_loc, (float[4]){0.9f, 0.9f, 0.9f, 1.0f}, SHADER_UNIFORM_VEC4);

    test = CreateLight(LIGHT_POINT, (Vector3){0.0f, 50.0f, 0.0f}, (Vector3){0.0f, 0.0f, 0.0f}, RED, light_shader);
}

void UpdateLighting(Camera *camera)
{
    float camera_pos[3] = {camera->position.x, camera->position.y, camera->position.z};
    SetShaderValue(light_shader, light_shader.locs[SHADER_LOC_VECTOR_VIEW], camera_pos, SHADER_UNIFORM_VEC3);

    UpdateLightValues(light_shader, test);
}

void ApplyLightingShader(Model *model)
{
    model->materials[0].shader = light_shader;
}

void DisposeLighting(void)
{
    UnloadShader(light_shader);
}