#version 330 core

in vec2 Tcoor;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D diffuse_0;
uniform float time;
uniform vec3 viewPos;


out vec4 FragColor;

struct Light{
    vec3 positon;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 color;
};

uniform Light light;

void main(){
    
    vec3 lightDir = normalize(light.positon-FragPos);
    
    vec4 color = texture(diffuse_0,Tcoor);
    if(color.a<0.1){
        discard;
    }

    
    //ambient
    vec3 ambience = light.ambient * vec3(color) * light.color;

    //diffuse
    float diffuse = max(dot(lightDir,Normal),0);
    vec3 diff = light.diffuse * diffuse * light.color * vec3(color);

    FragColor = color *vec4((ambience+diff),1.0);
}