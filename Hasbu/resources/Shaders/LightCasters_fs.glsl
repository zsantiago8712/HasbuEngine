#version 410 core


struct Material {

    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;

    float shininess;

};


struct Light {

    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;


    float constant;
    float linear;
    float quadratic;


};



in vec3 FragPosition;
in vec3 Normal;
in vec2 TextureCoords;



uniform Material material;
uniform Light light; 
uniform vec3 viewPosition;



out vec4 FragColor;

void main()
{

    float distance = length(light.direction - FragPosition);
    float attenuation = 1.0f/ (light.constant + light.linear * distance + light.quadratic * pow(distance, 2));

    vec3 ambient = light.ambient * texture(material.diffuse, TextureCoords).rgb;
    ambient *= attenuation;

    vec3 norm = normalize(Normal);
    vec3 ligthDirection = normalize(-light.direction);
    float diff = max(dot(norm, ligthDirection), 0.0f);
    vec3 diffuse =  light.diffuse * diff * texture(material.diffuse, TextureCoords).rgb;
    diffuse *= attenuation; 

    vec3 viewDirection = normalize(viewPosition - FragPosition);
    vec3 reflectDirection = reflect(-ligthDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TextureCoords).rgb;
    specular *= attenuation;
    
    vec3 emission = light.diffuse * diff * texture(material.emission, TextureCoords).rgb;
    emission *= attenuation;


    vec3 result = ambient + diffuse + specular + emission;

    FragColor = vec4(result, 1.0f);
}
