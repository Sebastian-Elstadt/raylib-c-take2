#include "raylib.h"
#include "raymath.h"
#include "entity.h"

Entity *entities[MAX_ENTITIES];
int entity_count;

void InitEntities(void)
{
    entity_count = 0;
}

int RegisterEntity(Entity *entity)
{
    if (entity_count >= MAX_ENTITIES)
    {
        return -1;
    }

    entities[entity_count] = entity;
    return entity_count++;
}

void AddEntityForce(Entity *entity, Vector3 force)
{
    entity->accel = Vector3Add(entity->accel, force);
}

void UpdateEntities(void)
{
    for (int i = 0; i < entity_count; i++)
    {
        Entity *entity = entities[i];

        entity->vel = Vector3Add(entity->vel, entity->accel);

        float speed = Vector3Length(entity->vel);
        if (speed > entity->max_velocity)
        {
            entity->vel = Vector3Scale(Vector3Normalize(entity->vel), entity->max_velocity);
        }

        entity->pos = Vector3Add(entity->pos, entity->vel);
        entity->vel = Vector3Scale(entity->vel, entity->force_damping_factor);
        entity->accel = (Vector3){0.0f, 0.0f, 0.0f};
    }
}