#pragma once
#include "ofMain.h"
#include "sprinkle.h"

/*
Ideas:
 - Form tracking grid
 - Lock onto pts
 - Make shape
 - check for line intersection with grid shape, w/ max line length
 
 -Piece out free 1 into particle id's, generate connections based on that ie 0.980134 = 98,01,34
 -Statistic Graphs of Speed's
 -Statistics of all particle counts across system
 -Diffent Modes flash fix text on change?
 -toggle debug modes
 -show velocity info / heading drawings
 -trace paths?
 -match dot patterns to stars maps???
    - list of locations
    - radius tollerance, check against pos
    - flash pattern? / highlight those somehow?
*/

#define CROSS_LEN     10
#define CROSS_DIST    15

class DonutData{
    public:
        void setSprinkePointer(std::vector<Sprinkle> *s);
        void updateSprinkleInfo(Sprinkle *p);
        void draw();
        void drawSprinkle(Sprinkle *p);
        void drawTrackingLines(Sprinkle *p);
        void drawTrackingData(Sprinkle *p);
        void drawTrackingSquare(Sprinkle *p);
        void drawSprinkleNetwork();
        std::vector<Sprinkle> *sprinkles;
private:
    float xPos,yPos,free1,free2;
};