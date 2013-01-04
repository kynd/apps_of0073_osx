#include "cube.h"


Cube::Cube( float size )
: _size( size ),
_vertices( NULL ),
_normals( NULL ),
_indices( NULL ),
_idxStart( 0 ),
_idxEnd( 0 ),
_valid( false ),
_numVerts( 0 )
{
}

Cube::~Cube()
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

void Cube::draw(){
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
	glDrawElements( GL_QUADS, _numVerts, GL_UNSIGNED_SHORT, _indices );
	
	glPopClientAttrib();
}

bool Cube::init() {
	_numVerts = 6 * 4;
	
	_vertices = new GLfloat[_numVerts * 3];	
	_normals = new GLfloat[_numVerts * 3];
	_indices = new GLushort[ _numVerts ];
	GLfloat* vertPtr = _vertices;
	GLfloat* normPtr = _normals;
	GLushort* indexPtr = _indices;
	
	const float halfSize = _size * .5f;
	int idx = 0;
	
	// Cube body
	_idxStart = idx;
	
	GLfloat verts[] = {
		
		-halfSize, -halfSize, halfSize,	-halfSize, halfSize, halfSize,
		halfSize, halfSize, halfSize,	halfSize, -halfSize, halfSize,
		
		halfSize, -halfSize, halfSize,	halfSize, halfSize, halfSize,
		halfSize, halfSize, -halfSize,	halfSize, -halfSize, -halfSize,
		
		-halfSize, -halfSize, -halfSize,	halfSize, -halfSize, -halfSize,
		halfSize, halfSize, -halfSize,	-halfSize, halfSize, -halfSize,
		
		-halfSize, -halfSize, -halfSize,	-halfSize, halfSize, -halfSize,
		-halfSize, halfSize, halfSize,	-halfSize, -halfSize, halfSize,
		
		-halfSize, halfSize, halfSize,	-halfSize, halfSize, -halfSize ,
		halfSize, halfSize, -halfSize,	halfSize, halfSize, halfSize,
		
		-halfSize, -halfSize, halfSize,		halfSize, -halfSize, halfSize ,
		halfSize, -halfSize, -halfSize,		-halfSize, -halfSize, -halfSize 
	};
	
	GLfloat norms[] = {
		0.f, 0.f, 1.f,	0.f, 0.f, 1.f,
		0.f, 0.f, 1.f,	0.f, 0.f, 1.f,
		
		1.f, 0.f, 0.f,	1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,	1.f, 0.f, 0.f,
		
		0.f, 0.f, -1.f,	0.f, 0.f, -1.f,
		0.f, 0.f, -1.f,	0.f, 0.f, -1.f,
		
		-1.f, 0.f, 0.f,	-1.f, 0.f, 0.f,
		-1.f, 0.f, 0.f,	-1.f, 0.f, 0.f,
		
		0.f, 1.f, 0.f,	0.f, 1.f, 0.f,
		0.f, 1.f, 0.f,	0.f, 1.f, 0.f,
		
		0.f, -1.f, 0.f,	0.f, -1.f, 0.f,
		0.f, -1.f, 0.f,	0.f, -1.f, 0.f
	};
	
	for (int i = 0; i < _numVerts; i ++) {
		vertPtr[0] = verts[i * 3];
		vertPtr[1] = verts[i * 3 + 1];
		vertPtr[2] = verts[i * 3 + 2];
		vertPtr += 3;
		
		normPtr[0] = norms[i * 3];
		normPtr[1] = norms[i * 3 + 1];
		normPtr[2] = norms[i * 3 + 2];
		normPtr += 3;
		
		*indexPtr++ = idx++;
	}
	
	_idxEnd = idx;
	
	
	
	return( _valid = true );
}
