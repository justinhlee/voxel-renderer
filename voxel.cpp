#include "voxel.h"

Voxel::Voxel() {
    lightValue = -1;
}
float Voxel::getDensity() {
    return density;
}
void Voxel::setDensity(float d) {
    density = d;
}
float Voxel::getLightValue() {
    return lightValue;
}
void Voxel::setLightValue(float l) {
    lightValue = l;
}
