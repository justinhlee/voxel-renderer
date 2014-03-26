#include "raymarch.h" 
#include <iostream>
using namespace std;
#define KVALUE .8

Raymarch::Raymarch(VoxelBuffer* buf, Camera * c,glm::vec3 e, glm::vec3 mat, glm::vec3 bg, glm::vec3 lc, glm::vec3 lpos, glm::vec3 ofst) {
    buffer = buf;
    cam = c;
    eye = e;
    materialColor = mat;
    backgroundColor = bg;
    lightColor = lc;
    lightPosition = lpos;
	displacement = ofst;
}

glm::vec3 Raymarch::getColor(int x_coor, int y_coor, float step, glm::vec3 dimensions) {
    glm::vec3 colors = glm::vec3(0);
    glm::vec3 ray = cam->getRayDirection(x_coor, y_coor);
    glm::vec3 min = glm::vec3 (0+displacement.x,0+displacement.y, -dimensions.z+displacement.z);
    glm::vec3 max = glm::vec3 (dimensions.x+displacement.x, dimensions.y+displacement.y, 0+displacement.z);
    float T = 1.0;
    float Q = 1.0;
    if (cam->intersectsBox(min, max, ray)) {
		// get t values for first intersection 
		// and exiting intersection
        float tmin = cam->getTMin();
        float tmax = cam->getTMax();
        float dT = 0;
        glm::vec3 start = eye + ray*tmin;
		
        glm::vec3 exit = eye + ray*tmax;
        glm::vec3 length = exit - start;
        float raylength = sqrt(length.x*length.x +
                         length.y*length.y +
                         length.z*length.z); 
		// find length of the traversal in terms of the step value
        int maxstep = raylength/step;
        for (int t = 0; t <= maxstep; t++) {
            int x = glm::floor(start.x);
            int y = glm::floor(start.y);
            int z = glm::floor(start.z);
            //std::cout << z << endl;
            z = abs(z);     
            Voxel* curr = buffer->getVoxelAt(x,y,z, displacement);
            if (curr != NULL && curr->getDensity() > 0) {
                dT = exp(-KVALUE*curr->getDensity()); // took out * step
                T*=dT;
                if (curr->getLightValue() == -1) {
                    glm::vec3 voxPos = glm::vec3((float) x, (float) y, (float) z);
                    setLight(voxPos, step);
                }  
                Q *= curr->getLightValue();
                T = glm::clamp(T, 0.0f, 1.0f);
                Q = glm::clamp(Q, 0.0f, 1.0f);
                colors += ((1-dT)/((float) KVALUE) * (materialColor * lightColor) * T * Q   );
            } 

            start+=ray*step;
        }

        colors += T*backgroundColor;
        colors = glm::clamp(colors, 0.0f, 1.0f);
        return colors;
    } else {
        return backgroundColor;
    }
}

void Raymarch::setLight(glm::vec3 v, float step) {
    glm::vec3 voxelPosition = v;
    glm::vec3 N = lightPosition - voxelPosition;
    glm::vec3 dir = glm::normalize(N);
    float NLength = glm::length(N);
    int max = NLength/step;
    glm::vec3 start = voxelPosition + dir*step;
    float Q = 1.0;
    float deltaQ = 0;

    for (int i = 0; i <= max; i++) {
        int x = glm::floor(start.x);
        int y = glm::floor(start.y);
        int z = glm::floor(start.z);
        z = abs(z);
        Voxel* curr = buffer->getVoxelAt(x,y,z,displacement);
        if (curr != NULL && curr->getDensity() > 0) {
            deltaQ = exp(-KVALUE * buffer->getVoxelAt(x,y,z, displacement)->getDensity());
            Q *= deltaQ;
        }
            
        start += dir*step;
    }
    Q = glm::clamp(Q, 0.0f, 1.0f);
    buffer->getVoxelAt(v.x, v.y, v.z, displacement)->setLightValue(Q);
}