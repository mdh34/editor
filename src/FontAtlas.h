
#ifndef FONT_ATLAS_H
#define FONT_ATLAS_H

#include <SDL2/SDL.h>

#include "Texture.h"
#include "Types.h"
#include "Font.h"

#include <unordered_map>

#include "glm/glm.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <freetype/ftglyph.h>

struct FontInfo {
    FT_GlyphSlot glyph;
    glm::vec2 coords;
};

typedef struct FontAtlas {
    NFont font;

    std::unordered_map<char, FontInfo> texMap;
    Texture texture;

    uint width;
    uint height;

    uint spriteWidth;
    uint spriteHeight;

    glm::vec2 cursor = glm::vec2(0, 0);

    void packChar(char character, uint x, uint y);
    FontInfo getChar(char character);

    FontAtlas();
    FontAtlas(uint width, uint height, NFont font);

} FontAtlas;

#endif
