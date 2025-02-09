#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

#define MAX_ENTITIES 1024

typedef struct Entity
{
    Vector3 pos;
    Vector3 vel;
    Vector3 accel;
    float force_damping_factor;
    float max_velocity;

    Vector3 forward;

    Model model;
    float model_scale;

    void (*Dispose)(struct Entity *self);
} Entity;

void InitEntities(void);
int RegisterEntity(Entity *entity);
void AddEntityForce(Entity *entity, Vector3 force);
void UpdateEntities(void);

#endif // ENTITY_H