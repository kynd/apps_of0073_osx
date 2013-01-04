
#include "soundLogger.h"
#include "traceBuffer.h"
SoundLogger::SoundLogger(int fr, string filename, int nb, bool b, bool a):
frameRate(fr),
bEnabled(false),
lastFrame(0),
startedMillis(0),
nBandsToGet(nb),
bReadFile(b),
bAsync(a),
lastReadFrame(0),
currentFrame(0),
log("")
{	 
	fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++){
		fftSmoothed[i] = 0;
	}
	
	if (bReadFile) {
		ifs = new ifstream();
		ifs->open(ofToDataPath(filename).c_str());
	} else {
		ofs = new ofstream();
		ofs->open(ofToDataPath(filename).c_str(), ios::trunc);
		ofs->close();
		ofs->open(ofToDataPath(filename).c_str(), ios::app);
	}
}

SoundLogger::~SoundLogger() {
	if (bReadFile) {
		ifs->close();
		delete ifs;
	} else {
		ofs->close();
		delete ofs;
	}
}

//--------------------------------------------------------------
bool SoundLogger::update(){
	if (!bEnabled) { return false; }
	if (!bReadFile) {readSound() ;}
	if (bAsync) {
		currentFrame ++;
	} else {
		currentFrame = (ofGetElapsedTimeMillis() - startedMillis) * (float) frameRate / 1000.0;
	}
	if (currentFrame > lastFrame) {
		
		if (currentFrame > lastFrame + 1) {
			log += "errasped " + ofToString(lastFrame) + "-" + ofToString(currentFrame) + "\n";
		}
		
		lastFrame = currentFrame;
		
		if (bReadFile) {
			readFile(currentFrame);
		} else {
			writeFile(currentFrame);
		}

		return true;
	} else {
		return false;
	}

	
}

//--------------------------------------------------------------
void SoundLogger::setEnabled(bool b) {
	if (b && !bEnabled) {
		startedMillis = ofGetElapsedTimeMillis();
	}
	bEnabled = b;
}
//--------------------------------------------------------------
void SoundLogger::readSound() {
	ofSoundUpdate();
	float * val = ofSoundGetSpectrum(nBandsToGet);
	
	
	for (int i = 0;i < nBandsToGet; i++){
		// let the smoothed calue sink to zero:
		fftSmoothed[i] *= 0.90f;
		// take the max, either the smoothed or the incoming:
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
	}
}

void SoundLogger::writeFile(int currentFrame) {
	*ofs << currentFrame << ", (" <<ofGetElapsedTimeMillis() << "), ";
	for (int i = 0;i < nBandsToGet; i++){
		*ofs << fftSmoothed[i] << ", ";
	}
	*ofs << std::endl;
}

void SoundLogger::readFile(int currentFrame) {
	
	if (*ifs == NULL) { return;}
	if(currentFrame < lastReadFrame) {return; }
	string str;
	getline(*ifs, str);
	
	vector<string> tokens = split(str, ",");
	if (tokens.size() > 3) {
		lastReadFrame = ofToInt(tokens[0]);
		for (int i = 2; i < tokens.size(); i ++) {
			fftSmoothed[i - 2] = ofToFloat(tokens[i]);
		}
	}
}

vector<string> SoundLogger::split(string s, string c) {
	vector<string> ret;
	for( int i=0, n; i <= s.length(); i=n+1 ){
		
		n = s.find_first_of( c, i );
		if( n == string::npos ) n = s.length();
		string tmp = s.substr( i, n-i );
		ret.push_back(tmp);
	}
	return ret;
}

void SoundLogger::draw() {
	float width = (float)(5 * 128) / nBandsToGet;
	
	for (int i = 0;i < nBandsToGet; i++){
		ofRect(100+i*width,ofGetHeight()-100,width,-(fftSmoothed[i] * 200));
	}
}
