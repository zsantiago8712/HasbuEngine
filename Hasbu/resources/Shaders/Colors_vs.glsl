#version 410 core

#define AMBIENT 0
#define DIFFUSE 1
#define SPECULAR 2


layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;
out float Selection;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;



uniform int selectLighting;


//NOTE: Con esto se claclula Phong Shading pero con view space
//uniform vec3 lightPosition;
//out vec3 LightPos;

void main()
{

    if (selectLighting == AMBIENT) {
        //NOTE: Formula para calcular la poscion si no usas diffuse ilumination
        gl_Position = projection * view * model * vec4(aPos, 1.0f);
    }else if (selectLighting == DIFFUSE) {
        //NOTE: esto es para diffuse ilumination
        // Calcula la posicion del Fragment Surface (el surface de tu objeto)
        FragPos = vec3(model * vec4(aPos, 1.0f));
        


        // No es bueno usar inverse el los shaders ya que es muiy pendeja la GPU para wese tipo de operaciones
        // estoy hay que hacerlo en c++ (CPU)
        // Esto corrigue el problema de que si haces un non-uniform scala (escalar usando un vector sin conmpenente w)
        // el vector resultante ya no sera perpendicular al Fragment Surface (el surface de tu objeto)
        Normal = mat3(transpose(inverse(model))) * aNormal;
        

    
        //NOTE: Formula para calcular la poscion si usas diffuse ilumination
        gl_Position = projection * view * vec4(FragPos, 1.0f);


        //NOTE: Con esto se claclula Phong Shading pero con view space
        /*
        FragPos = vec3(view * model * vec4(aPos, 1.0f));
        Normal = mat3(transpose(inverse(view * model))) * aNormal;
        LightPos = vec3(view * vec4(lightPosition, 1.0));
        gl_Position = projection * view * model * vec4(FragPos, 1.0f);
        */



    }else if(selectLighting == SPECULAR) {


        //NOTE: esto es para diffuse ilumination
        // Calcula la posicion del Fragment Surface (el surface de tu objeto)
        FragPos = vec3(model * vec4(aPos, 1.0f));


        // No es bueno usar inverse el los shaders ya qu e es muiy pendeja la GPU para wese tipo de operaciones
        // estoy hay que hacerlo en c++ (CPU)

        // Esto corrigue el problema de que si haces un non-uniform scala (escalar usando un vector sin conmpenente w)
        // el vector resultante ya no sera perpendicular al Fragment Surface (el surface de tu objeto)
        Normal = mat3(transpose(inverse(model))) * aNormal;


        //NOTE: Formula para calcular la poscion si usas diffuse ilumination
        gl_Position = projection * view * vec4(FragPos, 1.0f);



        //NOTE: Con esto se claclula Phong Shading pero con view space
        /*FragPos = vec3(view * model * vec4(aPos, 1.0f));


        // No es bueno usar inverse el los shaders ya qu e es muiy pendeja la GPU para wese tipo de operaciones
        // estoy hay que hacerlo en c++ (CPU)

        // Esto corrigue el problema de que si haces un non-uniform scala (escalar usando un vector sin conmpenente w)
        // el vector resultante ya no sera perpendicular al Fragment Surface (el surface de tu objeto)
        // Normal = mat3(transpose(inverse(model))) * aNormal;
        Normal = mat3(transpose(inverse(view * model))) * aNormal;

        LightPos = vec3(view * vec4(lightPosition, 1.0));

        //NOTE: Formula para calcular la poscion si usas diffuse ilumination
        gl_Position = projection * view * model * vec4(FragPos, 1.0f);
        */
    }
    

    Selection = float(selectLighting);
}
