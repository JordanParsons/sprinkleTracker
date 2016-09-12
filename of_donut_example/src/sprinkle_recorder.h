#pragma once
#include "ofMain.h"
#include "Sprinkle.h"
#define SCANNING 0
#define LOADING 1
#define WORKING 2

class SprinkleRecorder{
    public:
        void setup(int m, long d);
        void update(std::vector<Sprinkle> *sprinkles);
        void draw();
        void drawTimer();
        void drawScanLine();
        bool isReady();
    private:
        float barHeight;
        float scanPos;
        long lastTime;
        long targetTime;
        int mode = SCANNING;
};