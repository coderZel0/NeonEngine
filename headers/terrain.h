#ifndef TERRAIN_H
#define TERRAIN_H


#include<iostream>
#include<glad/glad.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<vector>


struct Biome{
    std::vector<float> grassBuffer;
    std::vector<float> rockBuffer;
    std::vector<float> flowerBuffer;
};

class Terrain{

    private:
        std::vector<float> buffer;
        std::vector<unsigned int> indices;
        int height,width;
        unsigned int VAO,BAO,EBO;
        Biome biomebuffers;

        void setIndices(){
            for(int i=0;i<height;i++){
                for(int j=0;j<width;j++){
                    indices.push_back(i*width +j);
                    indices.push_back((i+1)*width+j);
                }
            }

            for(int n:indices){
                std::cout<<n;
            }
        }

        void loadMap(const char* map){

        }
    public:

        Terrain(const char* height_map){
            loadMap(height_map);
        }

        Terrain(int width, int height){
            this->width = width;
            this->height = height;
            
            std::cout<<width<<"-"<<height;
            
            planeTerrain();
        }

        
        void draw(){
            glBindVertexArray(VAO);

            glDrawElements(GL_TRIANGLE_STRIP,indices.size(),GL_UNSIGNED_INT,0);
        }

        void initVertexArrays(){
            glGenVertexArrays(1,&VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1,&BAO);
            glBindBuffer(GL_ARRAY_BUFFER,BAO);

            glBufferData(GL_ARRAY_BUFFER,buffer.size()*sizeof(float),&buffer[0],GL_STATIC_DRAW);

            glGenBuffers(1,&EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(float),&indices[0],GL_STATIC_DRAW);

            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),0);
            glEnableVertexAttribArray(0);

           
        }

        void planeTerrain(){
            std::cout<<"generating buffer"<<std::endl;

            for(int i=0;i<height;i++){
                for(int j=0;j<width;j++){
                    buffer.push_back(-width/2.0f + j);
                    buffer.push_back(0.0f);
                    buffer.push_back((float)i);
                }
            }

            //setIndices();
            for(unsigned int i=0;i<height;i++){
                for(unsigned int j=0;j<width;j++){
                    indices.push_back(i*width +j);
                    indices.push_back((i+1)*width+j);
                }
            }

            initVertexArrays();
            
        }
};

#endif