
#ifndef FONT_ATLAS_H
#define FONT_ATLAS_H

#include <SDL2/SDL.h>

#include "Texture.h"
#include "Types.h"

#include <unordered_map>

#include "glm/glm.hpp"

typedef struct FontAtlas {
    
    std::unordered_map<char, glm::vec2> texMap;
    Texture texture;

    void packChar(char character);
    glm::vec2 getChar(char character);

    FontAtlas(uint width, uint height);

} FontAtlas;

#endif
