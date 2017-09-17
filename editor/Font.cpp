
#include "Font.h"

NFont::NFont(std::string path) {
    error = FT_Init_FreeType(&library);
    if (error) {
        fprintf(stderr, "[ERROR] Failed to init FreeType:(\n");
        exit(EXIT_FAILURE);
    }
    error = NULL;

    error = FT_New_Face(library, (getCWD() + path).c_str(), 0, &face);
    if (error == FT_Err_Unknown_File_Format) {
        fprintf(stderr, "[ERROR] Font format for font %s not supported!\n", path.c_str());
    }
    else if (error) {
        fprintf(stderr, "[ERROR] Failed to load font:%s\n", path.c_str());
        exit(EXIT_FAILURE);
    }

    error = NULL;

    error = FT_Set_Pixel_Sizes(face, 0, 16);
    if (error) {
        fprintf(stderr, "[ERROR] Failed to set char size!\n");
    }
    error = NULL;
}