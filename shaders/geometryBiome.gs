#version 330 core

layout (points) in;
layout (points,max_vertices=1) out;


out vec2 Tcoor;

in VS_OUT{
    vec2 TexCoords;
}gs_in[];

void main(){
   

    //gl_Position = gl_in[0].gl_Position + vec4(0.3,0.0,-0.5,0.0);
    //Tcoor = gs_in[0].TexCoords;
    //EmitVertex();

    gl_Position = gl_in[0].gl_Position;
    Tcoor = gs_in[0].TexCoords;
    EmitVertex();
    
    /*gl_Position = gl_in[0].gl_Position;// + vec4(0.0,0.0,-0.5,0.0);
    Tcoor = gs_in[0].TexCoords;
    EmitVertex();*/

    EndPrimitive();
}