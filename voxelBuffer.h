#pragma once
#include "voxel.h"
#include "glm/glm.hpp"
#include "perlin.h"

class VoxelBuffer {
 private:
    Voxel* buffer;
    int x;
    int y;
    int z;
 public:
    VoxelBuffer(int x, int y, int z);
    Voxel* getVoxelAt(int x, int y, int z, glm::vec3 displacement);
    void setVoxels(float* voxels);
    void setSphereVoxels(glm::vec3 center, float radius);
    void setCloudVoxels(glm::vec3 center, float radius, Perlin * noise);
    void setPyroclasticVoxels(glm::vec3 center, float radius, Perlin * noise);
};
