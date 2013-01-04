
#ifndef __TEXTURE_UTIL_2D__
#define __TEXTURE_UTIL_2D__

#include "ofMain.h"

class TextureUtil2D {
public:
	TextureUtil2D(int n = 8);
    ~TextureUtil2D();
	
    void setTexture(unsigned char * pixels, int n, int w, int h, GLenum format = GL_RGB);
    void setTexture(GLvoid * pixels, int n, int w, int h, GLenum format = GL_RGB);
	void bind(int n);
	GLuint getTexture(int n);
	
private:
	int num;
	GLuint* textures;
};


#endif
