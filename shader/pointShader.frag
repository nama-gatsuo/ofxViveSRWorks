#version 420
uniform sampler2DRect tex;
in vec2 vTexCoord;
out vec4 outputColor;

void main() {
    vec2 uv = gl_PointCoord.xy * 2.0 - 1.0;
    float d = dot(uv, uv);
    if (d > 1.) discard;

    outputColor = vec4(0);
}
