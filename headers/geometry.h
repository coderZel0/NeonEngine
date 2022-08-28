#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glad/glad.h>
#include<glfw/glfw3.h>
#include<glm/glm/glm.hpp>


const float quad[] ={
    -0.5f,0.5f,0.0f,0.0f,1.0f,
    -0.5f,0.0f,0.0f,0.0f,0.0f,
    0.5f,0.5f,0.0f,1.0f,1.0f,
    0.5f,0.5f,0.0f, 1.0f,1.0f,
    -0.5f,0.0f,0.0f, 0.0f,0.0f,
    0.5f,0.0f,0.0f, 1.0f,0.0f
};

class Geometry{
    private:
        unsigned int VAO;
        unsigned int BAO;
        int sizeBuffer;
        const float* buffer_ptr;

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

            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(sizeof(float)*3));
            glEnableVertexAttribArray(1);
            
            glBindBuffer(GL_ARRAY_BUFFER,0);
            glBindVertexArray(0);
        };
        
    public:
        Geometry(const char* type){
            loadGeometry(type);
        };    

        unsigned int getVAO(){
            return VAO;
        }
};


#endif