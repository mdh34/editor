#ifndef EDITOR_H
#define EDITOR_H

#include "Buffer.h"
#include "Window.h"
#include "Renderer.h"
#include "Util.h"

#include <vector>
#include <string>

typedef struct Editor {
    Editor();

    Window window;
    Renderer renderer;
    NFont font;

    Texture texture;
    
    std::vector<Buffer> buffers;
    glm::vec2 visibleBounds;
    
    int time = 0;
    bool show = true;
    
    void openFile(std::string path);
    void saveFile(std::string path);
    
    void update();
    void render();
    
    unsigned int activeBuffer;

    bool isOpen();
    void destroy();

} Editor;

#endif
