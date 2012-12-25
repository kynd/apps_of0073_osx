#include "testApp.h"
 
//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0,0,0);
    ofSetFrameRate(30);

	testFont.loadFont("verdana.ttf", 500, true, true, true);

	letter = '0';
	testChar = testFont.getCharacterAsPoints(letter);
	ofSetFullscreen(false);
    
    adjX = - 240;
    adjY = 240;
    
    for (int i = 0; i < 19880; i ++) {
        t.push_back(new Tracer());
        t[i]->x = ofRandom(0,ofGetWidth());
        t[i]->y = ofRandom(0,ofGetHeight());
        t[i]->target0 = ofRandom(0, (int)testChar.getOutline().size());
        t[i]->target1 = ofRandom(0, (int)testChar.getOutline()[t[i]->target0].size());
    }
    
    canvas.allocate(1280, 720, OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void testApp::update(){
    for (int i = 0; i < t.size(); i ++) {
        if (t[i]->target0 >= (int)testChar.getOutline().size() || ofRandom(0, 1) < 0.001) {
            
            t[i]->target0 = ofRandom(0, (int)testChar.getOutline().size());
            t[i]->target1 = ofRandom(0, (int)testChar.getOutline()[t[i]->target0].size());
        }
        if (t[i]->target1 > (int)testChar.getOutline()[t[i]->target0].size()) {
            t[i]->target0 = ofRandom(0, (int)testChar.getOutline().size());
            t[i]->target1 = ofRandom(0, (int)testChar.getOutline()[t[i]->target0].size());
        }
        
        float dx = (testChar.getOutline()[t[i]->target0].getVertices()[t[i]->target1].x + ofGetWidth() / 2 + adjX) - t[i]->x;
        float dy = (testChar.getOutline()[t[i]->target0].getVertices()[t[i]->target1].y + ofGetHeight() / 2 + adjY) - t[i]->y;
        float dist = sqrt(dx * dx + dy * dy);
        t[i]->vx += dx / dist * 0.4;
        t[i]->vy += dy / dist * 0.4;
        t[i]->proceed();
        
        
        
        if (dist <= t[i]->maxSpeed * 4) {
            t[i]->target1 += 1;
            t[i]->target1 %= (int)testChar.getOutline()[t[i]->target0].size();
        }
        
    }
    if (ofGetFrameNum() % 360 == 0 && ofGetFrameNum() != 0) {
        letter ++;
        testChar = testFont.getCharacterAsPoints(letter);
        cout << "++ ";
    }
    
    if (ofGetFrameNum() % 2 == 0) {
		v.save();
	}
    if (ofGetFrameNum() >= 360 * 12) {
		
        std::exit(0);
	}

}

//--------------------------------------------------------------
void testApp::draw(){
    if (ofGetFrameNum() == 0) {
        canvas.grabScreen(0, 0, 1280, 720);
    }
	ofFill();
    
    canvas.draw(0, 0);

    unsigned char* pixels = canvas.getPixels();
    
    for (int i = 0; i < t.size(); i ++) {
        int x = t[i]->x;
        int y = t[i]->y;
        pixels[(y * ofGetWidth() + x) * 3 ] = min(255, pixels[(y * ofGetWidth() + x) * 3] + 12);
        pixels[(y * ofGetWidth() + x) * 3 + 1] = min(255, pixels[(y * ofGetWidth() + x) * 3 + 1] + 12);
        pixels[(y * ofGetWidth() + x) * 3 + 2] = min(255, pixels[(y * ofGetWidth() + x) * 3 + 2] + 12);
    }
    canvas.update();
    canvas.draw(0, 0);
    
    
    int alpha = 10;
    if (ofGetFrameNum() > 360  * 10) {
        alpha += ofGetFrameNum() - 360 * 10; 
    }
    ofEnableAlphaBlending();
    ofSetColor(0, 0, 0, alpha);
    ofRect(0, 0, 1280, 720);
    ofSetColor(255,255,255, 255);
    canvas.grabScreen(0, 0, 1280, 720);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	testChar = testFont.getCharacterAsPoints(key);
	letter = key;
    for (int i = 0; i < t.size(); i ++) {
        t[i]->target0 = ofRandom(0, (int)testChar.getOutline().size());
        t[i]->target1 = ofRandom(0, (int)testChar.getOutline()[t[i]->target0].size());
    }
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
