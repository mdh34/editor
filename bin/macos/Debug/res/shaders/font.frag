#version 330 core

in vec2 texCoord;

out vec4 fragColor;

uniform vec4 colour;
uniform sampler2D texSampler;

void main() {
    // fragColor = vec4(1, 1, 1, texture(texSampler, texCoord).r);
    fragColor = vec4(colour.xyz, texture(texSampler, texCoord).r);
}
