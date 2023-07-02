#version 410 core 



struct Material {
  
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;

    float shininess;
};


struct Light {

    vec3 direction;
    vec3 position;
    float cutOff;
    float outerCutOff;
    

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
    
    vec3 lightDirection = normalize(light.position - FragPosition);
        
    float theta  = dot(lightDirection, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);


    vec3 ambient = light.ambient * texture(material.diffuse, TextureCoords).rgb;



    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDirection), 0.0f);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TextureCoords).rgb;


    vec3 viewDirection = normalize(viewPosition - FragPosition);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TextureCoords).rgb;


    vec3 emission = light.diffuse * diff * texture(material.emission, TextureCoords).rgb;


    float distance = length(light.direction - FragPosition);
    float attenation =  1.0f / (light.constant * light.linear * distance + light.quadratic * pow(distance, 2));   

    diffuse *= intensity;
    specular *= intensity;
    emission *= intensity;

    diffuse *= attenation;
    specular *= attenation;
    emission *= attenation;

    vec3 result = ambient + diffuse + specular + emission;
    FragColor = vec4(result, 1.0f); 

}
