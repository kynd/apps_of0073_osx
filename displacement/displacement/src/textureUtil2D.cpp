

#include "textureUtil2D.h"

TextureUtil2D::TextureUtil2D(int n):
num(n)
{
	textures = new GLuint[n];
	glGenTextures(n, textures); 
}
TextureUtil2D::~TextureUtil2D() {
	delete[] textures;
}

void TextureUtil2D::setTexture(unsigned char * pixels, int n, int w, int h, GLenum format) {
	setTexture((GLvoid *)pixels, n, w, h, format);
}


void TextureUtil2D::setTexture(GLvoid * pixels, int n, int w, int h, GLenum format) {
	if (n < 0 || n >= num) {
		return;
	}
	glBindTexture(GL_TEXTURE_2D, textures[n]);
	glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, pixels);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureUtil2D::bind(int n) {
	if (n < 0 || n >= num) {
		return;
	}
	glBindTexture(GL_TEXTURE_2D, textures[n]);
}

GLuint TextureUtil2D::getTexture(int n) {
	return textures[n];
}