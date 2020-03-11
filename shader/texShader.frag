#version 420
uniform sampler2DRect tex;
in vec2 vTexCoord;
out vec4 outputColor;

void main() {
    vec3 color = texture(tex, vTexCoord).rgb;
    //color = ContrastSaturationBrightness(color, 1., 1.0, 1.0);
    color = pow(color, vec3(0.5)); // Gamma correction
    outputColor = vec4(color, 1.);
}
