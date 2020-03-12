#version 420
uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
in vec4 position;
in vec4 color;
in vec4 normal;
in vec2 texcoord;

uniform float depthClip;

void main() {

    vec4 viewPos = modelViewMatrix * position;
    gl_Position = modelViewProjectionMatrix * position;
    gl_ClipDistance[0] = dot(viewPos, vec4(0, 0, 1, depthClip));
    gl_PointSize = 20.f / gl_Position.w;
}
