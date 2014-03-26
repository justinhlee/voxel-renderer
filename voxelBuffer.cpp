#include "voxelBuffer.h"
#include <iostream>
using namespace std;

VoxelBuffer::VoxelBuffer(int x_coor, int y_coor, int z_coor) {
    x = x_coor;
    y = y_coor;
    z= z_coor;
    buffer = new Voxel[x*y*z];
    for (int i = 0; i < x*y*z; i++) {
        buffer[i].setDensity(0);
    }
}

void VoxelBuffer::setVoxels(float* voxels) {
    for (int i = 0; i < x*y*z; i++) {
        buffer[i].setDensity(voxels[i]);
    }
}

void VoxelBuffer::setSphereVoxels(glm::vec3 center, float radius) {
    for (int k = 0; k < z; k++) {
        for (int j = 0; j < y; j++) {
            for (int i = 0; i < x; i++) {
                glm::vec3 position = glm::vec3(i, j, k);
                glm::vec3 distance = position - center;
                float length = glm::length(distance);
                int index = (x * j) + i + (k*(x * y));
                index = abs(index);
                if (length < radius) {
                    float curr = buffer[index].getDensity();
                    //std::cout << (radius - length)/radius  << endl;

                    buffer[index].setDensity(curr +  (radius - length)/radius     );
                } 
            }
        }
    }    
}

void VoxelBuffer::setCloudVoxels(glm::vec3 center, float radius, Perlin * noise) {
        for (int k = 0; k < z; k++) {
            for (int j = 0; j < y; j++) {
                for (int i = 0; i < x; i++) {
                glm::vec3 position = glm::vec3(i, j, k);
                glm::vec3 P = position - center;
                //std::cout << P.x << " " << P.y << " " << P.z << endl;
                float n = noise->Get(P.x, P.y, P.z);
                //n = glm::clamp(n, 0.0f, 1.0f);

                int index = (x * j) + i + (k*(x * y));
                index = (index);
                float density = ( n + (1 - glm::length( P)/radius ));
                density = glm::clamp(density, 0.0f, 1.0f);

                //density = glm::clamp(density, 0.0f, 1.0f);
                //std::cout << density << endl;
                float curr = buffer[index].getDensity();
                buffer[index].setDensity(curr + density);
                //std::cout << buffer[index].getDensity() << endl;
            }
        }
    }
}

void VoxelBuffer::setPyroclasticVoxels(glm::vec3 center, float radius, Perlin * noise) {
        for (int k = 0; k < z; k++) {
            for (int j = 0; j < y; j++) {
                for (int i = 0; i < x; i++) {
                    glm::vec3 position = glm::vec3(i, j, k);
                    glm::vec3 P = position - center;



                    float n = noise->Get(P.x, P.y, P.z);
                    n = glm::clamp(n, 0.0f, 1.0f);

                    int index = (x * j) + i + (k*(x * y));
                    index = abs(index);
                    float density = max(  ( radius - glm::length(P)/radius  + n), (float) 0      );
                    density = glm::clamp(density, 0.0f, 1.0f);
                    float curr = buffer[index].getDensity();
                    buffer[index].setDensity(curr + density);
            }
        }
    }
}


Voxel* VoxelBuffer::getVoxelAt(int x_coor, int y_coor, int z_coor, glm::vec3 displacement) {
	x_coor = x_coor - displacement.x;
	y_coor = y_coor - displacement.y;
	z_coor = z_coor - displacement.z;

    int index = (x * y_coor) + x_coor + (z_coor*(x * y));
    index = abs(index);
    if (index > x*y*z) {
        return NULL;
    }
    return &buffer[index];
}