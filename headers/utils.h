#ifndef UTIL_H
#define UTIL_H

#include<glad/glad.h>
#include<iostream>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif


namespace UTIL{
    unsigned int loadTexture(const char* path,bool clamp=false)
    {
        unsigned int texture;
        int width,height,channels;
        unsigned char* data;

        glGenTextures(1,&texture);
        glBindTexture(GL_TEXTURE_2D,texture);
        stbi_set_flip_vertically_on_load(false);
        data = stbi_load(path,&width,&height,&channels,0);
        GLenum format;
        if(channels==4){
            format =GL_RGBA;
        }
        else if(channels==3){
            format= GL_RGB;
        }
        else {format=GL_R;}

        
        if(data){
            
            glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,data);
            if(clamp){
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            }
            else{
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            }
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
        else{
            std::cout<<"(loadTexture)FAILED TO LOAD IMAGE"<<std::endl;
        }
        stbi_image_free(data);

        return texture;
}

}

#endif