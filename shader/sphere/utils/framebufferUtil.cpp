#include "framebufferUtil.h"

FramebufferUtil::FramebufferUtil(int n, bool fy):
flipY(fy),
initAntiAliasUtil(false)
{
    num = n;
	textures = new GLuint[n];
	renderbuffers = new GLuint[n];
	framebuffers = new GLuint[n];
	glGenTextures(n, textures);
	glGenRenderbuffersEXT(n, renderbuffers);
	glGenFramebuffersEXT(n, framebuffers);	
}

FramebufferUtil::~FramebufferUtil() {
	delete[] textures;
	delete[] renderbuffers;
	delete[] framebuffers;
	
	if (_vertices)
		delete[] _vertices;
	if (_normals)
		delete[] _normals;
	if (_indices)
		delete[] _indices;
	if (_texCoords)
		delete[] _texCoords;
	_vertices = _normals = _texCoords = NULL;
	_indices = NULL;
}	

void FramebufferUtil::initBuffer(int n, int w, int h, GLenum format) {
	if (n < 0 || n >= num) {
		return;
	}
	
	//texture
	glBindTexture(GL_TEXTURE_2D, textures[n]);
	glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, 0);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
	//renderbuffer
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, renderbuffers[n]);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT,w, h);
	
	//framebuffer
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffers[n]);
	
	//binding
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, textures[n], 0);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, renderbuffers[n] );

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void FramebufferUtil::bind(int n) {
	if (n < 0 || n >= num) {
		return;
	}
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffers[n]);
}

void FramebufferUtil::unbind() {
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void FramebufferUtil::bindTexture(int n) {
	if (n < 0 || n >= num) {
		return;
	}
	glBindTexture(GL_TEXTURE_2D, textures[n]);
}

void FramebufferUtil::copyToTexture(int n, int w, int h) {
	if (n < 0 || n >= num) {
		return;
	}
	bindTexture(n); 
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, w, h);
}


void FramebufferUtil::antiAliasUtilSetup(int n, float magnitude) {
    cout << num;
	if (n < 0 || n >= num) {
		return;
	}
	
    cout << "#";
	if (initAntiAliasUtil) {
		return;
	}
     cout << "#";
	initAntiAliasUtil = true;
	antiAliasBuffNum = n;
	antiAliasMagnitude = magnitude;
	initBuffer(antiAliasBuffNum, ofGetWidth() * antiAliasMagnitude, ofGetHeight() * antiAliasMagnitude, GL_RGBA);
	
	
	_numVerts = 4;
	_vertices = new GLfloat[_numVerts * 3];
	_normals = new GLfloat[_numVerts * 3];
	_texCoords = new GLfloat[_numVerts * 2];
	_indices = new GLushort[_numVerts];
	
	GLfloat* vertPtr = _vertices;
	GLfloat* normPtr = _normals;
	GLfloat* texCoordPtr = _texCoords;
	GLushort* indexPtr = _indices;
	
	*indexPtr++ = 0;
	vertPtr[0] = 0.0; vertPtr[1] = 0.0; vertPtr[2] = 0.0;
	normPtr[0] = 0.f; normPtr[1] = 0.f; normPtr[2] = 1.f;
	texCoordPtr[0] = 0.0; texCoordPtr[1] = 1.0;
	vertPtr += 3; normPtr += 3; texCoordPtr += 2;
	
	*indexPtr++ = 1;
	vertPtr[0] = 0.0; vertPtr[1] = ofGetHeight(); vertPtr[2] = 0.0;
	normPtr[0] = 0.f; normPtr[1] = 0.f; normPtr[2] = 1.f;
	texCoordPtr[0] = 0.0; texCoordPtr[1] = 0.0;
	vertPtr += 3; normPtr += 3; texCoordPtr += 2;
	
	*indexPtr++ = 2;
	vertPtr[0] = ofGetWidth(); vertPtr[1] = ofGetHeight(); vertPtr[2] = 0.0;
	normPtr[0] = 0.f; normPtr[1] = 0.f; normPtr[2] = 1.f;
	texCoordPtr[0] = 1.0; texCoordPtr[1] = 0.0;
	vertPtr += 3; normPtr += 3; texCoordPtr += 2;
	
	*indexPtr++ = 3;
	vertPtr[0] = ofGetWidth(); vertPtr[1] = -0.0; vertPtr[2] = 0.0;
	normPtr[0] = 0.f; normPtr[1] = 0.f; normPtr[2] = 1.f;
	texCoordPtr[0] = 1.0; texCoordPtr[1] = 1.0;
    
    cout << _indices[0] << "\n";
    cout << _indices[1] << "\n";
    cout << _indices[2] << "\n";
    cout << _indices[3] << "\n";
}

void FramebufferUtil::antiAliasOffScreenRender() {
	bind(antiAliasBuffNum);
	setupScreen(ofGetWidth() * antiAliasMagnitude, ofGetHeight() * antiAliasMagnitude);
	ofPushMatrix();
	ofScale(antiAliasMagnitude, antiAliasMagnitude, antiAliasMagnitude);
}

void FramebufferUtil::antiAliasScreenRender() {
	
	ofPopMatrix();
	bindTexture(antiAliasBuffNum);
	copyToTexture(antiAliasBuffNum, ofGetWidth() * antiAliasMagnitude, ofGetHeight() * antiAliasMagnitude);
	unbind();
	setupScreen();
	glDisable(GL_LIGHTING);
	
	glPushClientAttrib( GL_CLIENT_VERTEX_ARRAY_BIT );
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, _vertices );
	glNormalPointer( GL_FLOAT, 0, _normals );
	glTexCoordPointer(2, GL_FLOAT, 0, _texCoords);
	glDrawElements( GL_QUADS, _numVerts, GL_UNSIGNED_SHORT, _indices );
	glPopClientAttrib();
}


void FramebufferUtil::setupScreen() {
	setupScreen(ofGetWidth(), ofGetHeight());
}
void FramebufferUtil::setupScreen(int w, int h) {
	setupScreen(w, h, 60.0, (float)w / 2.0, (float)h / 2.0);
}
void FramebufferUtil::setupScreen(int w, int h, float screenFov, float eyeX, float eyeY){
	glViewport(0, 0, w, h);
	
	float theTan, aspect, halfFov;
	halfFov 		= PI * screenFov / 360.0;
	theTan 			= tanf(halfFov);
	float dist 		= eyeY / theTan;
	float nearDist 	= dist / 10.0;	// near / far clip plane
	float farDist 	= dist * 10.0;
	aspect 			= (float)w/(float)h;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(screenFov, aspect, nearDist, farDist);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, dist, eyeX, eyeY, 0.0, 0.0, 1.0, 0.0);
	
	if (flipY) {
		glScalef(1, -1, 1);           // invert Y axis so increasing Y goes down.
		glTranslatef(0, -h, 0);       // shift origin up to upper-left corner.
	}
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FramebufferUtil::clear(float r, float g, float b) {
	glClearColor(r,g,b,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
