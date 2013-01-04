#ifndef __FILE_READER__
#define __FILE_READER__


#include "ofMain.h"

class FileReader{
	
public:
	static void open(string filename);
	static void close();
	static string readLine();
	static bool bOpen;
	static ifstream* ifs;
};

#endif

