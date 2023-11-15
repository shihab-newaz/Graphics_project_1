#ifndef directionalLight_h
#define directionalLight_h

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"


class DirectionalLight {
public:
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;


    DirectionalLight(float posX, float posY, float posZ, float ambR, float ambG, float ambB, float diffR, float diffG, float diffB, float specR, float specG, float specB) {

        position = glm::vec3(posX, posY, posZ);
        ambient = glm::vec3(ambR, ambG, ambB);
        diffuse = glm::vec3(diffR, diffG, diffB);
        specular = glm::vec3(specR, specG, specB);

    }
    void setUpDirectionalLight(Shader& lightingShader)
    {

        lightingShader.use();
        lightingShader.setVec3("dirLight.position", position);
        lightingShader.setVec3("dirLight.ambient", ambientOn * ambient);
        lightingShader.setVec3("dirLight.diffuse", diffuseOn * diffuse);
        lightingShader.setVec3("dirLight.specular", specularOn * specular);


    }
    void turnOff()
    {
        ambientOn = 0.0;
        diffuseOn = 0.0;
        specularOn = 0.0;
    }
    void turnOn()
    {
        ambientOn = 1.0;
        diffuseOn = 1.0;
        specularOn = 1.0;
    }
    void turnAmbientOn()
    {
        ambientOn = 1.0;
    }
    void turnAmbientOff()
    {
        ambientOn = 0.0;
    }
    void turnDiffuseOn()
    {
        diffuseOn = 1.0;
    }
    void turnDiffuseOff()
    {
        diffuseOn = 0.0;
    }
    void turnSpecularOn()
    {
        specularOn = 1.0;
    }
    void turnSpecularOff()
    {
        specularOn = 0.0;
    }
private:
    float ambientOn = 1.0;
    float diffuseOn = 1.0;
    float specularOn = 1.0;
};

#endif /* directionalLight_h */
