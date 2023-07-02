#version 410 core


struct Material {

    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;


};


struct Light {

    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};


in vec3 FragPosition;
in vec3 Normal;
in vec2 TextureCoords;

uniform vec3 viewPosition;

uniform Material material;
uniform Light light;



out vec4 FragColor;



void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TextureCoords).rgb;

    // dffuse 
    vec3 norm = normalize(Normal);
    vec3 ligthDirection = normalize(light.position - FragPosition);
    float diff = max(dot(norm, ligthDirection), 0.0f);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TextureCoords).rgb;

    // specular
    vec3 viewDirection = normalize(viewPosition - FragPosition);
    vec3 reflectDirection = reflect(-ligthDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TextureCoords).rgb;
    // vec3 specular = light.specular * spec * (vec3(1.0) - vec3(texture(material.specular, TextureCoords)));

        
    // vec2 textureCords = vec2(TextureCoords.x, TextureCoords.y - (2.5f * gl_FragCoord.y));

    vec3 emission = light.diffuse * diff * texture(material.emission, TextureCoords).rgb;
    
    // Result
    // vec3 result = ambient + diffuse + specular;
    vec3 result = ambient + diffuse + specular + emission;
    FragColor = vec4(result, 1.0f);

}
