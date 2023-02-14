#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glad/glad.h>
#include<glfw/glfw3.h>
#include<glm/glm/glm.hpp>
#include "utils.h"
#include "shader.h"

const float quad[] ={
        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,    0.0f,0.0f,-1.0f,
        0.0f, -0.5f,  0.0f,  0.0f,  1.0f,    0.0f,0.0f,-1.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,    0.0f,0.0f,-1.0f,

        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,    0.0f,0.0f,-1.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,    0.0f,0.0f,-1.0f,
        1.0f,  0.5f,  0.0f,  1.0f,  0.0f,     0.0f,0.0f,-1.0f
};



class Geometry{
    private:
        unsigned int VAO;
        unsigned int BAO,textureID;
        
        int sizeBuffer;
        const float* buffer_ptr;
        bool haveTextures = false;

        void loadGeometry(const char* type){
            if(type=="QUAD"){
                sizeBuffer = sizeof(quad);
                buffer_ptr = quad;
            }
            glGenVertexArrays(1,&VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1,&BAO);
            glBindBuffer(GL_ARRAY_BUFFER,BAO);
            glBufferData(GL_ARRAY_BUFFER,sizeBuffer,buffer_ptr,GL_STATIC_DRAW);

            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(sizeof(float)*3));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(sizeof(float)*5));
            glEnableVertexAttribArray(2);
            
            glBindBuffer(GL_ARRAY_BUFFER,0);
            glBindVertexArray(0);
        };
        
        
    public:
        Geometry(const char* type){
            loadGeometry(type);
        };    
        
        Geometry(std::string type){
            loadGeometry(type.c_str());
        }

        void initTextures(const char* texture){
            textureID = UTIL::loadTexture(texture,true);
            if(textureID) haveTextures=true;

        }

        unsigned int getVAO(){
            return VAO;
        }

        unsigned int getTextureId(){
            return textureID;
        }

        void draw(){
            glBindVertexArray(VAO);
            
            glBindTexture(GL_TEXTURE_2D,textureID);
            
            glDrawArrays(GL_TRIANGLES,0,6);
        }
        
        void draw(unsigned int &textureId){
            glBindVertexArray(VAO);
            glBindTexture(GL_TEXTURE_2D,textureId);
            glDrawArrays(GL_TRIANGLES,0,6);
        }

        void draw(Shader &shader){
            shader.use();

            glBindVertexArray(VAO);
            
            glBindTexture(GL_TEXTURE_2D,textureID);
            
            glDrawArrays(GL_TRIANGLES,0,6);
        }

        void drawInstanced(int instances){
            glBindVertexArray(VAO);
            glBindTexture(GL_TEXTURE_2D,textureID);
            glDrawArraysInstanced(GL_TRIANGLES,0,6,instances);
        }
};


#endif