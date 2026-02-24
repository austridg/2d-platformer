#include "raylib.h"
#include "raymath.h"

const int G = 400;
const float PLAYER_HOR_SPEED = 200.f;
const float PLAYER_JUMP_SPEED = 350.f;

struct Player {
    Rectangle rect;
    Vector2 position;
    float speed;
    bool canJump;
};

struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
};

void UpdatePlayer(Player* player, EnvItem* envItems, int envItemsLength, float delta);
void updateCamera(Camera2D* camera, Player* player);

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "676767");

    // Player declaration
    Player player{};

    float positionX = 0;
    float positionY = 0;

    player.rect = { player.position.x - 20, player.position.y - 40, 40.0f, 40.0f };
    player.position = { positionX,positionY };
    player.speed = 0.0f;
    player.canJump = false;

    // Enviornment items declaration
    EnvItem envItems[] = {
        {{0, 0, 1000, 400}, 0, LIGHTGRAY}
    };

    int envItemsLength = sizeof(envItems) / sizeof(envItems[0]);

    // Camera declaration
    Camera2D camera;
    camera.target = player.position;
    camera.offset = { screenWidth / 2.0f , screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;


    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        float deltaTime = GetFrameTime();

        UpdatePlayer(&player, envItems, envItemsLength, deltaTime);

        updateCamera(&camera,&player);

        BeginDrawing();

        ClearBackground(GRAY);

        BeginMode2D(camera);

        for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color);

        DrawRectangleRec(player.rect, RED);

        EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void UpdatePlayer(Player* player, EnvItem* envItems, int envItemsLength, float delta) {
    EnvItem e = envItems[0];

    if (IsKeyDown(KEY_LEFT) && !(CheckCollisionRecs(player->rect,e.rect))) player->position.x -= PLAYER_HOR_SPEED * delta;
    if (IsKeyDown(KEY_RIGHT) && !(CheckCollisionRecs(player->rect,e.rect))) player->position.x += PLAYER_HOR_SPEED * delta;

    if (IsKeyDown(KEY_SPACE) && player->canJump) {
        player->speed = -PLAYER_JUMP_SPEED;
        player->canJump = false;
    }

    player->rect.x = player->position.x - 20;
    player->rect.y = player->position.y - 40;

    bool hitObstacle = false;

    if (CheckCollisionRecs(player->rect,e.rect)) {
        hitObstacle = true;
        player->speed = 0.0f;

        if (!(player->position.y > e.rect.y && (player->position.x < e.rect.x || player->position.x > e.rect.width))) { 
            player->position.y = e.rect.y; 
        }
    }

    if (!hitObstacle) {
        player->position.y += player->speed * delta;
        player->speed += G * delta;
        player->canJump = false;
    }
    else { player->canJump = true; }
}

void updateCamera(Camera2D* camera, Player* player) {
    camera->target = player->position;
}