#include "sprinkle.h"

//--------------------------------------------------------------
// Generate the sprinkle with random parameters
Sprinkle::Sprinkle(float maxVel, float maxAcc) {
    ofLog(OF_LOG_VERBOSE, "New Sprinkle from Random.");
    maxY = float(ofGetHeight()) / float(ofGetWidth());
    
    x = ofRandomuf();
    y = ofMap(ofRandomuf(),0.0,1.0,0.0,maxY);
    xVel = ofRandomf() * maxVel * 0.1;
    yVel = ofRandomf() * maxVel * 0.1;
    xAcc = ofRandomf() * maxAcc * 0.5;
    yAcc = ofRandomf() * maxAcc * 0.5;
    free1 = ofRandomuf();
    free2 = ofRandomuf();
    track = false;//(ofRandomf() > 0.9) ? true : false;
    rad = (track) ? 5 : 3;
}

//--------------------------------------------------------------
// Generate the sprinkle from an OSC message
Sprinkle::Sprinkle(const ofxOscMessage &m) {
    ofLog(OF_LOG_VERBOSE, "New Sprinkle from OSC.");
    maxY = float(ofGetHeight()) / float(ofGetWidth());
    
    x = 0;
    y = m.getArgAsFloat(0);
    xVel = m.getArgAsFloat(1);
    yVel = m.getArgAsFloat(2);
    xAcc = m.getArgAsFloat(3);
    yAcc = m.getArgAsFloat(4);
    free1 = m.getArgAsFloat(5);
    free2 = m.getArgAsFloat(6);
    track = false;//(ofRandomf() > 0.7) ? true : false;
    rad = (track) ? 5 : 3;
    // Handle starting on the right
    if (xVel < 0 ) { x = 1.0;}
}

//--------------------------------------------------------------
void Sprinkle::update(float maxVel, float maxAcc, bool beFroze) {
    if(track && beFroze){
        return;
    }
    
    
    // bounce off top and bottom
    if (y >= maxY || y <= 0.0) {
        yVel *= -1.0;
        yAcc *= -1.0;
    }
    
    x += xVel * 0.75f;
    y += yVel * 0.75f;
    
    
    xVel += xAcc;
    xVel += yAcc;
    xVel = ofClamp(xVel,-maxVel, maxVel);
    yVel = ofClamp(yVel, -maxVel, maxVel);
    xAcc = maxAcc*ofRandomf();
    yAcc = maxAcc*ofRandomf();
    xPos = ofMap(x,0.0, 1.0, 0.0, ofGetWidth());
    yPos = ofMap(y,0.0, maxY, 0.0, ofGetHeight());
    free1 = ofClamp(free1+ofRandomf()*0.001f, 0, 1);
    free2 = ofClamp(free2+ofRandomf()*0.001f, 0, 1);
    pos = ofVec2f(xPos, yPos);
    
}

//--------------------------------------------------------------
void Sprinkle::draw() {
    
    
}

//--------------------------------------------------------------
bool Sprinkle::isOffScreen() {
    return x > 1 || x < 0;
}

//--------------------------------------------------------------
ofxOscMessage Sprinkle::createOSCMessage() const {
    
    ofxOscMessage m;
    m.addFloatArg(y);
    m.addFloatArg(xVel);
    m.addFloatArg(yVel);
    m.addFloatArg(xAcc);
    m.addFloatArg(yAcc);
    m.addFloatArg(free1);
    m.addFloatArg(free2);
    return m;
}