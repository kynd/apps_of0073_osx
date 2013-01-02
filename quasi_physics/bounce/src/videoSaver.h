#ifndef __VIDEO_SAVER__
#define __VIDEO_SAVER__

#include "ofMain.h"
class VideoSaver {
public:
	VideoSaver();
	void save();
	void setEnabled(bool b);
	void setNum(int n);
private:
	int num;
	bool enabled;
	char file_name[255];
	ofImage img_saver;
};


#endif
