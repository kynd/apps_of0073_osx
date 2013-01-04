#include "traceBuffer.h"

string TraceBuffer::buff = "";
void TraceBuffer::draw() {
	ofDrawBitmapString(buff, 20,20);
}