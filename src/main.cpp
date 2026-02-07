#include "raylib.h"

int main() {
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth,screenHeight,"676767");

    SetTargetFPS(60);

    float positionX = (float)screenWidth/2.0f;
    float positionY = (float)screenHeight/2.0f;

    Vector2 textPosition = {positionX,positionY};


    while(!WindowShouldClose()) {

        if (IsKeyDown(KEY_RIGHT)) textPosition.x += 100.0f*GetFrameTime();
        if (IsKeyDown(KEY_UP)) textPosition.y -= 100.0f*GetFrameTime();
        if (IsKeyDown(KEY_LEFT)) textPosition.x -= 100.0f*GetFrameTime();
        if (IsKeyDown(KEY_DOWN)) textPosition.y += 100.0f*GetFrameTime();

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("67 LOL",textPosition.x,textPosition.y,100,BLACK);

        EndDrawing();

        positionX++;
    }

    CloseWindow();
}