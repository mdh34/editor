#ifndef NFONT_H
#define NFONT_H

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Util.h"

typedef struct NFont {
    FT_Library library;
    FT_Error error;
    FT_Face face;

    NFont(std::string path);
} NFont;


#endif