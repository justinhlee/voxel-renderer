#include "camera.h" 
#include <iostream>
using namespace std;
#define PI 3.14159265

Camera::Camera(glm::vec3 e, glm::vec3 c, glm::vec3 u, float t, int w, int h) {
    eye = e;
    viewDirection = c;
    up = u;
    fovY = t;
    width = (float) w;
    height = (float) h;
    midpoint = eye + viewDirection;
    a = glm::cross(viewDirection, up);
    b = glm::cross(a, viewDirection);
}

glm::vec3 Camera::getRayDirection(int x, int y) {    
    // convert to NDC 
    float ndc_x = ((float) x)/((float) (width-1));
    float ndc_y = 1-((float) y)/((float) (height-1));
    //std::cout << ndc_x << ", " << ndc_y << endl;

    float viewLength = glm::length(viewDirection);
    float aLength = glm::length(a);
    float bLength = glm::length(b);


    //glm::vec3 h =  ( a * viewLength*tan( fovX  ) )  /aLength;
    glm::vec3 v = ( b * viewLength* (float)tan(fovY  * PI/(float) 180.0) )  / bLength;
    glm::vec3 h = (a * (   (width-1)/(height-1)  * glm::length(v)  )    ) /aLength;


    // find point in NDC
    glm::vec3 point = midpoint + (2*ndc_x-1)*h + (2*ndc_y-1)*v;
    

    // return direction of ray 
    glm::vec3 dir = point - eye;
    dir = glm::normalize(dir);    
    return dir;
}

bool Camera::intersectsBox(glm::vec3 minimum, glm::vec3 maximum, glm::vec3 ray) { 
    float divx = 1/ray.x;
    float divy = 1/ray.y;
    float divz = 1/ray.z;

    float tx1 = (minimum.x - eye.x)*divx;
    float tx2 = (maximum.x - eye.x)*divx;
 
    float tmin = min(tx1, tx2);
    float tmax = max(tx1, tx2);
 
    float ty1 = (minimum.y - eye.y)*divy;
    float ty2 = (maximum.y - eye.y)*divy;
 
    tmin = max(tmin, min(ty1, ty2));
    tmax = min(tmax, max(ty1, ty2));

    float tz1 = (minimum.z - eye.z)*divz;
    float tz2 = (maximum.z - eye.z)*divz;
 
    tmin = max(tmin, min(tz1, tz2));
    tmax = min(tmax, max(tz1, tz2));

    if (tmin < 0)
        return false;

    tEntry = tmin;
    tExit = tmax;
 
    return tmax >= tmin;    
}

float Camera::getTMin() {
    return tEntry;
}
float Camera::getTMax() {
    return tExit;
}


