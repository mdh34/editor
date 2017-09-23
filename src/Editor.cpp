
#include "Editor.h"

Editor::Editor(Window& window, Renderer& renderer)
: window(window), renderer(renderer) {
    
    std::string path = "/res/fonts/consolas.ttf";
    font = NFont(path, 18);
    font.init();
    
    buffers.push_back(Buffer());
    activeBuffer = 0;
    
//    openFile("test.cpp");
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
                buffers[activeBuffer].delChar(false);
            } else if (event.key.keysym.sym == SDLK_RETURN) {
                buffers[activeBuffer].newLine();
            }
            else if (event.key.keysym.sym == SDLK_LEFT) {
                buffers[activeBuffer].moveCursorBy(-1, 0);
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                buffers[activeBuffer].moveCursorBy(1, 0);
            }
            else if (event.key.keysym.sym == SDLK_UP) {
                buffers[activeBuffer].moveCursorBy(0, -1);
            }
            else if (event.key.keysym.sym == SDLK_UP) {
                buffers[activeBuffer].moveCursorBy(0, 1);
            }
        }
        else if (event.type == SDL_TEXTINPUT) {
            buffers[activeBuffer].insert(event.text.text);
        }
    }

    time += 1;
}

void Editor::render() {
    for(unsigned int i = 0; i < buffers.size(); i++) {
//        renderer.drawString(font, buffers[i].contents, glm::vec3(0, 0, 0), glm::vec4(1, 1, 1, 1));
        for (unsigned int j = 0; j < buffers[i].lines.size(); j++) {
            renderer.drawString(font, buffers[i].lines[j], glm::vec3(0, j * font.height, 1), glm::vec4(1, 1, 1, 1));
        }
    }
    
    if (time % 30 == 0) {
        show = !show;
    }
    if (show) {
        renderer.fillQuad((float) buffers[activeBuffer].cursor.x * font.advance,
                          (float) buffers[activeBuffer].cursor.y * font.height,
                          2, font.height, glm::vec4(1, 1, 1, 1));
        
    }
    
}

void Editor::openFile(std::string filePath) {
    Buffer buffer;
    std::string contents = loadFile(filePath);
    std::vector<std::string> lines = stringSplitByLine(contents);
    buffer.lines = lines;
    buffers.push_back(buffer);
    activeBuffer = (unsigned int) buffers.size() - 1;
}

void Editor::saveFile(std::string filePath) {
    
}
