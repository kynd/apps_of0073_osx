
#ifndef __FRAMEBUFFER_UTIL__
#define __FRAMEBUFFER_UTIL__


#include "ofMain.h"

class FramebufferUtil {
public:
    FramebufferUtil(int n, bool flipY = false);
    ~FramebufferUtil();
	void initBuffer(int n, int w, int h, GLenum format);
	void bind(int n);
	void unbind();
	void setupScreen();
	void setupScreen(int w, int h);
	void setupScreen(int w, int h, float screenFov, float eyeX, float eyeY);
	void copyToTexture(int n, int w, int h);
	void bindTexture(int n);
	void antiAliasUtilSetup(int n, float magnitude);
	void antiAliasOffScreenRender();
	void antiAliasScreenRender();
	void clear(float r, float g, float b);
	
private:
	int num;
	bool flipY;
	GLuint* textures;
	GLuint* framebuffers;
	GLuint* renderbuffers;
	int antiAliasBuffNum;
	float antiAliasMagnitude;
	
	//antiAliasDraw
	GLfloat* _vertices;
    GLfloat* _normals;
	GLfloat* _texCoords;
    GLushort* _indices;
	int _numVerts;
	
	bool initAntiAliasUtil;
};


#endif
