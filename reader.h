#ifndef READER
#define READER
#include "glm/glm.hpp"
#include <cmath>
#include "perlin.h"
#include "voxelbuffer.h"

class Reader {
private:
    float delt;
    float step;
    int x;
    int y;
    int z;
    float bgRed;
    float bgGreen;
    float bgBlue;
    float materialRed;
    float materialGreen;
    float materialBlue;
    char* fileName;
    int width;
    int height;
    glm::vec3 eye;
    glm::vec3 viewDirection;
    glm::vec3 up;
    glm::vec3 displacement;
    float fovY;
    glm::vec3 lightPosition;
    float lightRed;
    float lightGreen;
    float lightBlue;
    float* voxels;
    VoxelBuffer * v;
    //void setSphereVoxels(glm::vec3 center, float radius, Perlin * noise);
    //void setCloudVoxels(glm::vec3 center, float radius, Perlin * noise);
    //void setPyroclasticVoxels(glm::vec3 center, float radius, Perlin * noise);
public:
    Reader(char* toRead);
    float getDELT();
    float getSTEP();
    int getX();
    int getY();
    int getZ();
    glm::vec3 getBRGB();
    glm::vec3 getMRGB();
    char* getFILE();
    int getWIDTH();
    int getHEIGHT();
    glm::vec3 getEYEP();
    glm::vec3 getVDIR();
    glm::vec3 getUVEC();
    float getFOVY();
    glm::vec3 getLPOS();
    glm::vec3 getLCOL();
    glm::vec3 getOFST();
    float* getVoxels();
    VoxelBuffer * getVB();
};
#endif