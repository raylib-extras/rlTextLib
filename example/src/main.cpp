/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event 
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial 
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you 
--  wrote the original software. If you use this software in a product, an acknowledgment 
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include "raylib.h"
#include "raymath.h"

#include "game.h"   // an external header in this project
#include "rlText.h"	// an external header in the static lib project



void GameInit()
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(InitialWidth, InitialHeight, "Example");
    SetTargetFPS(144);

    // load resources
}

void GameCleanup()
{
    // unload resources

    CloseWindow();
}

bool GameUpdate()
{
    return true;
}

void GameDraw()
{
    BeginDrawing();
    ClearBackground(DARKGRAY);

    double newStart = GetTime();
    rltDrawText("Hello Raylib I AM NEW DRAWING!!!!", 20, Vector2{10,10}, BLACK);
    double newDelta = GetTime() - newStart;
    rltDrawText(TextFormat("new time %f", newDelta * 1000.0f), 20, Vector2{10,30}, BLACK);

    double oldStart = GetTime();
    DrawText("Hello Raylib I AM OLD DRAWING!!!!", 10, 60, 20, BLACK);
    double oldDelta = GetTime() - oldStart;

    rltDrawText(TextFormat("old time %f", oldDelta * 1000.0f), 20, Vector2{ 10,80 }, BLACK);


    rltDrawText("Text is text\nI am more Text\nBruh!", 20, Vector2{ 10,100 }, BLACK);
    EndDrawing();
}

int main()
{
    GameInit();

    while (!WindowShouldClose())
    {
        if (!GameUpdate())
            break;

        GameDraw();
    }
    GameCleanup();

    return 0;
}