#include "reader.h"
#include <iostream>
#include <fstream> 
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

Reader::Reader(char* toRead) {
    int count = 0; 
    displacement = glm::vec3(0.0);
    Perlin * noise = new Perlin(6, .04, 3.2, 1);   

    ifstream configFile(toRead);
        if (!configFile.is_open()) {
            cout << "Could not open file.\n" << endl;
        } else {
            while (!configFile.eof()) {
                int n = 0;
                char buffer[10000];
                configFile.getline(buffer, 10000);

                const char* token[5] = {};
                token[0] = strtok(buffer, " ");
				if (!token[n]) continue;
                if (strcmp(token[0],  "DELT") == 0) {
                    token[1] = strtok(0, " ");
                    delt = (float) atof(token[1]);
                } else
                if (strcmp(token[0],  "STEP") == 0) {
                    token[1] = strtok(0, " ");
                    step = strtod(token[1], NULL);
                } else
                if (strcmp(token[0],  "XYZC") == 0) {
                    int n = 0;
                    for (n = 1; n < 4; n++) {
                        token[n] = strtok(0, " ");
                    }
                    x = strtol(token[1], NULL, 0);
                    y = strtol(token[2], NULL, 0);
                    z = strtol(token[3], NULL, 0);
                    
                    voxels = new float[x*y*z];
                    v = new VoxelBuffer(x, y, z);
                } else
                if (strcmp(token[0],  "BRGB") == 0) {
                    for (n = 1; n < 4; n++) {
                        token[n] = strtok(0, " ");
                    }
                    bgRed = strtod(token[1], NULL);
                    bgGreen = strtod(token[2], NULL);
                    bgBlue = strtod(token[3], NULL);

                } else
                if (strcmp(token[0],  "MRGB") == 0) {
                    for (n = 1; n < 4; n++) {
                        token[n] = strtok(0, " ");
                    }
                    materialRed = strtod(token[1], NULL);
                    materialGreen = strtod(token[2], NULL);
                    materialBlue = strtod(token[3], NULL);
                } else
                if (strcmp(token[0],  "FILE") == 0) {
                    token[1] = strtok(0, " ");
                    fileName = new char[strlen(token[1])];
                    strcpy(fileName, token[1]);
                } else
                if (strcmp(token[0],  "RESO") == 0) {
                    int n = 0;
                    for (n = 1; n < 3; n++) {
                        token[n] = strtok(0, " ");
                    }
                    width = strtol(token[1], NULL, 0);
                    height = strtol(token[2], NULL, 0);

                } else
                if (strcmp(token[0],  "EYEP") == 0) {
                    float temp_x;
                    float temp_y;
                    float temp_z;

                    int n = 0;
                    for (n = 1; n < 4; n++) {
                        token[n] = strtok(0, " ");   
                    }
                    temp_x= strtod(token[1], NULL);
                    temp_y = strtod(token[2], NULL);
                    temp_z = strtod(token[3], NULL);
                    eye = glm::vec3(temp_x, temp_y, temp_z);
                } else
                if (strcmp(token[0],  "VDIR") == 0) {
                    float temp_x;
                    float temp_y;
                    float temp_z;
                    int n = 0;
                    for (n = 1; n < 4; n++) {
                        token[n] = strtok(0, " ");   
                    }
                    temp_x = strtod(token[1], NULL);
                    temp_y = strtod(token[2], NULL);
                    temp_z = strtod(token[3], NULL);
                    viewDirection = glm::vec3(temp_x, temp_y, temp_z);
                } else
                if (strcmp(token[0],  "UVEC") == 0) {
                    float temp_x;
                    float temp_y;
                    float temp_z;
                    int n = 0;
                    for (n = 1; n < 4; n++) {
                        token[n] = strtok(0, " ");   
                    }
                    temp_x= strtod(token[1], NULL);
                    temp_y = strtod(token[2], NULL);
                    temp_z = strtod(token[3], NULL);
                    up = glm::vec3(temp_x, temp_y, temp_z);
                } else
                if (strcmp(token[0],  "FOVY") == 0) {
                    token[1] = strtok(0, " ");
                    fovY = strtod(token[1], NULL);
                } else 
                if (strcmp(token[0],  "LPOS") == 0) {
                    float temp_x;
                    float temp_y;
                    float temp_z;
                    int n = 0;
                    for (n = 1; n < 4; n++) {
                        token[n] = strtok(0, " ");   
                    }
                    temp_x= strtod(token[1], NULL);
                    temp_y = strtod(token[2], NULL);
                    temp_z = strtod(token[3], NULL);
                    lightPosition = glm::vec3(temp_x, temp_y, temp_z);
                } else 
                if (strcmp(token[0],  "LCOL") == 0) {
                    for (n = 1; n < 4; n++) {
                        token[n] = strtok(0, " ");
                    }
                    lightRed = strtod(token[1], NULL);
                    lightGreen = strtod(token[2], NULL);
                    lightBlue = strtod(token[3], NULL);
                } else if (strcmp(token[0], "OFST") == 0) {
                    float temp_x;
                    float temp_y;
                    float temp_z;

                    int n = 0;
                    for (n = 1; n < 4; n++) {
                        token[n] = strtok(0, " ");   
                    }
                    temp_x = strtod(token[1], NULL);
                    temp_y = strtod(token[2], NULL);
                    temp_z = strtod(token[3], NULL);
                    displacement = glm::vec3(temp_x, temp_y, temp_z);
                } else if (strncmp(token[0], "sphere", 6) == 0){

                    string center;
                    string radius;
                    getline(configFile, center);
                    istringstream iss(center);
                    vector<string> tokens;
                    copy(istream_iterator<string>(iss),
                            istream_iterator<string>(),
                            back_inserter<vector<string> >(tokens));
                    const char * temp_x = tokens[0].c_str();
                    const char * temp_y = tokens[1].c_str();
                    const char * temp_z = tokens[2].c_str();
                    getline(configFile, radius);
                    const char * temp_r = radius.c_str();

                    float r  = strtod(temp_r, NULL);
                    float x = strtod(temp_x, NULL);
                    float y = strtod(temp_y, NULL);
                    float z = strtod(temp_z, NULL);
                    glm::vec3 point = glm::vec3(x,y,z);

                    v->setSphereVoxels(point, r);
                } else if (strncmp(token[0], "pyroclastic", 11) == 0) {
                    string center;
                    string radius;
                    getline(configFile, center);
                    istringstream iss(center);
                    vector<string> tokens;
                    copy(istream_iterator<string>(iss),
                            istream_iterator<string>(),
                            back_inserter<vector<string> >(tokens));
                    const char * temp_x = tokens[0].c_str();
                    const char * temp_y = tokens[1].c_str();
                    const char * temp_z = tokens[2].c_str();
                    getline(configFile, radius);
                    const char * temp_r = radius.c_str();

                    float r  = strtod(temp_r, NULL);
                    float x = strtod(temp_x, NULL);
                    float y = strtod(temp_y, NULL);
                    float z = strtod(temp_z, NULL);
                    glm::vec3 point = glm::vec3(x,y,z);

                    v->setPyroclasticVoxels(point, r, noise);
                } else if (strncmp(token[0], "cloud", 5) == 0) {
                    string center;
                    string radius;
                    getline(configFile, center);
                    istringstream iss(center);
                    vector<string> tokens;
                    copy(istream_iterator<string>(iss),
                            istream_iterator<string>(),
                            back_inserter<vector<string> >(tokens));
                    const char * temp_x = tokens[0].c_str();
                    const char * temp_y = tokens[1].c_str();
                    const char * temp_z = tokens[2].c_str();
                    getline(configFile, radius);
                    const char * temp_r = radius.c_str();

                    float r  = strtod(temp_r, NULL);
                    float x = strtod(temp_x, NULL);
                    float y = strtod(temp_y, NULL);
                    float z = strtod(temp_z, NULL);
                    glm::vec3 point = glm::vec3(x,y,z);

                    v->setCloudVoxels(point, r, noise);      
                }
				//string line;
				//getline(configFile, line);
				//cout << line << endl;
				
                /*
                else {
                    float temp = strtod(token[0], NULL);
                    voxels[count++] = temp;
                }
                */
				//std::cout << token[0] << endl;

            }
        }         
}

VoxelBuffer * Reader::getVB() {
    return v;
}

float Reader::getDELT(){
    return delt;
}
float Reader::getSTEP() {
    return step;
}
int Reader::getX() {
    return x;
}
int Reader::getY() {
    return y;
}
int Reader::getZ() {
    return z;
}
glm::vec3 Reader::getBRGB() {
    return glm::vec3(bgRed, bgGreen, bgBlue);
}
glm::vec3 Reader::getMRGB() {
    return glm::vec3(materialRed, materialGreen, materialBlue);

}
char* Reader::getFILE() { 
	/*
    char * f;
	//f = new char[1000];
    for (int i = 0; !isspace(fileName[i]); i++) {
        f[i] = fileName[i];
    }  
	*/
    return(fileName);
}
int Reader::getWIDTH() {
    return width;
}
int Reader::getHEIGHT() {
    return height;
}
glm::vec3 Reader::getEYEP() {
    return eye;
}
glm::vec3 Reader::getVDIR() {
    return viewDirection;
}
glm::vec3 Reader::getUVEC() {
    return up;
}
float Reader::getFOVY() {
    return fovY;
}
glm::vec3 Reader::getLPOS() {
    return lightPosition;
}
glm::vec3 Reader::getLCOL() {
    return glm::vec3(lightRed, lightGreen, lightBlue);
}
glm::vec3 Reader::getOFST() {
    return displacement;
}
float* Reader::getVoxels() {
    return voxels;
}
