#ifndef TERRAIN_H
#define TERRAIN_H


#include<iostream>
#include<glad/glad.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<vector>
#include "geometry.h"
#include "shader.h"
#include "utils.h"
#include<time.h>

struct Biome{
    std::vector<glm::vec3> grassBuffer;
    std::vector<glm::vec3> rockBuffer;
    std::vector<glm::vec3> flowerBuffer;
};

class Terrain{

    private:
        std::vector<float> buffer;
        std::vector<unsigned int> indices;
        int height,width;
        unsigned int VAO,BAO,EBO;
        Biome biome;
        Geometry quad = Geometry("QUAD");
        bool renderBiomes = true;
        Shader* biomeShader =nullptr;
        std::map<std::string,unsigned int> textures;

        void setIndices(){
            for(int i=0;i<height;i++){
                for(int j=0;j<width;j++){
                    indices.push_back(i*width +j);
                    indices.push_back((i+1)*width+j);
                }
            }

           
        }

        void loadMap(const char* map){

        }
        
        void initBiomeTextures(){
            string texs[5][2] = {{"grass_texture","assets/grass.png"},{"flower_texture1","assets/flower1.png"},{"flower_texture2","assets/flower3.png"},{"stone_texture",""},{"ground_texture",""}};
            for(auto &tex:texs){
                if(tex[1]!=""){
                    textures[tex[0]] = UTIL::loadTexture(tex[1].c_str(),true);
                }
                
            }
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
            initBiomeTextures();
            //quad.initTextures("assets/grass.png");
        }

        void setShaderPointer(Shader &shader){
            this->biomeShader = &shader;
        }

        void draw(Shader &shader){
            shader.use();
            glBindVertexArray(VAO);

            glDrawElements(GL_TRIANGLE_STRIP,indices.size(),GL_UNSIGNED_INT,0);
            if(renderBiomes){
                biomeShader->use();
                glm::mat4 model = glm::mat4(1.0f);
                int n = biome.grassBuffer.size();
                for(int i=0;i<n;i++){
                    model = glm::mat4(1.0f);
                    model = glm::translate(model,biome.grassBuffer[i]);
                    model = glm::translate(model,glm::vec3(0.0f,0.5f,0.0f));
                    biomeShader->setMat4("model",model);
                    quad.draw(textures["grass_texture"]);

                    model = glm::rotate(model,80.0f,glm::vec3(0.0f,1.0f,0.0f));
                    biomeShader->setMat4("model",model);
                    quad.draw(textures["grass_texture"]);


                    /*model = glm::scale(model,glm::vec3(0.5f,0.5f,0.0f));
                    model = glm::translate(model,glm::vec3(0.0f,-0.5f,0.0f));
                    biomeShader->setMat4("model",model);
                    quad.draw(textures["flower_texture"]);

                    model = glm::rotate(model,-80.0f,glm::vec3(0.0f,1.0f,0.0f));
                    biomeShader->setMat4("model",model);
                    quad.draw(textures["flower_texture"]);*/

                    
                    biomeShader->setFloat("time",glm::sin(glfwGetTime()));
                }
                
                n= biome.flowerBuffer.size();
                
                for(int i=0;i<n;i++){
                   
                    model = glm::mat4(1.0f);
                    model = glm::translate(model,biome.flowerBuffer[i]);
                    
                    biomeShader->setMat4("model",model);
                    quad.draw(textures["flower_texture1"]);
                   
                    model = glm::rotate(model,80.0f,glm::vec3(0.0f,1.0f,0.0f));
                    model = glm::translate(model,glm::vec3(0.6f,0.0f,0.4f));
                    biomeShader->setMat4("model",model);
                    quad.draw(textures["flower_texture1"]);
                }
                
            }
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

            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(sizeof(float)*3));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER,0);
            glBindVertexArray(0);
           
        }

        void planeTerrain(){
            std::cout<<"generating buffer"<<std::endl;

            for(int i=0;i<height;i++){
                float u,v;
                glm::vec3 offset;
                for(int j=0;j<width;j++){
                    u=j/width;
                    v=i/height;
                    buffer.push_back(-width/2.0f + j);
                    buffer.push_back(0.0f);
                    buffer.push_back((float)i);
                    buffer.push_back(u);
                    buffer.push_back(v);
                    //grass position offsets
                    offset.x = -width/2.0f + j;
                    offset.y = 0.0f;
                    offset.z = (float)i;
                    biome.grassBuffer.push_back(offset);
                    offset.x = -width/2.0f + j + 0.5f;
                    biome.grassBuffer.push_back(offset);
                    offset.x = -width/2.0f +j;
                    offset.z = i + 0.5f;
                    biome.grassBuffer.push_back(offset);
                    offset.x = -width/2.0f +j + 0.5f;
                    biome.grassBuffer.push_back(offset);

                    //flower buffer
                    
                    offset.x = rand()%width + -width/2.0f;
                    offset.y = 0.0f + 0.5f;
                    offset.z = rand()%height;
                    biome.flowerBuffer.push_back(offset);
                    
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