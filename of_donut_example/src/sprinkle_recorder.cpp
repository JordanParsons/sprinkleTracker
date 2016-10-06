#include "sprinkle_recorder.h"

void SprinkleRecorder::setup(int m, long d){
    lastTime = ofGetElapsedTimeMillis();
    targetTime = lastTime + d;
    lastMode = mode;
    mode = m;
}

void SprinkleRecorder::update(std::vector<Sprinkle>  *sprinkles){
    if(mode == LOADING){
        if(ofGetElapsedTimeMillis() > targetTime){
            for (auto& p : *sprinkles) {
                p.setTracked(false);
            }
            setup(SCANNING, ofRandom(500,5000));
        }
    }else if(mode == SCANNING){
        if(isReady()){
            setup(WORKING, ofRandom(5000,10000));
        }
        for (auto& p : *sprinkles) {
            if(abs(p.getXPos() - scanPos) < 10){
                if(!p.canTrack()){
                    currentLine.push_back(&p);
                }
                p.setTracked(true);
            }
        }
    }else if(mode == WORKING){
        if(ofGetElapsedTimeMillis() > targetTime){
            currentLine.clear();
            for (auto& p : *sprinkles) {
                p.setTracked(false);
            }
            setup(WAITING, ofRandom(25000,60000));
        }
    }else if(mode == WAITING){
            if(ofGetElapsedTimeMillis() > targetTime){
                currentLine.clear();
                setup(LOADING, ofRandom(750,2500));
            }
        }
}

void SprinkleRecorder::draw(){
    if(mode == SCANNING){
        drawScanLine();
        drawTrackedLine();
    }else if(mode == LOADING){
        drawTimer();
    }else{
        drawTrackedLine();
    }
}

void SprinkleRecorder::drawTrackedLine(){
    
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

bool SprinkleRecorder::isLoading(){
    if (mode == LOADING){
        return true;
    }else {
        return false;
    }
}

bool SprinkleRecorder::isScanning() {
    if (mode == SCANNING){
        return true;
    }else {
        return false;
    }
}

bool SprinkleRecorder::isDoneScanning(){
    if(lastMode == SCANNING && mode == WORKING){
        lastMode = WORKING;
        return true;
    }else{
        return false;
    }
}