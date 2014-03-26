#pragma once
#include "voxelBuffer.h"
#include "glm/glm.hpp"
#include "camera.h"
#include "EasyBMP.h"

class Raymarch {
 private:
    VoxelBuffer*buffer;
    Camera* cam;
    glm::vec3 eye;
    glm::vec3 materialColor;
    glm::vec3 backgroundColor;
    glm::vec3 lightColor;
    glm::vec3 lightPosition;
	glm::vec3 displacement;
 public:
    Raymarch(VoxelBuffer*buffer,Camera*camera, glm::vec3 e, glm::vec3 mat, glm::vec3 bg, glm::vec3 lightColor, glm::vec3 lightPosition, glm::vec3 displacement);
    glm::vec3 getColor(int x_coor, int y_coor, float step, glm::vec3 dimensions);
    void setLight(glm::vec3 v, float step);
};
