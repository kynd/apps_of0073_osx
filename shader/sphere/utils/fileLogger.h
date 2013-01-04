#ifndef __FILE_LOGGER__
#define __FILE_LOGGER__


#include "ofMain.h"

class FileLogger{
	
public:
	static void open(string filename);
	static void close();
	static void write(string str);
	static void endl();
	static bool bOpen;
	static ofstream* ofs;
};

#endif

