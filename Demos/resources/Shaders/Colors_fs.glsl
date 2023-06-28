#version 410 core


#define AMBIENT 0.0f
#define DIFFUSE 1.0f
#define SPECULAR 2.0f

in vec3 Normal;
in vec3 FragPos;

in float Selection;

uniform vec3 objectColor;
uniform vec3 lightColor;

//NOTE: CON esto se claclula Phong Shading pero con view space
// in vec3 lightPosition;


uniform vec3 lightPosition;
uniform vec3 lightPosition2;
uniform float ambientStrength;

uniform vec3 viewPosition;
uniform float specularStrength;


out vec4 FragColor;


//TODO: crear una manera de poder elegir en tiempo real la iluminacion
void main()
{

    vec3 result;
    //NOTE: asi se calcula em ambient ilumination PT.1
    // Esto calcula el colo de la luz
    vec3 ambient = ambientStrength * lightColor;
    
    
    if (Selection == AMBIENT) {

        // Esto calcula el color del objeto cunado rebota la luz
        result = ambient * objectColor;

    } else if(Selection == DIFFUSE) {
        //NOTE: asi se calcula el diffuse ilumination PT.

        // Normaliza el vector Normal
        vec3 norm = normalize(Normal);

        // Calcula la direccion de la luz
        vec3 lightDirection = normalize(lightPosition - FragPos);
        vec3 lightDirection2 = normalize(lightPosition2 - FragPos);

        // Calcula el angulo del la direccion de luz con el Normla vector normalizado
        float diff = max(dot(norm, lightDirection), 0.0);
        float diff2 = max(dot(norm, lightDirection2), 0.0);

        // Calcula el color de luz
        vec3 diffuse = diff * lightColor;
        vec3 diffuse2 = diff2 * lightColor;

        // Calcula el color del objeto cunado la luz rebota en el 
        result = (ambient + diffuse2 + diffuse) * objectColor;
    }else if(Selection == SPECULAR) {

        // Normaliza el vector Normal
        vec3 norm = normalize(Normal);

        // Calcula la direccion de la luz
        vec3 lightDirection = normalize(lightPosition - FragPos);
        vec3 lightDirection2 = normalize(lightPosition2 - FragPos);

        // Calcula el angulo del la direccion de luz con el Normla vector normalizado
        float diff = max(dot(norm, lightDirection), 0.0);
        float diff2 = max(dot(norm, lightDirection2), 0.0);

        // Calcula el color de luz
        vec3 diffuse = diff * lightColor;
        vec3 diffuse2 = diff2 * lightColor;

        //
        vec3 viewDir = normalize(viewPosition - FragPos);


        vec3 reflectDir = reflect(-lightDirection, norm);
        vec3 reflectDir2 = reflect(-lightDirection2, norm);

        
        float spec = pow(max(dot(viewDir, reflectDir), 0), 32);
        float spec2 = pow(max(dot(viewDir, reflectDir2), 0), 32);

        vec3 specular = specularStrength * spec * lightColor;
        vec3 specular2 = specularStrength * spec2 * lightColor;

        result = (ambient + diffuse + diffuse2 + specular + specular2) * objectColor;
    }

    
    FragColor = vec4(result, 1.0f);
        
    //NOTE: Asi se calcula el color de un objeto 
    // FragColor = vec4(lightColor * objectColor, 1.0f);
}
