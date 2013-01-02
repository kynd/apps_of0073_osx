#include "videoSaver.h"
VideoSaver::VideoSaver() : 
num(0),
enabled(true)
{
};
void VideoSaver::save() {
	if (!num) { 
		num = 0;
	}
	sprintf(file_name, "output/output_%.5i.jpg", num);
	img_saver.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	printf("Saving file: %s\n", file_name);
	img_saver.saveImage(file_name);
	num ++;
}

void VideoSaver::setEnabled(bool b) {
	enabled = b;
}

void VideoSaver::setNum(int n) {
	num = n;
}