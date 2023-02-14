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
    
    vec4 texel = texture(diffuse_0,Tcoor);

    if(texel.a<0.1){
        discard;
    }

    
    //ambient
    vec3 ambience = light.ambient  * light.color;

    //diffuse
    float diff = max(dot(lightDir,Normal),0);
    vec3 diffuse = light.diffuse * diff * light.color;

    FragColor = texel * vec4((ambience+diffuse),1.0);
}