#ifndef MESH_H
#define MESH_H

#include<iostream>
#include <glad/glad.h>
#include<glfw/glfw3.h>
#include<glm/glm/glm.hpp>
#include <vector>
#include"shaderP.h"

struct Vertex{
    glm::vec3 Position;
    glm::vec2 texCoor;
    glm::vec3 Normal;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture{
    unsigned int id;
    std::string type;
    std::string path;
};


class Mesh{
    private:
        unsigned int VAO,EBO;
        unsigned int BAO;
        std::vector<Vertex> vertices;
        std::vector<Texture> textures;
        std::vector<unsigned int> indices;

    void loadMesh(){
        glGenVertexArrays(1,&VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1,&BAO);
        glBindBuffer(GL_ARRAY_BUFFER,BAO);
        glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(Vertex),&vertices[0],GL_STATIC_DRAW);

        glGenBuffers(1,&EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(unsigned int),&indices[0],GL_STATIC_DRAW);

        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(offsetof(Vertex,texCoor)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(offsetof(Vertex,Normal)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindVertexArray(0);
    };

    public:
        Mesh(std::vector<Vertex> vertices,std::vector<Texture> textures,std::vector<unsigned int> indices){
            this->vertices = vertices;
            this->textures = textures;
            this->indices = indices;

            loadMesh();
        };

        void Draw(Shader &shader){
            int diffuseN =0,specularN=0;
        

            for(unsigned int i=0;i<textures.size();i++){
                glActiveTexture(GL_TEXTURE0 + i);

                std::string name = textures[i].type;
                if(textures[i].type == "diffuse"){
                    name += "_"+ std::to_string(diffuseN++);
                }
                else if(textures[i].type =="specular"){
                    name += "_"+ std::to_string(specularN++);
                }

                shader.setInt((name).c_str(),i);
                glBindTexture(GL_TEXTURE_2D,textures[i].id);
                
            }            

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);

            glActiveTexture(GL_TEXTURE0);
            glBindVertexArray(0);
        }
};

#endif