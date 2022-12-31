// openGLtestLighting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include<glad/glad.h>
#include<glfw/glfw3.h>
#include<glm/glm/glm.hpp>
#include<vector>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<glm/glm/gtc/type_ptr.hpp>
#include"shader.h"
#include"camera.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
#include"modelPremade.h"
#include "geometry.h"
#include "terrain.h"
#include "Light.h"




const unsigned int SCR_WIDTH =800;
const unsigned int SCR_HEIGHT =600;
float deltatime = 0.0f;
float lastTime = 0.0f;
float lastX = (float)SCR_WIDTH / 2;
float lastY = (float)SCR_HEIGHT / 2;
bool mouseFirst = true;
glm::vec3 lightPos = glm::vec3(0.5f, 1.5f, 2.0f);
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

void frame_buffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow*);
unsigned int loadCubemap(std::vector<std::string>&,const char*);
unsigned int loadTexture(const char*);

Camera camera(glm::vec3(0.0f,2.0f,3.0f));

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //Shader
   
   

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Neon City", NULL, NULL);

    if (window==NULL) {
        std::cout << "failed to create Window";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout<<"GLAD::LOAD ERROR";
        return -1;
    }
    
    Shader shader("shaders/vertex.glsl", "shaders/fragment_simple.fs");
    Shader modelShader("vertex.vs","fragment.fs");
    Shader planeShader("shaders/vertex.glsl","shaders/fragment_model.fs");
    Shader biomeShader("shaders/vertex.glsl","shaders/fragmentPlane.fs");
    Shader lightShader("shaders/vertex.glsl","shaders/fragment_light.fs");

    //flip image before loading
    stbi_set_flip_vertically_on_load(true);

    //Model floorModel("assets/models/backpack/backpack.obj");

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //cube
    float cube[] = {
                          //Textures        //Normals
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f, //back cube
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, //front cube
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f, //left face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, //right face
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f, //down face
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //top face
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    };

    float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float)*3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5*sizeof(float)));
    glEnableVertexAttribArray(2);

    //Textures
    


    unsigned int cubeT;
    cubeT = TextureFromFile("glass.png","assets");
//Cube map
    std::vector<std::string> faces = {
    "right.jpg",
    "left.jpg",
    "top.jpg",
    "bottom.jpg",
    "front.jpg",
    "back.jpg"
};

    unsigned int cubeVAO,cubeBAO;
    glGenVertexArrays(1,&cubeVAO);
    glBindVertexArray(cubeVAO);
    glGenBuffers(1,&cubeBAO);
    glBindBuffer(GL_ARRAY_BUFFER,cubeBAO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(skyboxVertices),skyboxVertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    //unsigned int cubemapTexture = loadCubemap(faces,"skyboxes/jajlands1");

    glm::mat4 projection = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//Geometry
    Geometry quad = Geometry("QUAD");

//Light Source

    Light light = Light(glm::vec3(0.0f,10.0f,0.0f));
    light.setColor(glm::vec3(1.0f,0.0f,0.0f));
    light.setAmbient(glm::vec3(0.1f,0.1f,0.1f));
    light.setDiffuse(glm::vec3(0.5f,0.5f,0.5f));
    light.setSpecular(glm::vec3(1.0f,1.0f,1.0f));

//Terrain

Terrain plane(10,10);
plane.setShaderPointer(biomeShader);
//Emission Textures
    unsigned int emissionMap0 = TextureFromFile("emissionMap.jpg","assets/maps/emission");    
//Texture unit
    shader.use();
    glUniform1i(glGetUniformLocation(shader.ID, "diffuse_0"), 0);
    glUniform1i(glGetUniformLocation(shader.ID, "emissionMap0"), 1);
    planeShader.use();
    glUniform1i(glGetUniformLocation(planeShader.ID, "diffuse_0"), 0);
    biomeShader.use();
    glUniform1i(glGetUniformLocation(biomeShader.ID, "diffuse_0"), 0);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    //LOOP
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        float currentTime = glfwGetTime();
        deltatime = currentTime - lastTime;
        lastTime = currentTime;

        glClearColor(0.1f, 0.1f, 0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        shader.use();
        glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        //model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
        
        glm::mat4 view = camera.getViewMatrix();
        
        /*glUniform3fv(glGetUniformLocation(shader.ID, "lightColor"),1, &lightColor[0]);
        glUniform3f(glGetUniformLocation(shader.ID, "objColor"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);*/
        glUniform3fv(glGetUniformLocation(shader.ID, "viewPos"),1,&camera.Position[0]);
        
        
        
//Drawing

       
        //view = camera.getViewMatrix();
        //model = glm::mat4(1.0f);

        modelShader.use();
        glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"),1,GL_FALSE,glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));

        planeShader.use();
        glUniformMatrix4fv(glGetUniformLocation(planeShader.ID, "model"),1,GL_FALSE,glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(planeShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(planeShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));

        biomeShader.use();
        glUniformMatrix4fv(glGetUniformLocation(biomeShader.ID, "model"),1,GL_FALSE,glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(biomeShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(biomeShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        

        shader.use();
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"),1,GL_FALSE,glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        
        lightShader.use();
        lightShader.setMat4("model",model);
        lightShader.setMat4("projection",projection);
        lightShader.setMat4("view",view);

        //Light
        lightShader.setVec3("light_color",light.getColor());
        glBindVertexArray(VAO);
        model = glm::translate(model,light.getPosition());
        lightShader.setMat4("model",model);
        glBindTexture(GL_TEXTURE_2D,0);
        glDrawArrays(GL_TRIANGLES,0,36);
        //set time unifrom
        shader.use();
        glUniform1f(glGetUniformLocation(shader.ID,"time"),currentTime);
        glBindTexture(GL_TEXTURE_2D,cubeT);
        glBindVertexArray(VAO);
    
        model = glm::mat4(1.0f);
        shader.setMat4("model",model);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,emissionMap0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        biomeShader.use();
        biomeShader.setVec3("light.ambient",light.getAmbience());
        biomeShader.setVec3("light.diffuse",light.getDiffuse());
        biomeShader.setVec3("light.color",light.getColor());
        biomeShader.setVec3("light.position",light.getPosition());
        glBindTexture(GL_TEXTURE_2D,0);
        model = glm::mat4(1.0f);
        model = glm::translate(model,glm::vec3(2.0f,0.0f,0.0f));
        biomeShader.setMat4("model",model);
        glBindVertexArray(quad.getVAO());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,cubeT);        
        glDrawArrays(GL_TRIANGLES,0,6);

        //modelShader.use();
        //Models  
        //floorModel.Draw(modelShader);
      
        plane.draw(planeShader);
    
     
//Skybox
        
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VAO);

    glfwTerminate();
    return 0;
}
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.processKeyMovement("FORWARD", deltatime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.processKeyMovement("BACK", deltatime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.processKeyMovement("RIGHT", deltatime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.processKeyMovement("LEFT", deltatime);
    }
}
void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (mouseFirst) {
        lastX = xpos;
        lastY = ypos;
        mouseFirst = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    
    lastX = xpos;
    lastY = ypos;
    camera.processMouseMovement(&xoffset,&yoffset);
}

unsigned int loadCubemap(std::vector<std::string>& faces,const char* dirname){
    unsigned int textureId;
    glGenTextures(1,&textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP,textureId);

    unsigned char* data;
    int width,height,nchannel;
    for(unsigned int i=0;i<faces.size();i++){
        std::string path = std::string(dirname) +"/"+ faces[i];
        data = stbi_load(path.c_str(),&width,&height,&nchannel,0);
        if(data){
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        }
        else{
            std::cout<<"ERROR LOADING CUBE MAP TEXTURE"<<std::endl;
        }
        stbi_image_free(data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureId;
}

unsigned int loadTexture(const char* path){
    unsigned int texture;
    int width,height,channels;
    unsigned char* data;

    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);

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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    else{
         std::cout<<"(loadTexture)FAILED TO LOAD IMAGE"<<std::endl;
    }
    stbi_image_free(data);

    return texture;
}