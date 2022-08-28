#version 330 core

in vec2 Tcoor;

uniform sampler2D diffuse_0;

out vec4 FragColor;

void main(){
    FragColor = vec4(0.0f,0.9f,0.2f,1.0f);
}