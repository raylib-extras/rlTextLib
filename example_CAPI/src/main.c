/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

-- Copyright (c) 2020-2026 Jeffery Myers
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
#include "rlTextC.h"	// an external header in the static lib project

#include "rlgl.h"

#include <string.h>


rltcFont ttfFont;

Font rayFont = { 0 };

float fontSize = 32;

void GameInit()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
	InitWindow(InitialWidth, InitialHeight, "Example");
	SetTargetFPS(144);

	// set up a glpyh set with the standard range and some extra characters
	rltcGlyphSet fontSet = rltcCreateGlyphSet();
	rltcGetStandardGlyphSet(fontSet);
	rltcAddRangeToGlyphSet(255, 300, fontSet);
	rltcAddGlyphSetFromString(u8"~¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþ", fontSet);

	// load a ttf font with the defined font set, if you do not provide a set, the standard set will be used.
	ttfFont = rltcLoadFontTTF("resources/Vera.ttf", fontSize, fontSet, NULL);


	rayFont = LoadFontEx("resources/Vera.ttf", (int)fontSize, 0,0);

	// add a custom glyph to the font
	Image logo = LoadImage("resources/raylib_logo.png");
	ImageResize(&logo, (int)fontSize, (int)fontSize);
	int codePointSize = 0;
	rltcAddGlpyhToFont(ttfFont, GetCodepoint(u8"😊", &codePointSize), logo, Vector2Zero(), 0, (Rectangle){0,0,0,0});
	UnloadImage(logo);

	// add custom color glpyh to the font
	Image colorEmoji = LoadImage("resources/face-with-tears-of-joy_1f602.png");
	ImageResize(&colorEmoji, (int)fontSize, (int)fontSize);
	rltcAddGlpyhToFont(ttfFont, GetCodepoint(u8"😂", &codePointSize), colorEmoji, Vector2Zero(), 0, (Rectangle) { 0, 0, 0, 0 });
	UnloadImage(colorEmoji);
	rltcDestroyGlyphSet(fontSet);
}

void GameCleanup()
{
	// unload resources
	rltcUnloadFont(ttfFont);

	CloseWindow();
}

bool GameUpdate()
{
	return true;
}

int CurrentCharacter = 1;
float accumulator = 0;
float timeStep = 1.0f / 10.0f;

void GameDraw()
{
	BeginDrawing();
	ClearBackground(BLACK);

	DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), DARKBLUE, BLACK);

	// Text with colors
	rltcDrawText("-A Hello Raylib \a#FF0000FFI \a#FFFF00FFam \a#FF00FFFFDrawing \a#00FF00FFIn Color!!!!", fontSize, (Vector2){ 10,10 }, WHITE, ttfFont);

	// Text with alignment
	rltcDrawTextJustified(u8"I am Centered \a#FFFFFFFF😊", fontSize, (Vector2){ GetScreenWidth() * 0.5f, fontSize * 2 }, YELLOW, rltcAllignmentCenter, ttfFont);

	// Text with newlines
	const char* textWithNewlines = "This is text with newlines\nI am more Text\nCheck out my sweet bounding box!";
	//rltDrawText(textWithNewlines, fontSize, Vector2{ 10,fontSize * 3 }, WHITE, &ttfFont);
	DrawTextEx(rayFont, textWithNewlines, (Vector2){ 10, fontSize * 3 }, fontSize, fontSize / 10, WHITE);
	// bounding box of text with newlines
	Vector2 rectSize = rltMeasureText(textWithNewlines, fontSize, &ttfFont);
	Rectangle bounds = { 10,fontSize * 3, rectSize.x, rectSize.y };
	DrawRectangleLinesEx(bounds, 1, ColorAlpha(BLUE, 0.5f));

	// Text fit to a width with word wrap
	const char* longText = u8"😂 This is text fit to a width. I am more Text How do you like me now?... how many lines does this come out to?  who knows? Here are some Unicode characters to hold you over ÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒ\n\a#FFFFFFFF😊💩";

	size_t len = strlen(longText);

	accumulator += GetFrameTime();
	while (accumulator >= timeStep)
	{
		accumulator -= timeStep;
		if (CurrentCharacter < len)
			CurrentCharacter++;
		else
			CurrentCharacter = 0;
	}

	rltcDrawTextLengthWrapped(longText, CurrentCharacter, fontSize, (Vector2){ 10,fontSize * 7 }, GetScreenWidth() - 20.0f, RAYWHITE, ttfFont);

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