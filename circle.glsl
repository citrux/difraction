// shader.glsl

#version 130       // версия glsl

out vec3 color;

void main() {
    int n = 80;
    float a = 4e1;
    // получаем координату точки на текстуре
    vec3 p = vec3( 10e4 * (gl_TexCoord[0].xy - 0.5), 5e4);

    float lambda = 5.0;
    float k = 2.0 * 3.15159 / lambda;
    vec2 amplitude = vec2(0.0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            vec3 source = vec3(a * float(i) / float(n-1) - 0.5 * a,
                               a * float(j) / float(n-1) - 0.5 * a, 0);
            if (4.0*dot(source, source) < a*a) {
            float phi = k * length(p - source);
            amplitude += vec2(cos(phi), sin(phi));
            }
        }

    amplitude /= float(n*n/4.0);
    float intensity = dot(amplitude, amplitude);
    color = vec3(intensity);
}
