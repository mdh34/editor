
#include "Editor.h"

Editor::Editor() {
    int width = 1000;
    int height = width / 16 * 9;

    window = Window(width, height, "Editor");
    renderer = Renderer(window.width, window.height);

    renderer.projectionMatrix = glm::ortho(0.0f, (float)(window.width), (float)(window.height), 0.0f, -100.0f, 100.0f);;
    renderer.translationMatrix = glm::mat4();
    renderer.modelMatrix = glm::mat4();

    renderer.mvpMatrix = glm::mat4();
    renderer.init();

    std::string path = "/res/fonts/consolas.ttf";
    font = NFont(path, 18);
    font.init();

    buffers.push_back(Buffer());
    activeBuffer = 0;

    //    openFile("test.cpp");

    texture = Texture(256, 256);
}

void Editor::update() {
    renderer.projectionMatrix = glm::ortho(0.0f, (float)(window.width), (float)(window.height), 0.0f, -100.0f, 100.0f);

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
    window.clear();

    for(uint i = 0; i < buffers.size(); i++) {
        for (uint j = 0; j < buffers[i].lines.size(); j++) {
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

    Renderable2D renderable(glm::vec3(0, 0, 1), glm::vec2(800, 600));
    renderer.drawTexturedQuad(renderable, texture);

    window.flip();
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

bool Editor::isOpen() {
    return window.isOpen;
}

void Editor::destroy() {
    window.destroy();
}