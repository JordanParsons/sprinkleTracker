#include "donut_data.h"


void DonutData::setSprinkePointer(std::vector<Sprinkle> *s){
    sprinkles = s;
}

void DonutData::updateSprinkleInfo(Sprinkle *p){
    xPos = p->getXPos();
    yPos = p->getYPos();
    free1 = p->getFree1();
    free2 = p->getFree2();
}

void DonutData::draw(){
    //drawSprinkleNetwork();
    
    for (auto& p : *sprinkles) {
        updateSprinkleInfo(&p);
        drawSprinkle(&p);
        drawTrackingLines(&p);
        //drawTrackingData(&p);
        drawTrackingSquare(&p);
    }
    /*
    for (auto& p : *sprinkles) {
        updateSprinkleInfo(&p);
        drawTrackingData(&p);
    }
    for (auto& p : *sprinkles) {
        updateSprinkleInfo(&p);
        drawTrackingSquare(&p);
    }*/
}

void DonutData::drawSprinkleNetwork(){
    ofSetColor(255,70,0);
    for (auto& p : *sprinkles) {
        if(!p.canTrack()){  continue; }
        for (auto& p2 : *sprinkles) {
            if(!p2.canTrack()){ continue; }
            ofDrawLine(p.getXPos(), p.getYPos(), p2.getXPos(), p2.getYPos());
        }
    }
}

void DonutData::drawSprinkle(Sprinkle *p){
    float rad = ofMap(free1,0.0,1.0,1,p->getRad());
    ofFill();
    ofSetColor(255);
    ofDrawCircle(xPos,yPos,rad);
    //ofNoFill();
    //ofSetColor(0);
    //ofDrawCircle(xPos,yPos,rad);
}

void DonutData::drawTrackingLines(Sprinkle *p){
    if(!p->canTrack()){
        return;
    }
    ofNoFill();
    ofSetColor(255,15);
    //ofDrawLine(xPos, 0, xPos, ofGetHeight());
    //ofDrawLine(0, yPos, ofGetWidth(), yPos);
    ofSetColor(255,50);
    //Scale based on free 1
    float lineSize = (50 * free1) + 10;
    ofDrawLine(xPos-lineSize, yPos, xPos+lineSize, yPos);
    ofDrawLine(xPos, yPos-lineSize, xPos, yPos+lineSize);
}

void DonutData::drawTrackingData(Sprinkle *p){
    if(!p->canTrack()){
        return;
    }
    ofSetColor(150);
    string msg ="X:" + ofToString(xPos) + "\nY:" + ofToString(yPos);
    msg += "\nF:" + ofToString(free1) + "\nF2:" + ofToString(free2);
    //(CROSS_DIST*free1+2)
    float textX = xPos + (CROSS_DIST*free1+2);//(xPos < ofGetWidth() / 2) ? 50 : ofGetWidth() - 50;
    float textY = yPos + (CROSS_DIST*free1+11);//(yPos < ofGetHeight() / 2) ? 50 : ofGetHeight() - 50;
    ofDrawBitmapString(msg, textX, textY);
    //ofDrawLine(textX, textY - 10, xPos, yPos);
}

void DonutData::drawTrackingSquare(Sprinkle *p) {
    if(!p->canTrack()){
        return;
    }
    ofSetColor(150, 0, 0);
    ofNoFill();
    //Upper Right
    ofDrawLine(xPos+(CROSS_DIST*free1)+1, yPos-(CROSS_DIST*free1+1),
               xPos+(CROSS_DIST*free1+1), yPos-CROSS_LEN*free1);
    ofDrawLine(xPos+(CROSS_DIST*free1+1), yPos-(CROSS_DIST*free1+1),
               xPos+CROSS_LEN*free1, yPos-(CROSS_DIST*free1+1));
    //Lower Left
    ofDrawLine(xPos-(CROSS_DIST*free1+1), yPos+(CROSS_DIST*free1+1),
               xPos-(CROSS_DIST*free1+1), yPos+CROSS_LEN*free1);
    ofDrawLine(xPos-(CROSS_DIST*free1+1), yPos+(CROSS_DIST*free1+1),
               xPos-CROSS_LEN*free1, yPos+(CROSS_DIST*free1+1));
    //Upper Left
    ofDrawLine(xPos-(CROSS_DIST*free1+1), yPos-(CROSS_DIST*free1+1),
               xPos-(CROSS_DIST*free1+1), yPos-CROSS_LEN*free1);
    ofDrawLine(xPos-(CROSS_DIST*free1+1), yPos-(CROSS_DIST*free1+1),
               xPos-CROSS_LEN*free1, yPos-(CROSS_DIST*free1+1));
    //Lower Right
    ofDrawLine(xPos+(CROSS_DIST*free1+1), yPos+(CROSS_DIST*free1+1),
               xPos+(CROSS_DIST*free1+1), yPos+CROSS_LEN*free1);
    ofDrawLine(xPos+(CROSS_DIST*free1+1), yPos+(CROSS_DIST*free1+1),
               xPos+CROSS_LEN*free1, yPos+(CROSS_DIST*free1+1));
}