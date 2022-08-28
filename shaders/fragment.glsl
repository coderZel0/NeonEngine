#version 330 core

out vec4 FragColor;
in vec2 Tcoor;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D Tex0;
uniform samplerCube cubeMap;
uniform vec3 lightColor;
uniform vec3 objColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
//Diffuse
/*vec3 norm = normalize(Normal);
vec3 lightDir = normalize(lightPos - FragPos);
float diff = max(dot(norm,lightDir),0.0f);
vec3 diffuse = diff * lightColor;
//Ambient
float ambientStrength = 0.1;
vec3 ambient = ambientStrength * lightColor;
//Specular
float specularStrength = 0.5;
vec3 viewDir = normalize(viewPos - FragPos);
vec3 reflectDir = reflect(-lightDir,norm);
float spec = pow(max(dot(reflectDir,viewDir),0.0f),32);
vec3 specular = spec * lightColor * specularStrength;

vec3 color = (diffuse + ambient + specular) * objColor;*/

vec3 I = normalize(FragPos - viewPos);
//vec3 R = reflect(I,normalize(Normal));

float ratio = 1.0/1.33;
vec3 R = refract(I,normalize(Normal),ratio);
FragColor = texture(cubeMap,R);// * vec4(color,1.0);

}