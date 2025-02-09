#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "entity.h"

typedef struct {
    Camera camera;
    Entity entity;
} Player;

extern Player player;

void InitPlayer(void);
void UpdatePlayer(void);
void UpdatePlayerCamera(void);
void UpdateProjectionMatrix(void);

#endif // PLAYER_H