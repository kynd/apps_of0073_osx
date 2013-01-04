#ifndef __SOUND_LOGGER__
#define __SOUND_LOGGER__


#include "ofMain.h"

class SoundLogger{
	
public:
	SoundLogger(int fr, string filename, int nb, bool b = false, bool a = false);
	~SoundLogger();
	bool update();
	void setEnabled(bool b);
	float * fftSmoothed;
	ofstream* ofs;
	ifstream* ifs;
	int frameRate;
	int lastFrame;
	int startedMillis;
	bool bEnabled;
	int nBandsToGet;
	int lastReadFrame;
	int currentFrame;
	bool bReadFile;
	bool bAsync;
	void readSound();
	void readFile(int currentFrame);
	void writeFile(int currentFrame);
	vector<string> split(string s, string c);
	void draw();
	string log;
};

#endif

