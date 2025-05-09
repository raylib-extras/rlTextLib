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

void GameInit()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
	InitWindow(InitialWidth, InitialHeight, "Example");
	SetTargetFPS(144);

	// set up a glpyh set with the standard range and some extra characters
	rltGlyphSet fontSet;
	rltGetStandardGlyphSet(fontSet);
	rltAddRangeToGlyphSet(255, 300, fontSet);
	rltAddGlyphSetFromString(u8"~¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþ", fontSet);

	// load a ttf font with the defined font set, if you do not provide a set, the standard set will be used.
	ttfFont = rltLoadFontTTF("resources/anonymous_pro_bold.ttf", 20, &fontSet);

	// add a custom glyph to the font
	Image logo = LoadImage("resources/raylib_logo.png");
	ImageResize(&logo, 20, 20);

	int codePointSize = 0;
	rltAddGlpyhToFont(&ttfFont, GetCodepoint(u8"😊", &codePointSize), logo);
}

void GameCleanup()
{
	// unload resources
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

	// Text with colors
	rltDrawText(u8"Hello Raylib \a#FF0000FFI \a#FFFF00FFAM \a#FF00FFFFDrawing \a#00FF00FFIn Color!!!!", 20, Vector2{ 10,10 }, WHITE, &ttfFont);

	// Text with alignment
	rltDrawTextJustified(u8"I am Centered \a#FFFFFFFF😊", 20, Vector2{ GetScreenWidth() * 0.5f, 50 }, YELLOW, rltAllignment::Center, &ttfFont);

	// Text with newlines
	std::string textWithNewlines = "This is text with newlines\nI am more Text\nCheck out my sweet bounding box!";
	rltDrawText(textWithNewlines, 20, Vector2{ 10,100 }, WHITE, &ttfFont);

	// bounding box of text with newlines
	auto rectSize = rltMeasureText(textWithNewlines, 20, &ttfFont);
	Rectangle bounds = { 10,100, rectSize.x, rectSize.y };
	DrawRectangleLinesEx(bounds, 1, ColorAlpha(BLUE, 0.5f));

	// Text fit to a width with word wrap
	float width = 350 + sinf(float(GetTime())) * 100;
	rltDrawTextWrapped(u8"This is text fit to a width. I am more Text How do you like me now?... how many lines does this come out to?  who knows? Here are some Unicode characters to hold you over ÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒ\n\a#FFFFFFFF😊💩", 20, Vector2{ 10,200 }, width, RAYWHITE, &ttfFont);
	DrawLine(int(width), 200, int(width), 400, SKYBLUE);


	// font atlas with glyph rects
	Vector2 offset = { 500,200 };

	rltDrawText("Font atlas", 20, Vector2{ offset.x, offset.y - 20 }, WHITE);
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