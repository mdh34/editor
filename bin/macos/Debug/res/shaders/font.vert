
#version 330
layout (location=0) in vec4 coords;

uniform mat4 mvpMatrix;

out vec2 texCoord;

void main() {
    gl_Position = mvpMatrix * vec4(coords.xy, 0, 1);
    texCoord = coords.zw;
}
