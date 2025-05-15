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
#pragma once

#include "raylib.h"
#include "raymath.h"

#include <set>
#include <map>
#include <vector>
#include <string>

namespace rltCommonCodepointRanges
{
	static constexpr int HiraganaStart = 0x3040;
	static constexpr int HiraganaEnd = 0x309f;

	static constexpr int KatakanaStart = 0x30a0;
	static constexpr int KatakanaEnd = 0x30ff;

	static constexpr int CyrillicStart = 0x0400;
	static constexpr int CyrillicEnd = 0x04FF;

	static constexpr int EmoticonsStart = 0x1F600;
	static constexpr int EmoticonsEnd = 0x1F64F;

	static constexpr int CJKUnifiedStart = 0x4E00;
	static constexpr int CJKUnifiedEnd = 0x9FFF;

	static constexpr int LatinExtendedAStart = 0x0100;
	static constexpr int LatinExtendedAEnd = 0x017F;

	static constexpr int LatinExtendedBStart = 0x0180;
	static constexpr int LatinExtendedBEnd = 0x024F;

	static constexpr int BlockElementsStart = 0x2580;
	static constexpr int BlockElementsEnd = 0x259F;

	static constexpr int GeometricShapeStart = 0x25A0;
	static constexpr int GeometricShapeEnd = 0x25FF;

	static constexpr int MiscellaneousSymbolsStart = 0x2600;
	static constexpr int MiscellaneousSymbolBEnd = 0x26FF;

	static constexpr int DingbatsStart = 0x2700;
	static constexpr int DingbatsEnd = 0x27BF;

	static constexpr int ArrowsStart = 0x2190;
	static constexpr int ArrowsEnd = 0x21FF;
}

struct rltGlyphInfo
{
	int         Value = 0;
	Vector2     Offset = { 0,0 };
	float       NextCharacterAdvance = 0;
	Rectangle   SourceRect = { 0,0,0,0 };
	Vector2		DestSize = { 0,0 };

	std::map<int, float> KerningInfo;
};

struct rltGlyphRange
{
	size_t Start = 0;
	std::vector<rltGlyphInfo> Glyphs;
};

struct rltFont
{
	float BaseSize = 0;
	float GlyphPadding = 0;
	float DefaultSpacing = 0;
	float DefaultNewlineOffset = 0;
	float Accent = 0;
	std::vector<rltGlyphRange> Ranges;

	rltGlyphInfo InvalidGlyph;

	Texture2D Texture = { 0 };
	float LowestSourceRect = 0;
	float LastSourceRectX = 0;
};

const rltFont& rltGetDefaultFont();

using rltGlyphSet = std::set<int>;

void rltGetStandardGlyphSet(rltGlyphSet& glyphSet);
void rltAddRangeToGlyphSet(int start, int end, rltGlyphSet& glyphSet);
void rltAddGlyphSetFromString(std::string_view text, rltGlyphSet& glyphSet);

rltFont rltLoadFontTTF(std::string_view filePath, float fontSize, const rltGlyphSet* glyphSet = nullptr, float* defaultSpacing = nullptr);
rltFont rltLoadFontTTFMemory(const void* data, size_t dataSize, float fontSize, const rltGlyphSet* glyphSet = nullptr, float* defaultSpacing = nullptr);

void rltUnloadFont(rltFont* font);

bool rltFontHasCodepoint(rltFont* font, int codepoint);
bool rltFontHasAllGlyphsInString(rltFont* font, std::string_view text);

bool rltAddGlpyhToFont(rltFont* font, int codepoint, Image& glpyhImage, const Vector2& offeset = Vector2Zeros, float advance = -1, const Rectangle& sourceRect = Rectangle{ 0,0,0,0 });

void rltMergeGlypRange(rltFont* destination, const rltFont* source, rltGlyphSet& glyphSet);

void rltDrawText(std::string_view text, float size, const Vector2& position, Color tint, const rltFont* font = nullptr);

void rltSetTextYFlip(bool flip = true);

enum class rltAllignment
{
	Left,
	Center,
	Right,
};

void rltDrawTextJustified(std::string_view text, float size, const Vector2& position, Color tint, rltAllignment allignment, const rltFont* font = nullptr);

float rltDrawTextWrapped(std::string_view text, float size, const Vector2& position, float width, Color tint, const rltFont* font = nullptr);

Vector2 rltMeasureText(std::string_view text, float size, const rltFont* font = nullptr);