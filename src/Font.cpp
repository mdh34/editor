
#include "Font.h"

NFont::NFont() {}

NFont::NFont(std::string& path, unsigned int height) {
    this->path = path;
    this->height = height;
}

int NFont::init() {
    if (FT_Init_FreeType(&lib)) {
        fprintf(stderr, "[ERROR] Failed to init FreeType library\n");
        
        return 1;
    }
    
    std::string newPath = getCWD() + path;
    
    if (FT_New_Face(lib, newPath.c_str(), 0, &face)) {
        fprintf(stderr, "[ERROR] Failed to load face!");
        return 1;
    }
    
    FT_Set_Pixel_Sizes(face, 0, height);
    // FT_Set_Char_Size(face, )

    /*glActiveTexture(GL_TEXTURE1);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    glGenBuffers(1, &vbo);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindTexture(GL_TEXTURE_2D, 0);*/

    return 0;
}
