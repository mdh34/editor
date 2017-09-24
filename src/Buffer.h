
#ifndef BUFFER_H
#define BUFFER_H

#include "glm/glm.hpp"

#include "Util.h"

#include <string>
#include <algorithm>
#include <iostream>

typedef struct Buffer {
    std::vector<std::string> lines;
    
    glm::vec2 cursor = glm::vec2(0, 0);

    Buffer() {
        lines.push_back(std::string("Hello world"));
    }

    void delChar(bool forward) {
        if (forward) {

        }
        else {
            std::string& currentLine = lines[cursor.y];
            if (cursor.x == 0) {
                if (cursor.y != 0) {
                    lines.erase(lines.begin() + cursor.y);
                    cursor.x = lines[cursor.y - 1].size();
                    cursor.y--;
                }
            } else {
                // currentLine.pop_back();
                currentLine.erase(cursor.x - 1, 1);
                cursor.x--;
            }
        }
    }

    void newLine() {
        lines.emplace(lines.begin() + (int) cursor.y + 1, "");
        cursor.x = 0;
        cursor.y++;
    }

    void moveCursorBy(int x, int y) {
        std::string currentLine = lines[cursor.y];
        if (x > 0) {
            if (cursor.x == currentLine.size()) {
                moveCursorTo(0, cursor.y + 1);
            }
            else {
                if (x == 1) {
                    cursor.x++;
                }
                else {
                    moveCursorTo(0, cursor.y + y);
                }
            }
        }
        else if (x < 0){
            if (cursor.x == 0) {

            }
        }

        if (y > 0) {

        }
        else {

        }
    }

    void moveCursorTo(unsigned int x, unsigned int y) {
        unsigned int xa = cursor.x + x;
        unsigned int ya = cursor.y + y;

        if (y >= lines.size()) {
            ya = lines.size() - 1;
        }
        else {
            xa = std::min(x, lines[ya].size());
        }


        cursor.x = xa;
        cursor.y = ya;
    }

    void insert(std::string text) {
        std::string& currentLine = lines[cursor.y];

        if (cursor.x >= currentLine.length()) {
            currentLine.append(text);
            cursor.x += text.length();
        }
        else {
            currentLine.insert((int) cursor.x, text);
            cursor.x += text.length();
        }

    }

    char& getChar(unsigned int x, unsigned int y) {
        return lines[y][x];
    }
} Buffer;

#endif
