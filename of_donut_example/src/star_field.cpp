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
    for(int i = 0; i < num; i+=2){
        stars[i] = ofRandomf();
        stars[i+1] = ofRandomf();
    }
    for(int i = 0; i < num; i++){
        radii[i] = ofRandomf() * 2;
        brightness[i] = ofRandomf() * 255;
        twinkleList[i] = (ofRandom(10) > 6) ? 1 : 0;
    }
}

void StarField::updateField(){
    for(int i = 0; i < numStars; i++){
        if(twinkleList[i] == 1){
            brightness[i] += ofRandom(5);
            if(brightness[i] >= 255){
                brightness[i] = 255;
                twinkleList[i] = -1;
            }
        }else if(twinkleList[i] == -1){
            brightness[i] -= ofRandom(5);
            if(brightness[i] <= 0){
                brightness[i] = 0;
                twinkleList[i] = 1;
            }
        }
    }
}

void StarField::drawConns(std::vector<Sprinkle>  *sprinkles){
    ofSetColor(50);
    for (auto& p : *sprinkles) {
        for(int i = 0; i < numStars; i+=2){
            float dist = ofDist(p.getXPos(), p.getYPos(),
                                ofMap(stars[i], 0, 1, 0, ofGetWidth()),
                                ofMap(stars[i+1], 0, 1, 0, ofGetHeight()));
            if(dist < 50){
                ofDrawLine(p.getXPos(), p.getYPos(),
                           ofMap(stars[i], 0, 1, 0, ofGetWidth()),
                           ofMap(stars[i+1], 0, 1, 0, ofGetHeight()));
            }
        }
    }
}

void StarField::drawField(){
    ofFill();
    for(int i  = 0; i < numStars; i+=2){
        ofSetColor(brightness[i]);
        ofDrawCircle(ofMap(stars[i], 0, 1, 0, ofGetWidth()),
                     ofMap(stars[i+1], 0, 1, 0, ofGetHeight()), radii[i]);
    }
}
