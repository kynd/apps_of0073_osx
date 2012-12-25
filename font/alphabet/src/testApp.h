#pragma once

#include "ofMain.h"
#include "Tracer.h"
#include "utils.h"

class testApp : public ofSimpleApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased (int key);

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void setCol();
		
		ofTrueTypeFont testFont;
		ofTrueTypeFont testFont2;
		ofTTFCharacter testChar;
		char letter;
    vector<Tracer*> t;
    ofImage canvas;
    int adjX, adjY;
    
	VideoSaver v;
    float r,g,b,tr,tg,tb;
    float offset;
};

