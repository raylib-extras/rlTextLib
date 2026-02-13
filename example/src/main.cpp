/*
rlTextLib example

-- Copyright (c) 2026 Jeffery Myers
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

#define RL_TEXT_IMPLEMENTATION
#include "rlText.h"	// an external header in the static lib project

#include "rlgl.h"

#include <array>

rltFont ttfFont;

float fontSize = 20;
RenderTexture renderTexture = { 0 };

void GameInit()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
	InitWindow(InitialWidth, InitialHeight, "Example");
	SetTargetFPS(144);

	// set up a glyph set with the standard range and some extra characters
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
	UnloadImage(logo);

	// add custom color glyph to the font
	Image colorEmoji = LoadImage("resources/face-with-tears-of-joy_1f602.png");
	ImageResize(&colorEmoji, int(fontSize), int(fontSize));
	rltAddGlpyhToFont(&ttfFont, GetCodepoint(u8"😂", &codePointSize), colorEmoji);
	UnloadImage(colorEmoji);

	renderTexture = LoadRenderTexture(int(400 * GetWindowScaleDPI().x),int(400 * GetWindowScaleDPI().y));
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
	// draw to a render texture but flip the text so we don't have to flip the render texture when we draw it.
	rltSetTextYFlip(true);
	BeginTextureMode(renderTexture);
	ClearBackground(BLANK);

	DrawRectangle(0, 0, 10, 10, RED);

	float y = 200 + sinf(float(GetTime() / 2)) * 70;

	rltDrawText(TextFormat("I am in the render texture at Y %0.0f", y), fontSize * GetWindowScaleDPI().y, Vector2{ 20, y }, WHITE, &ttfFont);

	EndTextureMode();
	rltSetTextYFlip(false);

	BeginDrawing();
	ClearBackground(BLACK);

	//DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), DARKGREEN, BLACK);

	// Text with colors
	rltDrawText(u8"Hello Raylib \a#FF0000FFI \a#FFFF00FFam \a#FF00FFFFDrawing \a#00FF00FFIn Color!!!! -A", fontSize, Vector2{ 10,10 }, WHITE, &ttfFont);

	// Text with alignment
	rltDrawTextJustified(u8"I am Centered \a#FFFFFFFF😊", fontSize, Vector2{ GetScreenWidth() * 0.5f, fontSize * 2 }, YELLOW, rltAllignment::Center, &ttfFont);

	// Text with newlines
	std::string textWithNewlines = "This is text with newlines\nI am more Text\nCheck out my sweet bounding box!";
	rltDrawText(textWithNewlines, fontSize, Vector2{ 10,fontSize * 3 }, WHITE, &ttfFont);

	// bounding box of text with newlines
	auto rectSize = rltMeasureText(textWithNewlines, fontSize, &ttfFont);
	Rectangle bounds = { 10,fontSize * 3, rectSize.x, rectSize.y };
	DrawRectangleLinesEx(bounds, 1, ColorAlpha(BLUE, 0.5f));

	// Text fit to a width with word wrap
	float width = 350 + sinf(float(GetTime() / 5)) * 100;
	rltDrawTextWrapped(u8"😂 This is text fit to a width. I am more Text How do you like me now?... how many lines does this come out to?  who knows? Here are some Unicode characters to hold you over ÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒ\n\a#FFFFFFFF😊💩", fontSize, Vector2{ 10,fontSize * 7 }, width, RAYWHITE, &ttfFont);
	DrawLine(int(width), int(fontSize * 7), int(width), int(fontSize * 14), SKYBLUE);

	// font atlas with glyph rects
	Vector2 offset = { 500,fontSize * 10 };

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

	// draw the render texture that has our text in it, but don't flip it so that Y+ is up.
	// we do have to scale it for the DPI scale though
	Rectangle sourceRect = { 0, 0, float(renderTexture.texture.width), float(renderTexture.texture.height) };
	Rectangle destRect = { 0, 0, float(renderTexture.texture.width / GetWindowScaleDPI().x), float(renderTexture.texture.height / GetWindowScaleDPI().y) };
	destRect.y = GetScreenHeight() - destRect.height;

	DrawTexturePro(renderTexture.texture, sourceRect, destRect, Vector2Zeros, 0, WHITE);

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