#pragma once
#include "ofMain.h"
#include "Sprinkle.h"

class StarField {
public:
    void setupField(int num);
    void updateField();
    void drawConns(std::vector<Sprinkle>  *sprinkles);
    void drawField();
private:
    int numStars;
    float *stars;
    float *radii;
    float *brightness;
    int *twinkleList;
};