#pragma once
#include "ofMain.h"
#include "Sprinkle.h"
#include "Quadtree.h"

class StarField {
public:
    void setupField(int num);
    void updateField();
    void drawConns(std::vector<Sprinkle>  *sprinkles);
    void drawField();
    void drawTree(bool draw);
    void renewField();
    void setSearchRad(int r) { searchRad = r; }
private:
    int numStars;
    float *stars;
    float *radii;
    float *brightness;
    int *twinkleList;
    Quadtree * tree;
    int width;
    int height;
    int searchRad;
    bool blink;
    long blinkTime;
    bool status;
    bool lastDraw;
    int currentBlink;
};