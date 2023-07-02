#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aText;


out vec3 FragPosition;
out vec3 Normal;
out vec2 TextureCoords;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;



void main()
{
    FragPosition = vec3(model * vec4(aPos, 1.0f));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TextureCoords = aText;

    gl_Position = projection * view * vec4(FragPosition, 1.0f);

}
