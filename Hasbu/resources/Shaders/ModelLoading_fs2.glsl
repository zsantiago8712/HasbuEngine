#version 410 core

in vec2 TextureCoords;

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
};

uniform Material material;

void main()
{
    FragColor = texture(material.diffuse, TextureCoords);
}

