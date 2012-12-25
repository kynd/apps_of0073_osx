#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0,0,0);
    ofSetFrameRate(30);

	testFont.loadFont("verdana.ttf", 500, true, true, true);

	letter = 'a';
	testChar = testFont.getCharacterAsPoints(letter);
	ofSetFullscreen(false);
    
    adjX = - 240;
    adjY = 240;
    
    for (int i = 0; i < 19880; i ++) {
        t.push_back(new Tracer());
        float dist = ofRandom(0,150);
        float ang = ofRandom(0,PI * 2);
        t[i]->x = cos(ang) * dist + ofGetWidth() / 2;
        t[i]->y = sin(ang) * dist + ofGetHeight() / 2;
        t[i]->target0 = ofRandom(0, (int)testChar.getOutline().size());
        t[i]->target1 = ofRandom(0, (int)testChar.getOutline()[t[i]->target0].size());
    }
    
    canvas.allocate(1280, 720, OF_IMAGE_COLOR);
    
    tr = tg = tb = r = g = b = 0;
    setCol();
    
}

//--------------------------------------------------------------
void testApp::update(){
    for (int i = 0; i < t.size(); i ++) {
        int n = max(1.f, (float) t.size() * 100 / i); 
        
        t[i]->r += (r - t[i]->r) / 3 / n; 
        t[i]->g += (g - t[i]->g) / 3 / n; 
        t[i]->b += (b - t[i]->b) / 3 / n; 
        
        
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
    if (ofGetFrameNum() % 240 == 0 && ofGetFrameNum() != 0) {
        letter ++;
        testChar = testFont.getCharacterAsPoints(letter);
        setCol();
        for (int i = 0; i < t.size(); i ++) {
            float spd = ofRandom(20,25);
            float ang = ofRandom(0,PI * 2);
            t[i]->vx = cos(ang) * spd;
            t[i]->vy = sin(ang) * spd;
            
        }
        cout << "-- ";
    }

    if (ofRandom(0,1) < 0.05) {
        //setCol();
    }
    
    r += (tr - r) / 80;
    g += (tg - g) / 80;
    b += (tb - b) / 80;
    
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
        float rdif = tr - pixels[(y * ofGetWidth() + x) * 3];
        float gdif = tg - pixels[(y * ofGetWidth() + x) * 3 + 1];
        float bdif = tb - pixels[(y * ofGetWidth() + x) * 3 + 2];
        pixels[(y * ofGetWidth() + x) * 3 ] = min(255.f, pixels[(y * ofGetWidth() + x) * 3] + rdif / 4);
        pixels[(y * ofGetWidth() + x) * 3 + 1] = min(255.f, pixels[(y * ofGetWidth() + x) * 3 + 1] + gdif / 4);
        pixels[(y * ofGetWidth() + x) * 3 + 2] = min(255.f, pixels[(y * ofGetWidth() + x) * 3 + 2] + bdif / 4);
    }
    canvas.update();
    canvas.draw(0, 0);
    
    
    int alpha = 10;
    if (ofGetFrameNum() > 240  * 26) {
        alpha += ofGetFrameNum() - 240 * 26; 
    }
    ofEnableAlphaBlending();
    ofSetColor(0,0,0, alpha);
    ofRect(0, 0, 1280, 720);
    ofSetColor(255,255,255, 255);
    canvas.grabScreen(0, 0, 1280, 720);
    
    
    if (ofGetFrameNum() % 2 == 0) {
		v.save();
	}
    if (ofGetFrameNum() >= 240 * 30) {
		 std::exit(0);
	}
}



//--------------------------------------------------------------
void  testApp::setCol() {
    tr = ofRandom(0,255);
    tg = ofRandom(0,255);
    tb = ofRandom(0,255);
}
//--------------------------------------------------------------
void testApp::keyPressed  (int key){
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
