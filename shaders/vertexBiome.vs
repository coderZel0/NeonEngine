#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 Texcoor;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 offset;


out vec3 Normal;
out vec3 FragPos;

out VS_OUT{
    vec2 TexCoords;
}vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
FragPos = vec3(model* vec4(pos,1.0));
gl_Position = projection * view * vec4(FragPos,1.0);
vs_out.TexCoords = Texcoor;
Normal = mat3(transpose(inverse(model))) * normal;

}