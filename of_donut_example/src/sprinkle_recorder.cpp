#include "sprinkle_recorder.h"



void SprinkleRecorder::setup(long d){
    lastTime = ofGetElapsedTimeMillis();
    targetTime = lastTime + d;
    enabled = true;
}

void SprinkleRecorder::delayScan(){
    targetTime = ofGetElapsedTimeMillis() + ofRandom(1000,3000);
    enabled = false;
}

void SprinkleRecorder::update(std::vector<Sprinkle>  *sprinkles){
    if(!enabled){
        if(ofGetElapsedTimeMillis() > targetTime){
            setup(ofRandom(3000,5000));
        }
    }else{
        if(isReady()){
            delayScan();
            for (auto& p : *sprinkles) {
                p.setTracked(false);
            }
        }
        for (auto& p : *sprinkles) {
            if(abs(p.getXPos() - scanPos) < 5){
                p.setTracked(true);
            }
        }
    }
}

void SprinkleRecorder::draw(){
    drawTimer();
    if(enabled){
        drawScanLine();
    }
}

void SprinkleRecorder::drawTimer(){
    /*
     ofSetColor(255);
     ofDrawRectangle(0, 0, ofGetWidth(), 15);
     ofSetColor(100);
     //ofDrawLine(10, 10, 20, 20);
     ofDrawLine(10, 10, ofGetWidth()-20, 10);
     ofFill();
     ofSetColor(255,70,0);
     barHeight = ofMap(ofGetElapsedTimeMillis(), lastTime, targetTime, ofGetWidth()-20, 0);
     ofDrawRectangle(10, 7, barHeight, 5);
     */
    ofFill();
    ofSetColor(255,70,0);
    barHeight = ofMap(ofGetElapsedTimeMillis(), lastTime, targetTime, ofGetHeight()-100, 0);
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