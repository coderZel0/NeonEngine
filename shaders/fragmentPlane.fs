#version 330 core

in vec2 Tcoor;

uniform sampler2D diffuse_0;

out vec4 FragColor;

void main(){
    FragColor = texture(diffuse_0,Tcoor);
}