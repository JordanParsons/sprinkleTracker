#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "sprinkle.h"
#include "donut_cop.h"
#include "donut_data.h"
#include "star_field.h"
#include "sprinkle_recorder.h"
#include "QuadTree.h"

#define HC_HEIGHT 1920
#define HC_WIDTH 1080


class ofApp : public ofBaseApp{

  public:

		// Generic OF functions
		void setup();
		void update();
		void draw();
        void drawTrackedLine();
    void drawTree(bool draw);

		// OF Events
		void windowResized(int w, int h);
		void keyPressed(int key);

		DonutCop donutCop;

		// Sprinkle functions
		std::vector<Sprinkle> sprinkles;  // The vector of sprinkles
		bool createSprinkles();
		bool removeSprinkles();
    
        DonutData donutData;
        StarField stars;
        SprinkleRecorder recorder;
    
        ofTrueTypeFont announce;
    
            bool addingConst;
        std::vector<vector<float*>> constilations;
    
        void addConstilation();
    long addStarted;
    ofImage search;
    ofImage result;
    long shouldStartAdding;
    
    bool drawGridForFun;
    long turnGridOffAt;
    
    
        bool doneScanning;
    
        ofShader shaderBlurA;
        ofFbo bufferA;

    
        Quadtree * tree;
 
        bool paused = false;
    
    int maxSearchRad = 150;
    int minSearchRad = 25;
    float searchRadSetp = 0.05;
    float searchRad = 50;
    
        //tree
    bool blinkTree;
    bool lastDrawTree;
    int currentTreeBlink;
    long treeBlinkTime;

};
