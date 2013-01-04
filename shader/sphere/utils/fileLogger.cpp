#include "fileLogger.h"

bool FileLogger::bOpen = false;
ofstream* FileLogger::ofs;
void FileLogger::open(string filename) {
	ofs = new ofstream();
	ofs->open(ofToDataPath(filename).c_str(), ios::trunc);
	ofs->close();
	ofs->open(ofToDataPath(filename).c_str(), ios::app);
	bOpen = true;
}
void FileLogger::close() {
	ofs->close();
	bOpen = false;
}
void FileLogger::write(string str) {
	if(!bOpen) { return; }
	*ofs << str;
}

void FileLogger::endl() {
	*ofs << std::endl;
}