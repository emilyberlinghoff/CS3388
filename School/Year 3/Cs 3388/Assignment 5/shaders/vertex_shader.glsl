#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

uniform mat4 MVP;
uniform mat4 V;

out vec3 FragPos;
out vec3 Normal;
out vec3 VertexColor;

void main()
{
    FragPos = vec3(V * vec4(position, 1.0));
    Normal = mat3(transpose(inverse(V))) * normal;
    VertexColor = color;
    gl_Position = MVP * vec4(position, 1.0);
}

// 14:33