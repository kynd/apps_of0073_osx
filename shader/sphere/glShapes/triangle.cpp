#include "triangle.h"

Triangle::Triangle( GLfloat verts[9]  )
: _vertices( NULL ),
_normals( NULL ),
_indices( NULL ),
_idxStart( 0 ),
_idxEnd( 0 ),
_valid( false ),
_numVerts( 4 )
{
	 _vertices = new GLfloat[_numVerts * 3];
	 GLfloat* vertPtr = _vertices;
	 for (int i = 0; i < _numVerts * 3; i ++) {
	 vertPtr[i] = verts[i];
	 }
}

Triangle::~Triangle()
{
	if ( _valid )
	{
		if (_vertices)
			delete[] _vertices;
		if (_normals)
			delete[] _normals;
		if (_indices)
			delete[] _indices;
		_vertices = _normals = NULL;
		_indices = NULL;
		_valid = false;
	}
}

void Triangle::draw(){
	if (!_valid)
	{
		if (!init())
			return;
	}
	
	glPushClientAttrib( GL_CLIENT_VERTEX_ARRAY_BIT );
	
	// enable and allocate data
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, _vertices );
	glNormalPointer( GL_FLOAT, 0, _normals );
	
    // draw
	glDrawElements( GL_TRIANGLES, _numVerts, GL_UNSIGNED_SHORT, _indices );
	
	glPopClientAttrib();
}

bool Triangle::init() {
	
	_normals = new GLfloat[_numVerts * 3];
	_indices = new GLushort[ _numVerts ];
	
	GLfloat* vertPtr = _vertices;
	GLfloat* normPtr = _normals;
	GLushort* indexPtr = _indices;
	
	int idx = 0;
	
	// Triangle body
	_idxStart = idx;

	GLfloat a1, a2, a3, b1, b2, b3;
	
	a1 = vertPtr[0] - vertPtr[3];
	a2 = vertPtr[1] - vertPtr[4];
	a3 = vertPtr[2] - vertPtr[5];
	b1 = vertPtr[6] - vertPtr[3];
	b2 = vertPtr[7] - vertPtr[4];
	b3 = vertPtr[8] - vertPtr[5];
	
	for (int i = 0; i < _numVerts; i ++) {
		
		normPtr[0] = (a2 * b3 - a3 * b2);
		normPtr[1] = (a3 * b1 - a1 * b3);
		normPtr[2] = (a1 * b2 - a2 * b1);
		normPtr += 3;
		
		*indexPtr++ = idx++;
	}
	
	_idxEnd = idx;
	
	return( _valid = true );
}
