/*
rlTextLib example

-- Copyright (c) 2025 Jeffery Myers
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
Font oldFont;
Font oldFontScaled;

float fontSize = 20;


std::string Text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
std::string TextNewlines = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna \naliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. \nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. \nExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

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
	ttfFont = rltLoadFontTTF("resources/Vera.ttf", fontSize, &fontSet);

	// add a custom glyph to the font
	Image logo = LoadImage("resources/raylib_logo.png");
	ImageResize(&logo, int(fontSize), int(fontSize));

	int codePointSize = 0;
	rltAddGlpyhToFont(&ttfFont, GetCodepoint(u8"😊", &codePointSize), logo);

	oldFont = LoadFontEx("resources/Vera.ttf", int(fontSize), nullptr, 0);

	oldFontScaled = LoadFontEx("resources/Vera.ttf", int(fontSize * GetWindowScaleDPI().y), nullptr, 0);
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

	rltDrawText("Old Font Native", 20, Vector2{ 10,10 }, WHITE);
	DrawTextEx(oldFont, TextNewlines.c_str(), Vector2{ 10, 40 }, fontSize, fontSize / 10, WHITE);

	rltDrawText("Old Font Scaled", 20, Vector2{ 10,140 }, WHITE);
	DrawTextEx(oldFontScaled, TextNewlines.c_str(), Vector2{ 10, 160 }, fontSize, fontSize / 10, WHITE);


	rltDrawText("New Font Newlines", 20, Vector2{ 10,260 }, WHITE);
	rltDrawText(TextNewlines, fontSize, Vector2{ 10, 280 }, WHITE, &ttfFont);

	rltDrawText("New Font Wrapped", 20, Vector2{ 10,380 }, WHITE);
	rltDrawTextWrapped(Text, fontSize, Vector2{ 10, 400 }, float(GetScreenWidth()), WHITE, &ttfFont);



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