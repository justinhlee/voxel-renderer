#include "EasyBMP.h"
#include "glm/glm.hpp"
#include <iostream>
#include <fstream> 
#include <string>
#include "voxel.h"
#include "voxelBuffer.h"
#include "camera.h"
#include "raymarch.h"
#include "reader.h"

using namespace std;

int main(int argc, char** argv) {

    if (argc != 2) {
        cout << "Incorrect input. Please enter the name of the configuration file." << endl; 
        return -1; 
    } 
    Reader * config = new Reader(argv[1]);
    
    int width = config->getWIDTH();
    int height = config->getHEIGHT();
    int x = config->getX();
    int y = config->getY();
    int z = config->getZ();

    Camera * rayGenerator = new Camera(config->getEYEP(), config->getVDIR(), 
                                                config->getUVEC(), config->getFOVY(), width, height);
    BMP output;
    output.SetSize(width, height);
    output.SetBitDepth(24);

    Raymarch * raymarch = new Raymarch(config->getVB(), rayGenerator, config->getEYEP(), 
                                        config->getMRGB(), config->getBRGB(), 
                                        config->getLCOL(), config->getLPOS(), config->getOFST());
    
    for (int w = 0; w < width; w++) {
		cout << "Rendering: " << (float) w/width << endl;
        for (int h = 0; h < height; h++) {
            /*
            // Ray direction color test
            output(w,h)->Red = abs(rayGenerator->getRayDirection(w,h).x) *255;
            output(w,h)->Green = abs(rayGenerator->getRayDirection(w,h).y) *255;
            output(w,h)->Blue = abs(rayGenerator->getRayDirection(w,h).z) *255;
            */
            glm::vec3 colors = raymarch->getColor(w,h, config->getSTEP(), glm::vec3(x, y, z));
            colors*=255.0;
            if (colors.x > 255) 
                colors.x = 255;
            if (colors.y > 255) 
                colors.y = 255;
            if (colors.z > 255) 
                colors.z = 255;
            output(w,h)->Red =colors.x;
            output(w,h)->Green = colors.y;
            output(w,h)->Blue = colors.z;
        }
    }
    
    output.WriteToFile(config->getFILE());
	cout << "File has been finished rendering." <<endl;
    return 0;
}
