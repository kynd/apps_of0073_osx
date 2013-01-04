#include "lines.h"

Lines::Lines( int length, GLfloat verts[], GLfloat color[], GLfloat width  )
: _vertices( NULL ),
_indices( NULL ),
_idxStart( 0 ),
_idxEnd( 0 ),
_valid( false ),
_numVerts( length * 2 ),
_width(width)
{
	_vertices = new GLfloat[_numVerts * 3];
	GLfloat* vertPtr = _vertices;
	for (int i = 0; i < _numVerts * 3; i ++) {
		vertPtr[i] = verts[i];
	}
	_color = new GLfloat[4];
	GLfloat* colPtr = _color;
	
	for (int i = 0; i < 4; i ++) {
		colPtr[i] = color[i];
	}
}


Lines::~Lines()
{
	if ( _valid )
	{
		if (_vertices)
			delete[] _vertices;
		if (_indices)
			delete[] _indices;
		_vertices =  NULL;
		_indices = NULL;
		_valid = false;
	}
}

void Lines::draw(){
	if (!_valid)
	{
		if (!init())
			return;
	}
	
	glPushClientAttrib( GL_CLIENT_VERTEX_ARRAY_BIT );
	glPushAttrib( GL_ALL_ATTRIB_BITS ); 
	glDisable(GL_LIGHTING);
	glLineWidth(_width);
	glColor4f(_color[0],_color[1],_color[2],_color[3]); 
	glEnable(GL_LINE_SMOOTH);	
	
	// enable and allocate data
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, _vertices );
	glNormalPointer( GL_FLOAT, 0, _normals );
	
    // draw
	glDrawElements( GL_LINES, _numVerts, GL_UNSIGNED_SHORT, _indices );

	glPopAttrib();
	glPopClientAttrib();
}

bool Lines::init() {
	
	_normals = new GLfloat[_numVerts * 3];
	_indices = new GLushort[ _numVerts ];
	
	GLfloat* vertPtr = _vertices;
	GLfloat* normPtr = _normals;
	GLushort* indexPtr = _indices;
	
	
	int idx = 0;
	
	// Lines body
	_idxStart = idx;

	for (int i = 0; i < _numVerts; i ++) {
		normPtr[0] = 0.f;
		normPtr[1] = 0.f;
		normPtr[2] = 0.f;
		normPtr += 3;
		*indexPtr++ = idx++;
	}
	
	_idxEnd = idx;
	
	
	return( _valid = true );
}
