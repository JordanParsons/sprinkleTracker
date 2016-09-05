#pragma once
#include "ofMain.h"
#include "Sprinkle.h"


class SprinkleRecorder{
    public:
        void setup(long d);
    void delayScan();
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
        bool enabled = false;
};