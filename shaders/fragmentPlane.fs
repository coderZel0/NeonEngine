#version 330 core

in vec2 Tcoor;

uniform sampler2D diffuse_0;

out vec4 FragColor;

void main(){
    vec4 color = texture(diffuse_0,Tcoor);
    if(color.a<0.1){
        discard;
    }
    FragColor = color;
}