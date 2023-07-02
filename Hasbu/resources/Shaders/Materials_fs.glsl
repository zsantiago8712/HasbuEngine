#version 410 core



struct Material {

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;

};


struct Ligth {

    // Posicion
    vec3 position;

    // Color de Luz ambiental
    vec3 ambient;

    // Color de Luz diffuse
    vec3 diffuse;

    // Color de Luz specular
    vec3 specular;

};



// Vector perpendicualr al Fragment surface
in vec3 Normal;

// Posicion del Fragment surface
in vec3 FragPosition;

in float Selection;


// Vector que apunta al target que la camara esta viendo
uniform vec3 viewPosition;


uniform Material material;
uniform Ligth light;



// Color resultante (iluminacion)
out vec4 FragColor;


void main()
{
    // Color de la luz ambiental
    vec3 ambient = light.ambient * material.ambient;

    // Normalizar el vector perpendicular
    vec3 norm = normalize(Normal);

    // La dirrecion de la luz
    vec3 ligthDirection = normalize(light.position - FragPosition);

    // El angulo entre el vector perpendicular y la direecion de la luz
    float diff = max(dot(norm, ligthDirection), 0.0f);

    // Color de Luz Diffuse ilumination
    vec3 diffuse = light.diffuse * (diff * material.diffuse);


    // La direccion del target donde apunta la camara
    vec3 viewDirection = normalize(viewPosition - light.position);

    // La direccion del "reflejo"
    vec3 reflectDirection = reflect(-ligthDirection, norm);

    // El angulo entre la direccion del target  y la direccion del reflejo
    // y tambien se calcula el brillo del material con pow
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    
    // Color de luz Specular ilumination
    vec3 specular = light.specular * (spec * material.specular);


    vec3 result = ambient + diffuse + specular; 
    FragColor = vec4(result, 1.0f);
    
    
}
