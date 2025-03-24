#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec3 VertexColor;

uniform vec3 modelColor;
uniform vec3 LightDir; // should be normalized and in view space
uniform mat4 V;
uniform bool useLighting;

out vec4 FragColor;

void main()
{
    if (!useLighting) {
        FragColor = vec4(modelColor, 1.0); // Render without lighting
        return;
    }

    // Phong lighting components
    vec3 ambientColor = vec3(0.2);
    vec3 diffuseColor = modelColor;
    vec3 specularColor = vec3(1.0);

    vec3 norm = normalize(Normal); // Normalize input normal
    vec3 lightDir = normalize(LightDir); // Light direction (view space)
    vec3 viewDir = normalize(-FragPos); // camera is at origin in view space // View direction
    vec3 reflectDir = reflect(-lightDir, norm); // Reflect direction

    // Compute components
    float diff = max(dot(norm, lightDir), 0.0);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64.0);

    vec3 finalColor = ambientColor + diffuseColor * diff + specularColor * spec;
    FragColor = vec4(finalColor, 1.0);
}

// 16:02