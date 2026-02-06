#pragma once

#include "raylib.h"

#if defined(__cplusplus)
extern "C" {            // Prevents name mangling of functions
#endif

    /* Codepoint ranges */
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

    typedef void* rltcGlyphInfo;
    typedef void* rltcGlyphRange;
    typedef void* rltcFont;
    typedef void* rltcGlyphSet;

    rltcFont rltcGetDefaultFont();

    rltcGlyphSet rltcCreateGlyphSet();
    void rltcDestroyGlyphSet(rltcGlyphSet glyphSet);

    void rltcGetStandardGlyphSet(rltcGlyphSet glyphSet);
    void rltcAddRangeToGlyphSet(int start, int end, rltcGlyphSet glyphSet);
    void rltcAddGlyphSetFromString(const char* text, rltcGlyphSet glyphSet);
    void rltcAddGlyphSetFromStringWithLength(const char* text, size_t length, rltcGlyphSet glyphSet);

    rltcFont rltcLoadFontTTF(const char* filePath, float fontSize, rltcGlyphSet glyphSet, float* defaultSpacing);
    rltcFont rltcLoadFontTTFMemory(const void* data, size_t dataSize, float fontSize, rltcGlyphSet glyphSet, float* defaultSpacing);

    void rltcUnloadFont(rltcFont font);

    bool rltcFontHasCodepoint(rltcFont* font, int codepoint);
    bool rltcFontHasAllGlyphsInString(rltcFont* font, const char* text);

    bool rltcAddGlpyhToFont(rltcFont font, int codepoint, Image glpyhImage, Vector2 offeset, float advance, Rectangle sourceRect);

    void rltcMergeGlypRange(rltcFont destination, rltcFont source, rltcGlyphSet glyphSet);

    void rltcDrawText(const char* text, float size, Vector2 position, Color tint, rltcFont font);
	void rltcDrawTextLength(const char* text, size_t length, float size, Vector2 position, Color tint, rltcFont font);

    void rltcSetTextYFlip(bool flip);

    typedef enum rltcAllignment
    {
       rltcAllignmentLeft,
       rltcAllignmentCenter,
       rltcAllignmentRight,
    }rltcAllignment;

    void rltcDrawTextJustified(const char* text, float size, Vector2 position, Color tint, rltcAllignment allignment, rltcFont font);
	void rltcDrawTextLenghtJustified(const char* text, size_t length, float size, Vector2 position, Color tint, rltcAllignment allignment, rltcFont font);

    float rltcDrawTextWrapped(const char* text, float size, Vector2 position, float width, Color tint, rltcFont* font);
	float rltcDrawTextLengthWrapped(const char* text, size_t length, float size, Vector2 position, float width, Color tint, rltcFont* font);

    Vector2 rltMeasureText(const char* text, float size, rltcFont font);
    Vector2 rltMeasureTextLength(const char* text, size_t length, float size, rltcFont font);

#if defined(__cplusplus)
}           // Prevents name mangling of functions
#endif