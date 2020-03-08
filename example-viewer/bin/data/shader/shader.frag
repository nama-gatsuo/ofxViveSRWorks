#version 400

uniform sampler2DRect tex;

in vec2 vTexCoord;
out vec4 outputColor;

void main(){

    vec3 c = texture(tex, vTexCoord).rgb;

    outputColor = vec4(vec3(c.r * 0.005), 1.);
}
