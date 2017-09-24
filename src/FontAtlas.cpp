
#include "FontAtlas.h"

FontAtlas::FontAtlas(uint width, uint height, NFont font)  {
    this->width = width;
    this->height = height;

    this->font = font;

    this->spriteWidth = font.height;
    this->spriteHeight = font.height;

    texture = Texture(width, height);
}


void FontAtlas::packChar(char character, uint x, uint y) {
    FT_UInt glyph_index = FT_Get_Char_Index(font.face, character);
    if (FT_Load_Char(font.face, glyph_index, FT_LOAD_RENDER)) {
        printf("Cannot load char %c\n", character);
    }
    FT_GlyphSlot glyph = font.face->glyph;

    if (cursor.x >= width / spriteWidth) {
        cursor.x = 0;
        cursor.y++;
    }

    if (cursor.y >= height / spriteHeight) {
        printf("No more room to pack sprites\n");
        return;
    }

    for (uint x = 0; x < glyph->bitmap.width; x++) {
        for (uint y = 0; y < glyph->bitmap.rows; y++) {
            texture.setPixel(texture.surface, cursor.x * spriteWidth + x, cursor.y + spriteHeight + y, 0xFF000000);
            cursor.x++;
        }
    }
}

FontInfo FontAtlas::getChar(char character) {

}