
#version 330
layout (location=0) in vec3 position;
layout (location=1) in vec2 texCoords;

uniform mat4 mvpMatrix;

out vec2 texCoord;

void main() {
    gl_Position = mvpMatrix * vec4(position, 1);
    texCoord = texCoords;
}
