#pragma once
#include "ofMain.h"
#include "ofxOsc.h"


class Sprinkle{
  public:
 
    // Constructors
    Sprinkle(const ofxOscMessage &m);
    Sprinkle(float maxVel, float maxAcc);
    
    // Standard OF functions
    void draw();
    void update(float maxVel, float maxAcc, bool beFroze);
    
    // Custom functions
    ofxOscMessage createOSCMessage() const;
    bool isOffScreen();
    
    float getX() const {return x;};
    float getY() const {return y;};
    float getMaxY() const{return maxY;};
    float getXPos() const { return xPos; };
    float getYPos() const { return yPos; };
    float getFree1() const { return free1; };
    float getFree2() const { return free2; };
    bool canTrack() const { return track; };
    float getRad() const { return rad; };
    ofVec2f getPos() const { return ofVec2f(xPos, yPos); }
    ofVec2f * getPosP() { return & pos; }
    void setTracked(bool t) { track = t; };

  protected:
    float maxY;
    float x;
    float y;
    float xVel;
    float yVel;
    float xAcc;
    float yAcc;
    float free1;
    float free2;
    float xPos;
    float yPos;
    bool track;
    float rad;
    ofVec2f pos;
};