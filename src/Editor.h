#ifndef EDITOR_H
#define EDITOR_H

#include "Buffer.h"
#include "Window.h"
#include "Renderer.h"
#include "Util.h"

#include <vector>
#include <string>

typedef struct Editor {
    Editor(Window& window, Renderer& renderer);

    Window& window;
    Renderer& renderer;
    
    NFont font;
    
    std::vector<Buffer> buffers;
    
    void openFile(std::string path);
    void saveFile(std::string path);
    
    void update();
    void render();
    
    unsigned int activeBuffer;

} Editor;

#endif
