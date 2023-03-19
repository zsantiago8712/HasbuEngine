#version 410 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;


void main()
{
    FragColor = mix(texture(texture1, texCoord) *  vec4(ourColor, 0.0), texture(texture2, texCoord) * vec4(ourColor, 0.0), 0.2);  
}