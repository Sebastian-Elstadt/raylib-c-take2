#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include "player.h"
#include "game_math.h"
#include "entity.h"

const float PLAYER_HEIGHT = 1.0f;
const float PLAYER_MOVE_SPEED = 100.0f;
const float PLAYER_LOOK_SENSITIVITY = 0.003f;

Player player;

void InitPlayer(void)
{
    player.camera = (Camera){0};
    player.camera.position = (Vector3){0.0f, 100.0f + PLAYER_HEIGHT, 0.0f};
    player.camera.target = (Vector3){0.0f, PLAYER_HEIGHT, 1.0f};
    player.camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    player.camera.fovy = 65.0f;
    player.camera.projection = CAMERA_PERSPECTIVE;

    player.entity.pos = (Vector3){0.0f, 100.0f, 0.0f};
    player.entity.forward = V3_CalculateForward(player.entity.pos, player.camera.target);
    player.entity.force_damping_factor = 0.9f;
    player.entity.max_velocity = 10.0f;

    RegisterEntity(&player.entity);
}

void UpdatePlayer(void)
{
    if (IsKeyDown(KEY_W))
    {
        AddEntityForce(&player.entity, Vector3Scale(player.entity.forward, PLAYER_MOVE_SPEED * GetFrameTime()));
    }

    if (IsKeyDown(KEY_S))
    {
        AddEntityForce(&player.entity, Vector3Scale(player.entity.forward, -PLAYER_MOVE_SPEED * GetFrameTime()));
    }

    Vector3 right = V3_CalculateRight(player.entity.forward, player.camera.up);

    if (IsKeyDown(KEY_A))
    {
        AddEntityForce(&player.entity, Vector3Scale(right, -PLAYER_MOVE_SPEED * GetFrameTime()));
    }

    if (IsKeyDown(KEY_D))
    {
        AddEntityForce(&player.entity, Vector3Scale(right, PLAYER_MOVE_SPEED * GetFrameTime()));
    }

    Vector2 mouse_delta = GetMouseDelta();
    float yaw = mouse_delta.x * PLAYER_LOOK_SENSITIVITY;
    float pitch = mouse_delta.y * PLAYER_LOOK_SENSITIVITY;

    if (pitch > PI / 2.0f - 0.1f)
    {
        pitch = PI / 2.0f - 0.1f;
    }
    else if (pitch < -PI / 2.0f + 0.1f)
    {
        pitch = PI / 2.0f + 0.1f;
    }

    Matrix rotation_yaw = MatrixRotateY(-yaw);
    player.entity.forward = Vector3Transform(player.entity.forward, rotation_yaw);

    right = V3_CalculateRight(player.entity.forward, player.camera.up);

    Matrix rotation_pitch = MatrixRotate(right, -pitch);
    player.entity.forward = Vector3Normalize(Vector3Transform(player.entity.forward, rotation_pitch));
}

void UpdatePlayerCamera(void)
{
    player.camera.position = player.entity.pos;
    player.camera.position.y += PLAYER_HEIGHT;
    player.camera.target = Vector3Add(player.camera.position, player.entity.forward);
    UpdateCamera(&player.camera, CAMERA_CUSTOM);
}

void UpdateProjectionMatrix(void)
{
    Matrix projection = MatrixPerspective(
        player.camera.fovy * (PI / 180.0f),
        (float)GetScreenWidth() / GetScreenHeight(),
        0.1f,
        100000.0f);

    rlSetMatrixProjection(projection);
}