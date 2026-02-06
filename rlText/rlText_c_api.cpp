#include "rlTextC.h"

#define RL_TEXT_IMPLEMENTATION
#include "rlText.h"
#undef  RL_TEXT_IMPLEMENTATION


rltcFont rltcGetDefaultFont()
{
    return (rltcFont)&rltGetDefaultFont();
}

rltcGlyphSet rltcCreateGlyphSet()
{
    return (rltcGlyphSet)new rltGlyphSet();
}

void rltcDestroyGlyphSet(rltcGlyphSet glyphSet)
{
    delete (rltGlyphSet*)glyphSet;
}

void rltcGetStandardGlyphSet(rltcGlyphSet glyphSet)
{
    rltGetStandardGlyphSet(*(rltGlyphSet*)glyphSet);
}

void rltcAddRangeToGlyphSet(int start, int end, rltcGlyphSet glyphSet)
{
    rltAddRangeToGlyphSet(start, end, *((rltGlyphSet*)glyphSet));
}

void rltcAddGlyphSetFromStringWithLenght(const char* text, size_t lenght, rltcGlyphSet glyphSet)
{
    rltAddGlyphSetFromString(std::string_view(text, lenght), *(rltGlyphSet*)glyphSet);
}

void rltcAddGlyphSetFromString(const char* text, rltcGlyphSet glyphSet)
{
    rltAddGlyphSetFromString(std::string_view(text), *(rltGlyphSet*)glyphSet);
}

rltcFont rltcLoadFontTTF(const char* filePath, float fontSize, rltcGlyphSet glyphSet, float* defaultSpacing)
{
    auto font = rltLoadFontTTF(filePath, fontSize, (rltGlyphSet*)glyphSet, defaultSpacing);
    auto* fontPtr = new rltFont(std::move(font));
    return (rltcFont)fontPtr;
}

rltcFont rltcLoadFontTTFMemory(const void* data, size_t dataSize, float fontSize, rltcGlyphSet glyphSet, float* defaultSpacing)
{
    auto font = rltLoadFontTTFMemory(data, dataSize, fontSize, (rltGlyphSet*)glyphSet, defaultSpacing);
    auto* fontPtr = new rltFont(std::move(font));
    return (rltcFont)fontPtr;
}

void rltcUnloadFont(rltcFont font)
{
    auto* fontPtr = (rltFont*)font;
    rltUnloadFont(fontPtr);
    delete fontPtr;
}

bool rltcFontHasCodepoint(rltcFont* font, int codepoint)
{
    return rltFontHasCodepoint((rltFont*)font, codepoint);
}

bool rltcFontHasAllGlyphsInString(rltcFont* font, const char* text)
{
    return rltFontHasAllGlyphsInString((rltFont*)font, text);
}

bool rltcAddGlpyhToFont(rltcFont font, int codepoint, Image glpyhImage, Vector2 offeset, float advance, Rectangle sourceRect)
{
    return rltAddGlpyhToFont((rltFont*)font, codepoint, glpyhImage, offeset, advance, sourceRect);
}

void rltcMergeGlypRange(rltcFont destination, rltcFont source, rltcGlyphSet glyphSet)
{
    rltMergeGlypRange((rltFont*)destination, (rltFont*)source, *(rltGlyphSet*)glyphSet);
}

void rltcDrawText(const char* text, float size, Vector2 position, Color tint, rltcFont font)
{
    rltDrawText(std::string_view(text), size, position, tint, (rltFont*)font);
}

void rltcDrawTextLen(const char* text, size_t lenght, float size, Vector2 position, Color tint, rltcFont font)
{
    rltDrawText(std::string_view(text, lenght), size, position, tint, (rltFont*)font);
}

void rltcSetTextYFlip(bool flip)
{
    rltSetTextYFlip(flip);
}

void rltcDrawTextJustified(const char* text, float size, Vector2 position, Color tint, rltcAllignment allignment, rltcFont font)
{
    rltAllignment align = rltAllignment::Left;
    switch (allignment)
    {
    case rltcAllignmentLeft:
        align = rltAllignment::Left;
        break;
    case rltcAllignmentCenter:
        align = rltAllignment::Center;
        break;
    case rltcAllignmentRight:
        align = rltAllignment::Right;
        break;
    }
    rltDrawTextJustified(std::string_view(text), size, position, tint, align, (rltFont*)font);
}

void rltcDrawTextLenJustified(const char* text, size_t lenght, float size, Vector2 position, Color tint, rltcAllignment allignment, rltcFont font)
{
	rltAllignment align = rltAllignment::Left;
	switch (allignment)
	{
	case rltcAllignmentLeft:
		align = rltAllignment::Left;
		break;
	case rltcAllignmentCenter:
		align = rltAllignment::Center;
		break;
	case rltcAllignmentRight:
		align = rltAllignment::Right;
		break;
	}
	rltDrawTextJustified(std::string_view(text, lenght), size, position, tint, align, (rltFont*)font);
}

float rltcDrawTextWrapped(const char* text, float size, Vector2 position, float width, Color tint, rltcFont* font)
{
    return rltDrawTextWrapped(std::string_view(text), size, position, width, tint, (rltFont*)font);
}

float rltcDrawTextLenghtWrapped(const char* text, size_t lenght, float size, Vector2 position, float width, Color tint, rltcFont* font)
{
    return rltDrawTextWrapped(std::string_view(text, lenght), size, position, width, tint, (rltFont*)font);
}

Vector2 rltMeasureText(const char* text, float size, rltcFont font)
{
    return rltMeasureText(std::string_view(text), size, (rltFont*)font);
}

Vector2 rltMeasureTextLenght(const char* text, size_t lenght, float size, rltcFont font)
{
	return rltMeasureText(std::string_view(text, lenght), size, (rltFont*)font);
}