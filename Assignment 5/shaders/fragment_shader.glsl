#version 330 core
in vec3 normal;
in vec3 light_direction;
in vec3 eye_direction;

out vec4 color;

uniform vec4 modelColor;

void main() {
    vec4 ambient = vec4(0.2, 0.2, 0.2, 1) * modelColor;
    vec4 specular = vec4(1, 1, 1, 1);
    
    float shininess = 64.0;
    
    vec3 n = normalize(normal);
    vec3 l = normalize(light_direction);
    vec3 e = normalize(eye_direction);
    vec3 r = reflect(-l, n);

    float cosTheta = max(dot(n, l), 0);
    float cosAlpha = max(dot(e, r), 0);
    
    color = ambient + (modelColor * cosTheta * 0.8) + (specular * pow(cosAlpha, shininess));
}
