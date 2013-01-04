
#include "fileReader.h"


bool FileReader::bOpen = false;
ifstream* FileReader::ifs;
void FileReader::open(string filename) {
	ifs = new ifstream();
	ifs->open(ofToDataPath(filename).c_str());
	bOpen = true;
}
void FileReader::close() {
	ifs->close();
	bOpen = false;
}
string FileReader::readLine() {
	if(!bOpen) { return ""; }
	
	if (*ifs == NULL) { return  "";}
	string str;
	getline(*ifs, str);
	return str;
}