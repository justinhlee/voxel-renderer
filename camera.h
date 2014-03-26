#ifndef CAMERA
#define CAMERA
#include <cmath>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
 private:
    glm::vec3 viewDirection;
    glm::vec3 eye;
    glm::vec3 up;
    float fovY;
    float width;
    float height;
    glm::vec3 midpoint;
    glm::vec3 a;
    glm::vec3 b;
    float getLength(glm::vec3 v);
    float tEntry;
    float tExit;

 public:
    Camera(glm::vec3 e, glm::vec3 c, glm::vec3 u, float t, int w, int h);
    glm::vec3 getRayDirection(int x, int y); // given pixel coordinates
    bool intersectsBox(glm::vec3 min, glm::vec3 max, glm::vec3 ray);
    float getTMin();
    float getTMax();
};
#endif