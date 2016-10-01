#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetLogLevel(OF_LOG_VERBOSE);

    ofBackgroundGradient(10,0, OF_GRADIENT_CIRCULAR);

    stars.setupField(7500);
    recorder.setup(LOADING, 3000);
    
    bufferA.allocate(ofGetWidth(),ofGetHeight());
    bufferB.allocate(ofGetWidth(),ofGetHeight());
    
    shaderBlurA.load("blur");

    shaderBlurB.load("shaderBlurY");
    shaderBlurA.setUniform1f("resolution", 1024);

};

//--------------------------------------------------------------
void ofApp::update(){
    stars.updateField();
  donutCop.update(sprinkles.size());
    
if(!paused){
  // Update the sprinkle system
  for (auto& p : sprinkles) {
    p.update(donutCop.maxVelocity(),donutCop.maxAcceleration());
  }
}

  // add new sprinkles from messages
  while (donutCop.hasNewSprinkles()) {
    sprinkles.push_back(donutCop.getSprinkle());
  }

    if(createSprinkles()){
            //Sprinkles were created.
    }
    if(removeSprinkles()){
        //Sprinkles were removed
    }
    donutData.setSprinkePointer(&sprinkles);
    recorder.update(&sprinkles);
}

//--------------------------------------------------------------
void ofApp::draw(){
    float blur = ofMap(mouseX, 0, ofGetWidth(), 0, 10, true);
    bufferA.begin();
    ofClear(0,0,0,0);
        ofBackground(0,0,0,255);
        ofBackgroundGradient(25,0, OF_GRADIENT_CIRCULAR);
        stars.drawField();
        stars.drawConns(&sprinkles);
        //stars.drawField();
    
    
    bufferA.end();

    shaderBlurA.begin();
    shaderBlurA.setUniform1f("max_radius", 1);
    shaderBlurA.setUniformTexture("tex", bufferA.getTexture(), 0);
    bufferA.draw(0,0);
    shaderBlurA.end();
    
    stars.drawField();

    donutData.draw();
    for (auto& p : sprinkles) { p.draw();}
    recorder.draw();
    
    for (auto& p : sprinkles) { p.draw();}

    
    
    
    recorder.draw();
    
    ofSetColor(100);
    ofDrawBitmapString("v0.0.3-sprinkleTracker-id:"+ofToString(donutCop.getId()), 10, ofGetHeight() - 10);
    ofDrawBitmapString("FPS: "+ofToString(round(ofGetFrameRate())), ofGetWidth() - 70, ofGetHeight() - 10);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    bufferA.allocate(w, h);
    bufferB.allocate(w, h);
}
void ofApp::keyPressed(int key) {
    if (key == '0'){donutCop.setId(0);}
    if (key == '1'){donutCop.setId(1);}
    if (key == '2'){donutCop.setId(2);}
    if (key == 'p'){paused = !paused;}
    
}

//--------------------------------------------------------------
bool ofApp::createSprinkles() {

  // Check with the donut cop if you're allowed to create a new sprinkle
  if (donutCop.allowedToCreateSprinkle(sprinkles.size())) {

    // Create a new sprinkle
    Sprinkle p(donutCop.maxVelocity(), donutCop.maxAcceleration());

    // Add it to the sprinkles list
    sprinkles.push_back(p);

    // Tell the cop that we created one, so it can keep track
    // of how many have been created. 
    donutCop.mentionNewSprinkle();
      return true;
  }
    return false;
}

//--------------------------------------------------------------
bool ofApp::removeSprinkles() {
    bool sprinkeRemoved = false;
  // Loop through and broadcast offscreen sprinkles
  for (auto& p : sprinkles) {
    if (p.isOffScreen()){
      donutCop.broadcastSprinkle(p);
        sprinkeRemoved = true;
    }
  }
  
  // Loop through and remove offscreen sprinkles 
  sprinkles.erase(
    remove_if(sprinkles.begin(), sprinkles.end(), [](Sprinkle p) { return p.isOffScreen();}),
  sprinkles.end());
    
    return sprinkeRemoved;
}