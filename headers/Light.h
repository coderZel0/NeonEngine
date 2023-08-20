#ifndef LIGHT_H
#define LIGHT_H

#include<iostream>
#include<glad/glad.h>
#include<glm/glm/glm.hpp>



class Light{
    private:
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        glm::vec3 color;
        glm::vec3 position;

    public:
        Light(glm::vec3 position){
            this->position = position;
        }    

        Light(glm::vec3 position,glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,glm::vec3 color){
            this->position = position;
            this->ambient = ambient;
            this->diffuse = diffuse;
            this->specular = specular;
            this->color = color;
        }

        void setAmbient(glm::vec3 ambience)
        {
            this->ambient = ambience;
        }

        void setDiffuse(glm::vec3 diffuse)
        {
            this->diffuse = diffuse;
        }

        void setSpecular(glm::vec3 specular)
        {
            this->specular = specular;
        }

        glm::vec3 getPosition()
        {
            return this->position;
        }

        void setPosition(glm::vec3 position)
        {
            this->position = position;
        }

        void setColor(glm::vec3 color)
        {
            this->color = color;
        }

        glm::vec3 getColor()
        {
            return this->color;
        }

        glm::vec3 getAmbience()
        {
            return this->ambient;
        }

        glm::vec3 getDiffuse()
        {
            return this->diffuse;
        }

        glm::vec3 getSpecular()
        {
            return this->specular;
        }
};





#endif