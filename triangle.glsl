// shader.glsl

#version 130       // версия glsl

out vec3 color;

void main() {
    int n = 80;
    float a = 8e1;
    // получаем координату точки на текстуре
    vec3 p = vec3( 5e2 * (gl_TexCoord[0].xy - 0.5), 5e2);

    float lambda = 5.0;
    float k = 2.0 * 3.15159 / lambda;
    vec2 amplitude = vec2(0.0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n-i; ++j) {
            vec2 a1 = vec2(1.0, 0);
            vec2 a2 = vec2(0.5, 0.866);
            vec3 source = vec3(a * (float(i) / float(n-1) - 0.333) * a1 +
                               a * (float(j) / float(n-1) - 0.333) * a2, 0);
            float phi = k * length(p - source);
            amplitude += vec2(cos(phi), sin(phi));
        }

    amplitude /= float(n*n/4.0);
    float intensity = dot(amplitude, amplitude);
    color = vec3(intensity);
}
