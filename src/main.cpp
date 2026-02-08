#include "raylib.h"
#include "raymath.h"

#define G 400
#define PLAYER_HOR_SPEED 200.f
#define PLAYER_JUMP_SPEED 350.f

typedef struct Player {
    Rectangle rect;
    Vector2 position;
    float speed;
    bool canJump;
};

typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
};

void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta);

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth,screenHeight,"676767");

    // Player declaration
    Player player;

    float positionX = (float)screenWidth/2.0f;
    float positionY = (float)screenHeight/2.0f;

    player.rect = {player.position.x - 20, player.position.y - 40, 40.0f, 40.0f};
    player.position = {positionX,positionY};
    player.speed = 50.0f;
    player.canJump = false;

    // Enviornment items declaration
    EnvItem envItems[] = {
        {{0, 0, 1000, 400}, 0, LIGHTGRAY}
    };

    int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);

    // Camera declaration
    Camera2D camera;
    camera.target = player.position;
    camera.offset = { screenWidth/2.0f , screenHeight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;


    SetTargetFPS(60);

    while(!WindowShouldClose()) {

        float deltaTime = GetFrameTime();

        UpdatePlayer(&player,envItems,envItemsLength,deltaTime);

        BeginDrawing();

            ClearBackground(GRAY);

            BeginMode2D(camera);

            // for(int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect,envItems[i].color);

            DrawRectangleRec(player.rect,RED);

            EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta) {
    if(IsKeyDown(KEY_LEFT)) player->position.x -= PLAYER_HOR_SPEED*delta;
    if(IsKeyDown(KEY_RIGHT)) player->position.x += PLAYER_HOR_SPEED*delta;

    if(IsKeyDown(KEY_SPACE) && player->canJump) {
        player->speed = -PLAYER_JUMP_SPEED;
        player->canJump = false;
    }

    Vector2 p = player->position;

    bool hitObstacle = false;
    for(int i = 0; i < envItemsLength; i++) {
        EnvItem *e = envItems + i;

        if(e->blocking &&
            e->rect.x <= p.x &&
            e->rect.x + e->rect.width >= p.x &&
            e->rect.y >= p.y &&
            e->rect.y <= p.y + player->speed*delta
        )
        {
            hitObstacle = true;
            player->speed = 0.0f;
            p.y = e->rect.y;

            break;
        }
    }

    if (!hitObstacle) {
        player->position.y += player->speed*delta;
        player->speed += G*delta;
        player->canJump = false;
    }
    else {player->canJump = true;}
}