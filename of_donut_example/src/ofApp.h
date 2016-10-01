#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "sprinkle.h"
#include "donut_cop.h"
#include "donut_data.h"
#include "star_field.h"
#include "sprinkle_recorder.h"

class ofApp : public ofBaseApp{

  public:

		// Generic OF functions
		void setup();
		void update();
		void draw();

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
    
    ofShader shaderBlurA;
    ofShader shaderBlurB;
    ofFbo bufferA;
    ofFbo bufferB;
    
        bool paused = false;

};
