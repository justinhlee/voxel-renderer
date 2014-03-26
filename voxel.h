#pragma once

class Voxel {
 private:
    float density;
    float lightValue;
 public:
    Voxel();
    float getDensity();
    void setDensity(float d);
    float getLightValue();
    void setLightValue(float l);
};
