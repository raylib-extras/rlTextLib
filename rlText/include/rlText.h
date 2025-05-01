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

#include <vector>
#include <string>

struct rltGlyphInfo 
{
    int         Value = 0;
    Vector2     Offset = { 0,0 };
    float       NextCharacterAdvance = 0;
    Rectangle   SourceRect = { 0,0,0,0 };
};

struct rltGlyphRange
{
    int Start = 0;
    std::vector<rltGlyphInfo> Glyphs;
};

struct rltFont
{
    float BaseSize;           // Base size (default chars height)
    float GlyphPadding;       // Padding around the glyph characters
    float DefaultSpacing = 0;
    float DefaultNewlineOffset = 0;
    std::vector<rltGlyphRange> Ranges;

    Texture2D texture;          // Texture atlas containing the glyphs
};

const rltFont& rltGetDefaultFont();

void rltGetStandardGlyphRange(const std::vector<int>& glyphRange);
void rltAddGlyphRange(int start, int end, const std::vector<int>& glyphRange);
void rltAddGlyphRangeFromString(std::string_view text, const std::vector<int>& glyphRange);

rltFont rltLoadFontTTF(std::string_view filePath, const std::vector<int>* glyphRange = nullptr);
rltFont rltLoadFontTTFMemory(const void* data, size_t size);

void rltUnloadFont(rltFont* font);

void rltDrawText(std::string_view text, float size, const Vector2& position, Color tint, const rltFont* font = nullptr);