
#include "Editor.h"

Editor::Editor(Window& window, Renderer& renderer)
: window(window), renderer(renderer) {
    
    std::string path = "/res/fonts/consolas.ttf";
    font = NFont(path, 24);
    font.init();
    
    buffers.push_back(Buffer());
    activeBuffer = 0;
}

void Editor::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            window.destroy();
            window.isOpen = false;
        }
        else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
            window.width = event.window.data1;
            window.height = event.window.data2;
            glViewport(0, 0, window.width, window.height);
        }
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_BACKSPACE) {
                buffers[activeBuffer].contents.pop_back();
            } else if (event.key.keysym.sym == SDLK_RETURN) {
                buffers[activeBuffer].contents += '\n';
            }
        }
        else if (event.type == SDL_TEXTINPUT) {
            buffers[activeBuffer].contents += event.text.text;
        }
    }
}

void Editor::render() {
    for(unsigned int i = 0; i < buffers.size(); i++) {
//        renderer.drawString(font, buffers[i].contents, glm::vec3(0, 0, 0), glm::vec4(1, 1, 1, 1));
        std::string splitBy = "\n";
        std::vector<std::string> lines = stringSplit(buffers[i].contents, splitBy);
        for (unsigned int j = 0; j < lines.size(); j++) {
            renderer.drawString(font, lines[j], glm::vec3(0, j * font.height, 1), glm::vec4(1, 1, 1, 1));
        }
    }
}

void Editor::openFile(std::string filePath) {
    
}

void Editor::saveFile(std::string filePath) {
    
}
