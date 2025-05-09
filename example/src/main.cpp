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

#include "rlgl.h"

#include <array>

rltFont ttfFont;
Font oldTTFFont;

void GameInit()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
	InitWindow(InitialWidth, InitialHeight, "Example");
	SetTargetFPS(144);

	rltGlyphSet fontSet;
	rltGetStandardGlyphSet(fontSet);
	rltAddRangeToGlyphSet(255, 300, fontSet);
	rltAddGlyphSetFromString(u8"~¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþ", fontSet);

	ttfFont = rltLoadFontTTF("resources/anonymous_pro_bold.ttf", 20, &fontSet);

	Image logo = LoadImage("resources/raylib_logo.png");
	ImageResize(&logo, 20, 20);

	int codePointSize = 0;
	rltAddGlpyhToFont(&ttfFont, GetCodepoint(u8"😊", &codePointSize), logo);

	oldTTFFont = LoadFontEx("resources/anonymous_pro_bold.ttf", 20, nullptr, 0);
}

void GameCleanup()
{
	// unload resources
	UnloadFont(oldTTFFont);
	rltUnloadFont(&ttfFont);

	CloseWindow();
}

bool GameUpdate()
{
	return true;
}

void GameDraw()
{
	BeginDrawing();
	ClearBackground(BLACK);

	double newStart = GetTime();
	rltDrawText(u8"Hello Raylib \a#FF0000FFI \a#FFFF00FFAM \a#FF00FFFFNEW \a#00FF00FFDRAWING!!!!", 20, Vector2{ 10,10 }, WHITE, &ttfFont);
	double newDelta = GetTime() - newStart;
	rltDrawText(TextFormat("new time %f", newDelta * 1000.0f), 20, Vector2{ 10,30 }, WHITE);

	double oldStart = GetTime();
	DrawTextEx(oldTTFFont, "Hello Raylib I AM OLD DRAWING!!!!", Vector2{ 10, 60 }, 20, 1, WHITE);
	double oldDelta = GetTime() - oldStart;

	rltDrawText(TextFormat("old time %f", oldDelta * 1000.0f), 20, Vector2{ 10,80 }, WHITE);

	std::string textWithNewlines = "Text is text with newlines\nI am more Text\nBruh!";
	rltDrawText(textWithNewlines, 20, Vector2{ 10,100 }, WHITE, &ttfFont);

	auto rectSize = rltMeasureText(textWithNewlines, 20, &ttfFont);
	Rectangle bounds = { 10,100, rectSize.x, rectSize.y };
	DrawRectangleLinesEx(bounds, 1, ColorAlpha(BLUE, 0.5f));

	float width = 350 + sinf(float(GetTime())) * 100;
	rltDrawTextWrapped(u8"This is text fit to a width. I am more Text Bruh! Brosef... how many lines does this come out to? ÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒ\n\a#FFFFFFFF😊", 20, Vector2{ 10,200 }, width, PURPLE, &ttfFont);
	DrawLine(int(width), 200, int(width), 400, SKYBLUE);

	Vector2 offset = { 500,200 };

	DrawTexture(ttfFont.Texture, int(offset.x), int(offset.y), WHITE);

	for (auto& range : ttfFont.Ranges)
	{
		for (auto& glyph : range.Glyphs)
		{
			auto rect = glyph.SourceRect;
			rect.x += offset.x;
			rect.y += offset.y;
			DrawRectangleLinesEx(rect, 1, ColorAlpha(RED, 0.5f));
		}
	}

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