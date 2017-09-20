
#version 330

in vec2 texCoord;

uniform sampler2D texSampler;
uniform vec4 colour;

out vec4 fragColor;

void main() {
    fragColor = vec4(1, 1, 1, texture(texSampler, texCoord).r) * colour;
}
