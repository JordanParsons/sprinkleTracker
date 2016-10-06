#pragma once
#include "ofMain.h"
#include "Sprinkle.h"
#define SCANNING 0
#define LOADING 1
#define WORKING 2
#define WAITING 3

class SprinkleRecorder{
    public:
        void setup(int m, long d);
        void update(std::vector<Sprinkle> *sprinkles);
        void draw();
        void drawTimer();
        void drawScanLine();
        void drawTrackedLine();
        bool isReady();
        bool isScanning();
        bool isDoneScanning();
        bool isLoading();
        bool isWaiting() { return (mode == WAITING); };
      bool isWorking() { return (mode == WORKING); };
    private:
        float barHeight;
        float scanPos;
        long lastTime;
        long targetTime;
        int mode = LOADING;
        int lastMode = WAITING;
        vector<Sprinkle*> currentLine;
};