// shader.glsl

#version 130       // версия glsl

out vec3 color;

void main() {
    float d = 4e2;
    float l = 5e5;
    // получаем координату точки на текстуре
    float x = 6e4 * (gl_TexCoord[0].y - 0.5);

    float lambda = 5.0;
    float k = 2.0 * 3.15159 / lambda;
    float phi1 = k * length(vec2(l, x - d / 2.0));
    float phi2 = k * length(vec2(l, x + d / 2.0));
    vec2 amplitude = vec2(cos(phi1) + cos(phi2), sin(phi1) + sin(phi2));

    amplitude /= 2.0;
    float intensity = dot(amplitude, amplitude);
    color = vec3(intensity);
}
