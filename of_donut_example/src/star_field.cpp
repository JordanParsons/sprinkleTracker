//
//  star_field.cpp
//  donutDemo
//
//  Created by Jordan Parsons on 9/4/16.
//
//

#include "star_field.h"



void StarField::setupField(int num){
    numStars = num;
    stars = new float[num];
    radii = new float[num];
    brightness = new float[num];
    twinkleList = new int[num];
    
    searchRad = 75;
    blink = true;
    status = false;
    lastDraw = true;
    
    tree = new Quadtree(0, ofGetWindowRect());
    width = ofGetWidth();
    height = ofGetHeight();
    for(int i = 0; i < num; i+=2){
        stars[i] = ofRandomf() * width;
        stars[i+1] = ofRandomf() * height;
        tree->insertVec(new ofVec2f(stars[i], stars[i+1]));
    }
    for(int i = 0; i < num; i++){
        radii[i] = ofRandomf() * 2;
        brightness[i] = ofRandomf() * 255;
        twinkleList[i] = (ofRandom(10) > 6) ? 1 : -1;
    }
}

void StarField::renewField(){
    setupField(numStars);
}

void StarField::updateField(){
    //delete tree;
    //tree = new Quadtree(0, ofGetWindowRect());
    for(int i = 0; i < numStars; i++){
        if(twinkleList[i] == 1){
            brightness[i] += ofRandom(2);
            if(brightness[i] >= 255){
                brightness[i] = 255;
                twinkleList[i] = -1;
            }
        }else if(twinkleList[i] == -1){
            brightness[i] -= ofRandom(2);
            if(brightness[i] <= 0){
                brightness[i] = 0;
                twinkleList[i] = 1;
                //stars[i*2] = ofRandomf() * width;
                //stars[i*2+1] = ofRandomf() * height;
            }
        }
        //tree->insertVec(new ofVec2f(stars[i*2], stars[i*2+1]));
    }
}

void StarField::drawConns(std::vector<Sprinkle>  *sprinkles){
    ofSetColor(25);
    for (auto& p : *sprinkles) {
        vector<ofVec2f*> near = tree->queryArea(AABB(ofVec2f(p.getXPos()-searchRad, p.getYPos()-searchRad), ofVec2f(searchRad*2,searchRad*2)));
        for (auto& star : near){
            ofDrawLine(star->x, star->y, p.getXPos(), p.getYPos());
        }
    }
}

void StarField::drawField(){
    ofFill();
    for(int i  = 0; i < numStars; i+=2){
        ofSetColor(255, brightness[i]);
        ofDrawCircle(stars[i],
                     stars[i+1], radii[i]);
    }
}

void StarField::drawTree(bool draw){
    if(draw != lastDraw){
        blink = true;
        lastDraw = draw;
        blinkTime = ofGetElapsedTimeMillis();
        currentBlink = 0;
    }
    int blinkDelay = 75 - currentBlink*10;
    if(blinkTime + blinkDelay < ofGetElapsedTimeMillis() && currentBlink <= 6){
        blinkTime = ofGetElapsedTimeMillis();
        blink = !blink;
        currentBlink++;
        if(currentBlink == 6){
            blink = draw;
            currentBlink++;
            cout<<draw;
        }
    }
    
    if(blink){
        ofNoFill();
        if(draw){
            ofSetColor(255,70,0, 5 * currentBlink);
        }else{
            ofSetColor(255,70,0, 5 * (6-currentBlink));
        }
        tree->draw();
    }
}
