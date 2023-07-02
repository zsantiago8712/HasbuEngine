#version 410 core

#define NR_POINT_LIGHTS 4

struct Material {

    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;

    float shininess;
};


struct DirectionalLight{
  
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};

struct PointLight {

    vec3 position;

    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
};


struct SpotLigth {

    vec3 position;
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
    
    float cutOff;
    float outerCutOff;
};



in vec3 FragPosition;
in vec3 Normal;
in vec2 TextureCoords;

uniform Material material;
uniform DirectionalLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLigth spotLight;
uniform vec3 viewPosition;

out vec4 FragColor;


vec3 calculateDirectionLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection);
vec3 calculateSpotLight(SpotLigth light, vec3 normal, vec3 fragPosition, vec3 viewDirection);

void main()
{
    vec3 normal = normalize(Normal);
    vec3 viewDirection = normalize(viewPosition - FragPosition);

    vec3 result = calculateDirectionLight(dirLight, normal, viewDirection);
    
    for(int i = 0; i < NR_POINT_LIGHTS; i++) {
        result += calculatePointLight(pointLights[i], normal, FragPosition, viewDirection);
    }

    result += calculateSpotLight(spotLight, normal, FragPosition, viewDirection);
    FragColor = vec4(result, 1.0f);
}



vec3 calculateDirectionLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
    vec3 lightDirection = normalize(-light.direction);

    float diff = max(dot(normal, lightDirection), 0.0f);
    
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);

    vec3 ambient = light.ambient * texture(material.diffuse, TextureCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TextureCoords).rgb;
    vec3 specular = light.specular * spec * texture(material.diffuse, TextureCoords).rgb;

    return (ambient + specular + diffuse);
}


vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection)
{
    vec3 lightDirection = normalize(light.position - fragPosition);


    float diff = max(dot(normal, lightDirection), 0.0f);
    vec3 reflectDirection = reflect(-lightDirection, normal);   
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);

    vec3 ambient = light.ambient * texture(material.diffuse, TextureCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TextureCoords).rgb;
    vec3 specular = light.specular * spec *texture(material.diffuse, TextureCoords).rgb;

    float distance = length(light.position - fragPosition);
    float attenuation = 1 / (light.constant + light.linear * distance + light.quadratic * pow(distance, 2));
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}



vec3 calculateSpotLight(SpotLigth light, vec3 normal, vec3 fragPosition, vec3 viewDirection)
{
    vec3 lightDirection = normalize(light.position - fragPosition);


    float diff = max(dot(normal, lightDirection), 0.0f);
    vec3 reflectDirection = reflect(-lightDirection, normal);   
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);

    vec3 ambient = light.ambient * texture(material.diffuse, TextureCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TextureCoords).rgb;
    vec3 specular = light.specular * spec * texture(material.diffuse, TextureCoords).rgb;
    vec3 emission = light.diffuse * diff * texture(material.emission, TextureCoords).rgb;


    float theta = dot(lightDirection, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

    ambient *= intensity;
    diffuse *= intensity;
    specular *= intensity;
    emission *= intensity;

    return (ambient + diffuse + specular + emission);
}
