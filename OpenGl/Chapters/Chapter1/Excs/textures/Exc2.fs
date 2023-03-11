#version 410 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;


uniform float percentagaMix = 0.0;

void main()
{
    // Para poner usar ourColor y la de la textura multiplicamos el color por la textura
    // FragColor = texture(texture1, texCoord) * vec4(ourColor, 0.0); 
    FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), percentagaMix);
}