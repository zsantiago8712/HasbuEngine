#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextureCoords;


out vec2 TextureCoords;
out vec3 FragPosition;
out vec3 Normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


void main()
{
    // TextureCoords = aTextureCoords;
    // gl_Position = projection * view * model * vec4(aPos, 1.0f);
    
    FragPosition = vec3(model * vec4(aPos, 1.0f));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TextureCoords = aTextureCoords;
    gl_Position = projection * view * model * vec4(aPos, 1.0f);

}


