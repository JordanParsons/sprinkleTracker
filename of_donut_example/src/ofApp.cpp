#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(30);
    ofBackgroundGradient(10,0, OF_GRADIENT_CIRCULAR);
    
    stars.setupField(5000);
    recorder.setup(LOADING, 3000);
    tree = new Quadtree(0, ofGetWindowRect());
    addingConst = false;
    drawGridForFun = false;
    bufferA.allocate(ofGetWidth(),ofGetHeight());
    
    shaderBlurA.load("blur");
    shaderBlurA.setUniform1f("resolution", 2048);
    
    announce.load("frabk.ttf", 24);
    search.load("overlay-search.png");
    result.load("overlay-result.png");
    donutCop.setId(0);
    
};

//--------------------------------------------------------------
void ofApp::update(){
    stars.updateField();
    donutCop.update(sprinkles.size());
    delete tree;
    tree = new Quadtree(0, ofGetWindowRect());
    
    if(!paused){
        // Update the sprinkle system
        bool beFrozen = (recorder.isWorking() || recorder.isScanning());
        for (auto& p : sprinkles) {
            p.update(donutCop.maxVelocity(),donutCop.maxAcceleration(), beFrozen);
            
        }
    }
    
    // add new sprinkles from messages
    while (donutCop.hasNewSprinkles()) {
        sprinkles.push_back(donutCop.getSprinkle());
        if(recorder.isWaiting() && ofRandom(100) > 95){
            Sprinkle  test = sprinkles.back();
            sprinkles.pop_back();
            test.setTracked(true);
            sprinkles.push_back(test);
            cout << "new"<<endl;
        }
    }
    
    if(createSprinkles()){
        //Sprinkles were created.
    }
    if(removeSprinkles()){
        //Sprinkles were removed
    }
    donutData.setSprinkePointer(&sprinkles);
    recorder.update(&sprinkles);
    for (auto& p : sprinkles){
        if(p.canTrack())
            tree->insertVec(p.getPosP());
    }
    
    if(recorder.isDoneScanning()){
        cout<<endl<<"DONE"<<endl;
        shouldStartAdding = ofGetElapsedTimeMillis() + ofRandom(500,2500);
    }
    
    if(shouldStartAdding < ofGetElapsedTimeMillis() && addingConst == false){
        addingConst = true;
        addConstilation();
        addStarted = ofGetElapsedTimeMillis();
    }
    
    if(addStarted + 1000 < ofGetElapsedTimeMillis()){
        addingConst = false;
        shouldStartAdding = 18446744079551615;
        addStarted = shouldStartAdding;
    }
    
    if(recorder.isWaiting() && (ofRandom(10000)>9998)){
        drawGridForFun = true;
        turnGridOffAt = ofGetElapsedTimeMillis() + ofRandom(1500,3000);
    }
    if(ofGetElapsedTimeMillis() > turnGridOffAt){
        drawGridForFun = false;
        turnGridOffAt =18446744079551615;
    }
    
        searchRad += searchRadSetp;
        stars.setSearchRad(int(searchRad));
    if ( searchRad >  maxSearchRad){
        searchRadSetp = -0.05;
    }else if( searchRad < minSearchRad){
        searchRadSetp = 0.05;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    float blur = ofMap(mouseX, 0, ofGetWidth(), 0, 10, true);
    bufferA.begin();
        //ofClear(0,0,0,0);
        //ofBackground(0,0,0,255);
        ofBackgroundGradient(25,0, OF_GRADIENT_CIRCULAR);
        stars.drawField();
    bufferA.end();
    
    shaderBlurA.begin();
        shaderBlurA.setUniform1f("max_radius", 2);
        shaderBlurA.setUniformTexture("tex", bufferA.getTexture(), 0);
        bufferA.draw(0,0);
    shaderBlurA.end();
    
    stars.drawConns(&sprinkles);
    stars.drawField();
    
    stars.drawTree(recorder.isLoading() || drawGridForFun);
    
    donutData.draw();
    
    for (auto& p : sprinkles) { p.draw();}
    recorder.draw();
    if(recorder.isWorking() || recorder.isScanning()){
        drawTrackedLine();
    }
    
    ofSetColor(255, 0, 0);
    drawTree(recorder.isScanning());
    
    ofSetColor(100);
    ofDrawBitmapString("v0.1.3-sprinkleTracker-id:"+ofToString(donutCop.getId()), 10, ofGetHeight() - 10);
    ofDrawBitmapString("FPS: "+ofToString(round(ofGetFrameRate())), ofGetWidth() - 70, ofGetHeight() - 10);
    
    
    
    if(addingConst){
        ofSetColor(255);
        result.draw((ofGetWidth()-800)/2,(ofGetHeight()-600)/2, 800, 600);
        //announce.drawString("NEW STAR:", ofGetWidth()/2, ofGetHeight()/2);
    }
}

void ofApp::addConstilation(){
    
}

void ofApp::drawTree(bool draw){
    if(draw != lastDrawTree){
        blinkTree = true;
        lastDrawTree = draw;
        treeBlinkTime = ofGetElapsedTimeMillis();
        currentTreeBlink = 0;
    }
    int blinkDelay = 75 - currentTreeBlink*10;
    if(treeBlinkTime + blinkDelay < ofGetElapsedTimeMillis() && currentTreeBlink <= 6){
        treeBlinkTime = ofGetElapsedTimeMillis();
        blinkTree = !blinkTree;
        currentTreeBlink++;
        if(currentTreeBlink == 6){
            blinkTree = draw;
            currentTreeBlink++;
            cout<<draw;
        }
    }
    
    if(blinkTree){
        ofNoFill();
        if(draw){
            ofSetColor(255,70,0, 5 * currentTreeBlink);
        }else{
            ofSetColor(255,70,0, 5 * (6-currentTreeBlink));
        }
        tree->draw();
        ofSetColor(255,255);
        search.draw((ofGetWidth()-800)/2,(ofGetHeight()-600)/2, 800, 600);
    }
}

void ofApp::drawTrackedLine() {
    Sprinkle *past;
    int searchRad = 250;
    ofNoFill();
    ofSetColor(0, 0, 255, 255);
    for (auto& p : sprinkles){
        if(!p.canTrack())
            continue;
        vector<ofVec2f*> near = tree->queryArea(AABB(ofVec2f(p.getXPos()-searchRad, p.getYPos()-searchRad), ofVec2f(searchRad*2,searchRad*2)));
        for (auto& star : near){
            ofDrawLine(star->x, star->y, p.getXPos(), p.getYPos());
        }
    }

    
    ofSetColor(0, 0, 255,50);
    bool first = true;
    for (auto& p : sprinkles){
        if(!p.canTrack())
            continue;
        if(!first){
            ofDrawLine(p.getPos(), past->getPos());
            first = false;
        }
        first = false;
        past = &p;
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    bufferA.allocate(w, h);
    stars.renewField();
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