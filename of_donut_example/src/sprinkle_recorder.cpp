#include "sprinkle_recorder.h"

void SprinkleRecorder::setup(int m, long d){
    lastTime = ofGetElapsedTimeMillis();
    targetTime = lastTime + d;
    mode = m;
}

void SprinkleRecorder::update(std::vector<Sprinkle>  *sprinkles){
    if(mode == LOADING){
        if(ofGetElapsedTimeMillis() > targetTime){
            setup(SCANNING, ofRandom(1000,3000));
        }
    }else if(mode == SCANNING){
        if(isReady()){
            setup(WORKING, ofRandom(3000,5000));
        }
        for (auto& p : *sprinkles) {
            if(abs(p.getXPos() - scanPos) < 10){
                p.setTracked(true);
            }
        }
    }else if(mode == WORKING){
        if(ofGetElapsedTimeMillis() > targetTime){
            for (auto& p : *sprinkles) {
                p.setTracked(false);
            }
            setup(LOADING, 1000);
        }
    }
}

void SprinkleRecorder::draw(){
    if(mode == SCANNING){
        drawScanLine();
    }else if(mode == LOADING){
        drawTimer();
    }
}

void SprinkleRecorder::drawTimer(){
    ofFill();
    ofSetColor(255,70,0);
    barHeight = ofMap(ofGetElapsedTimeMillis(),
                      lastTime, targetTime, ofGetHeight() - 100, 0);
    ofDrawRectangle(10, 10, 5, barHeight);
    
}

void SprinkleRecorder::drawScanLine(){
    scanPos = ofMap(ofGetElapsedTimeMillis(), lastTime, targetTime, 0, ofGetWidth());
    ofSetColor(200);
    ofDrawLine(scanPos, 0, scanPos, ofGetHeight());
}

bool SprinkleRecorder::isReady(){
    return (ofGetElapsedTimeMillis() > targetTime);
}