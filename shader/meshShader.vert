#version 420
uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
in vec4 position;
in vec4 color;
in vec4 normal;
in vec2 texcoord;

void main() {
    gl_Position = modelViewProjectionMatrix * position;
}
