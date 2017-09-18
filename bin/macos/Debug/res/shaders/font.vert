
#version 120

attribute vec4 position;
varying vec2 texCoord;

void main(void) {
    gl_Position = vec4(position.xy, 1.0, 1.0);
    
    texCoord = position.zw;
}