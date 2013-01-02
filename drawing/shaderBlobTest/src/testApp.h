#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"

//#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
								// otherwise, we'll use a movie file

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

    ofImage sample;
    ofImage contourSample;
    ofxCvColorImage			colorCVImg;
    ofxCvGrayscaleImage 	grayCVImg;
    ofxCvContourFinder 	contourFinder;
    int threshold;
    
    ofFbo fbo;
    ofFbo drawBuffer;
    ofShader shader;
};

