#version 330 core

out vec4 FragColor;
in vec2 Tcoor;

uniform sampler2D tex0;
uniform sampler2D diffuse_0;

uniform sampler2D emissionMap0;
uniform float time;

uniform vec3 light_color;



void main(){
    
    vec4 col = texture(diffuse_0,Tcoor);// + vec4(0.0,0.1,1.0,0.4);
    //col.a=0.2;
    
    FragColor = col + light_color;
    //FragColor =vec4(1.0,0.0,0.0,0.5);
}