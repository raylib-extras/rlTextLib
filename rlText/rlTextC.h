#pragma once

/*
rlTextLib

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

Pure C API.
use with rlText_c_api.cpp to build a static lib

*/

#include "raylib.h"

#include <stddef.h> // For size_t

#if defined(__cplusplus)
extern "C" {            // Prevents name mangling of functions
#endif

/* Common Codepoint ranges */
#define RLT_HIRAGANA_START                  0x3040
#define RLT_HIRAGANA_END                    0x309f
#define RLT_KATAKANA_START                  0x30a0
#define RLT_KATAKANA_END                    0x30ff
#define RLT_CYRILLIC_START                  0x0400
#define RLT_CYRILLIC_END                    0x04FF
#define RLT_EMOTICONS_START                 0x1F600
#define RLT_EMOTICONS_END                   0x1F64F
#define RLT_CJK_UNIFIED_START               0x4E00
#define RLT_CJK_UNIFIED_END                 0x9FFF
#define RLT_LATIN_EXT_A_START               0x0100
#define RLT_LATIN_EXT_A_END                 0x017F
#define RLT_LATIN_EXT_B_START               0x0180
#define RLT_LATIN_EXT_B_END                 0x024F
#define RLT_BLOCK_ELEMENTS_START            0x2580
#define RLT_BLOCK_ELEMENTS_END              0x259F
#define RLT_GEOMETRIC_SHAPE_START           0x25A0
#define RLT_GEOMETRIC_SHAPE_END             0x25FF
#define RLT_MISCELLANEOUS_SYMBOLS_START     0x2600
#define RLT_MISCELLANEOUS_SYMBOLS_END       0x26FF
#define RLT_DINGBATS_START                  0x2700
#define RLT_DINGBATS_END                    0x27BF
#define RLT_ARROWS_START                    0x2190
#define RLT_ARROWS_END                      0x21FF

// opaque types
typedef void* rltcGlyphInfo;
typedef void* rltcGlyphRange;
typedef void* rltcFont;
typedef void* rltcGlyphSet;

/// <summary>
/// Gets the default built-in font.
/// </summary>
/// <returns>Handle to the default font.</returns>
rltcFont rltcGetDefaultFont();

/// A null font, will be treated as the default font in all functions
#define NULLFONT ((rltcFont)NULL)

/// <summary>
/// Creates a new glyph set.
/// </summary>
/// <returns>Handle to the new glyph set.</returns>
rltcGlyphSet rltcCreateGlyphSet();

/// <summary>
/// Destroys a glyph set and frees its resources.
/// </summary>
/// <param name="glyphSet">Handle to the glyph set to destroy.</param>
void rltcDestroyGlyphSet(rltcGlyphSet glyphSet);

/// <summary>
/// Fills a glyph set with the standard ASCII printable characters (32-127).
/// </summary>
/// <param name="glyphSet">Handle to the glyph set to fill.</param>
void rltcGetStandardGlyphSet(rltcGlyphSet glyphSet);


/// <summary>
/// Adds a range of codepoints to a glyph set.
/// </summary>
/// <param name="start">First codepoint in the range (inclusive).</param>
/// <param name="end">Last codepoint in the range (inclusive).</param>
/// <param name="glyphSet">Handle to the glyph set.</param>
void rltcAddRangeToGlyphSet(int start, int end, rltcGlyphSet glyphSet);

/// <summary>
/// Adds all unique codepoints found in a UTF-8 string to a glyph set.
/// </summary>
/// <param name="text">UTF-8 encoded string.</param>
/// <param name="glyphSet">Handle to the glyph set.</param>
void rltcAddGlyphSetFromString(const char* text, rltcGlyphSet glyphSet);

/// <summary>
/// Adds all unique codepoints found in a UTF-8 string (with length) to a glyph set.
/// </summary>
/// <param name="text">UTF-8 encoded string.</param>
/// <param name="length">Length of the string in bytes.</param>
/// <param name="glyphSet">Handle to the glyph set.</param>
void rltcAddGlyphSetFromStringWithLength(const char* text, size_t length, rltcGlyphSet glyphSet);

/// <summary>
/// Loads a TTF font from a file.
/// </summary>
/// <param name="filePath">Path to the TTF file.</param>
/// <param name="fontSize">Desired font size in pixels.</param>
/// <param name="glyphSet">Glyph set to include (can be NULL).</param>
/// <param name="defaultSpacing">Optional pointer to override default spacing.</param>
/// <returns>Handle to the loaded font.</returns>
rltcFont rltcLoadFontTTF(const char* filePath, float fontSize, rltcGlyphSet glyphSet, float* defaultSpacing);

/// <summary>
/// Loads a TTF font from memory.
/// </summary>
/// <param name="data">Pointer to TTF data in memory.</param>
/// <param name="dataSize">Size of the TTF data in bytes.</param>
/// <param name="fontSize">Desired font size in pixels.</param>
/// <param name="glyphSet">Glyph set to include (can be NULL).</param>
/// <param name="defaultSpacing">Optional pointer to override default spacing.</param>
/// <returns>Handle to the loaded font.</returns>
rltcFont rltcLoadFontTTFMemory(const void* data, size_t dataSize, float fontSize, rltcGlyphSet glyphSet, float* defaultSpacing);

/// <summary>
/// Unloads a font and frees its resources.
/// </summary>
/// <param name="font">Handle to the font to unload.</param>
void rltcUnloadFont(rltcFont font);


/// <summary>
/// Checks if a font contains a glyph for the given codepoint.
/// </summary>
/// <param name="font">Pointer to the font handle.</param>
/// <param name="codepoint">Unicode codepoint to check.</param>
/// <returns>True if the font contains the codepoint, false otherwise.</returns>
bool rltcFontHasCodepoint(rltcFont* font, int codepoint);

/// <summary>
/// Checks if a font contains glyphs for all codepoints in a string.
/// </summary>
/// <param name="font">Pointer to the font handle.</param>
/// <param name="text">UTF-8 encoded string to check.</param>
/// <returns>True if all codepoints are present, false otherwise.</returns>
bool rltcFontHasAllGlyphsInString(rltcFont* font, const char* text);

/// <summary>
/// Adds a new glyph to a font from an image.
/// </summary>
/// <param name="font">Handle to the font.</param>
/// <param name="codepoint">Unicode codepoint for the glyph.</param>
/// <param name="glpyhImage">Image containing the glyph bitmap.</param>
/// <param name="offeset">Offset to apply when rendering the glyph.</param>
/// <param name="advance">Advance value for the glyph (use -1 for default).</param>
/// <param name="sourceRect">Source rectangle in the image.</param>
/// <returns>True if the glyph was added successfully, false otherwise.</returns>
bool rltcAddGlpyhToFont(rltcFont font, int codepoint, Image glpyhImage, Vector2 offeset, float advance, Rectangle sourceRect);

/// <summary>
/// Merges glyphs from a source font into a destination font for the specified glyph set.
/// </summary>
/// <param name="destination">Font to add glyphs to.</param>
/// <param name="source">Font to copy glyphs from.</param>
/// <param name="glyphSet">Glyph set to merge.</param>
void rltcMergeGlypRange(rltcFont destination, rltcFont source, rltcGlyphSet glyphSet);

/// <summary>
/// Draws text at the specified position using a font.
/// </summary>
/// <param name="text">UTF-8 encoded string to draw.</param>
/// <param name="size">Font size in pixels.</param>
/// <param name="position">Top-left position to draw the text.</param>
/// <param name="tint">Color tint to apply.</param>
/// <param name="font">Font handle to use.</param>
void rltcDrawText(const char* text, float size, Vector2 position, Color tint, rltcFont font);

/// <summary>
/// Draws text at the specified position using a font, with explicit string length.
/// </summary>
/// <param name="text">UTF-8 encoded string to draw.</param>
/// <param name="length">Length of the string in bytes.</param>
/// <param name="size">Font size in pixels.</param>
/// <param name="position">Top-left position to draw the text.</param>
/// <param name="tint">Color tint to apply.</param>
/// <param name="font">Font handle to use.</param>
void rltcDrawTextLength(const char* text, size_t length, float size, Vector2 position, Color tint, rltcFont font);

/// <summary>
/// Sets whether text rendering should be vertically flipped.
/// </summary>
/// <param name="flip">True to flip text vertically, false to render normally.</param>
void rltcSetTextYFlip(bool flip);

/// <summary>
/// Text alignment options for justified drawing.
/// </summary>
typedef enum rltcAllignment
{
	rltcAllignmentLeft,
	rltcAllignmentCenter,
	rltcAllignmentRight,
}rltcAllignment;

/// <summary>
/// Draws justified (aligned) text at the specified position.
/// </summary>
/// <param name="text">UTF-8 encoded string to draw.</param>
/// <param name="size">Font size in pixels.</param>
/// <param name="position">Reference position for alignment.</param>
/// <param name="tint">Color tint to apply.</param>
/// <param name="allignment">Text alignment (left, center, right).</param>
/// <param name="font">Font handle to use.</param>
void rltcDrawTextJustified(const char* text, float size, Vector2 position, Color tint, rltcAllignment allignment, rltcFont font);

/// <summary>
/// Draws justified (aligned) text at the specified position, with explicit string length.
/// </summary>
/// <param name="text">UTF-8 encoded string to draw.</param>
/// <param name="length">Length of the string in bytes.</param>
/// <param name="size">Font size in pixels.</param>
/// <param name="position">Reference position for alignment.</param>
/// <param name="tint">Color tint to apply.</param>
/// <param name="allignment">Text alignment (left, center, right).</param>
/// <param name="font">Font handle to use.</param>
void rltcDrawTextLengthJustified(const char* text, size_t length, float size, Vector2 position, Color tint, rltcAllignment allignment, rltcFont font);

/// <summary>
/// Draws text with automatic word wrapping to fit within a given width.
/// </summary>
/// <param name="text">UTF-8 encoded string to draw.</param>
/// <param name="size">Font size in pixels.</param>
/// <param name="position">Top-left position to draw the text.</param>
/// <param name="width">Maximum width for wrapping.</param>
/// <param name="tint">Color tint to apply.</param>
/// <param name="font">Pointer to the font handle.</param>
/// <returns>The final y position after drawing (useful for multi-line layouts).</returns>
float rltcDrawTextWrapped(const char* text, float size, Vector2 position, float width, Color tint, rltcFont* font);

/// <summary>
/// Draws text with automatic word wrapping to fit within a given width, with explicit string length.
/// </summary>
/// <param name="text">UTF-8 encoded string to draw.</param>
/// <param name="length">Length of the string in bytes.</param>
/// <param name="size">Font size in pixels.</param>
/// <param name="position">Top-left position to draw the text.</param>
/// <param name="width">Maximum width for wrapping.</param>
/// <param name="tint">Color tint to apply.</param>
/// <param name="font">Pointer to the font handle.</param>
/// <returns>The final y position after drawing (useful for multi-line layouts).</returns>
float rltcDrawTextLengthWrapped(const char* text, size_t length, float size, Vector2 position, float width, Color tint, rltcFont* font);

/// <summary>
/// Measures the size (width and height) of the given text string.
/// </summary>
/// <param name="text">UTF-8 encoded string to measure.</param>
/// <param name="size">Font size in pixels.</param>
/// <param name="font">Font handle to use.</param>
/// <returns>Vector2 containing the width (x) and height (y) of the text.</returns>
Vector2 rltMeasureText(const char* text, float size, rltcFont font);

/// <summary>
/// Measures the size (width and height) of the given text string, with explicit string length.
/// </summary>
/// <param name="text">UTF-8 encoded string to measure.</param>
/// <param name="length">Length of the string in bytes.</param>
/// <param name="size">Font size in pixels.</param>
/// <param name="font">Font handle to use.</param>
/// <returns>Vector2 containing the width (x) and height (y) of the text.</returns>
Vector2 rltMeasureTextLength(const char* text, size_t length, float size, rltcFont font);

#if defined(__cplusplus)
}           // Prevents name mangling of functions
#endif