
#include "cone.h"


Cone::Cone( float radius, float length, int slices )
: _radius( radius ),
_length( length ),
_slices( slices ),
_drawCap( true ),
_vertices( NULL ),
_normals( NULL ),
_indices( NULL ),
_capStart( NULL ),
_idxStart( 0 ),
_capIdx( 0 ),
_idxEnd( 0 ),
_valid( false ),
_numVerts( 0 ),
_numCapVerts( 0 )
{
}

Cone::~Cone()
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

void Cone::cap( bool posZ)
{
	_drawCap = posZ;
}

void Cone::draw(){
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
	if (_drawCap){
		glDrawElements( GL_TRIANGLE_FAN, _numCapVerts, GL_UNSIGNED_SHORT, _capStart );
	}
	glPopClientAttrib();
}

bool Cone::init() {
	_numVerts = (_slices) * 3;
	_numCapVerts = _slices + 2;
	
	const int totalVerts = _numVerts + _numCapVerts;
	
	_vertices = new GLfloat[ totalVerts * 3 ];
	_normals = new GLfloat[ totalVerts * 3 ];
	_indices = new GLushort[ totalVerts ];
	
	const float halfLength = _length * .5f;
	const double delta = PI * 2 / _slices;
	
	GLfloat* vertPtr = _vertices;
	GLfloat* normPtr = _normals;
	GLushort* indexPtr = _indices;
	int idx = 0;
	
	// Cone body
	_idxStart = idx;
	double theta = 0;
	int i;
	for (i=0; i<_slices; i++)
	{
		const float cosTheta0 = (float) cos( theta );
		const float sinTheta0 = (float) sin( theta );
		
		const float cosTheta1 = (float) cos( theta - delta / 2);
		const float sinTheta1 = (float) sin( theta - delta / 2);
		
		const float cosTheta2 = (float) cos( theta - delta);
		const float sinTheta2 = (float) sin( theta - delta);
		
		const float normLen = sqrt(_length * _length + _radius * _radius);
		
		vertPtr[0] = 0.f;
		vertPtr[1] = 0.f;
		vertPtr[2] = halfLength;
		vertPtr += 3;
		
		normPtr[0] = cosTheta1 * _length / normLen;
		normPtr[1] = sinTheta1 * _length / normLen;
		normPtr[2] = _radius / normLen;
		normPtr += 3;
		
		*indexPtr++ = idx++;
		
		vertPtr[0] = cosTheta0 * _radius;
		vertPtr[1] = sinTheta0 * _radius;
		vertPtr[2] = -halfLength;
		vertPtr += 3;
		
		normPtr[0] = cosTheta0 * _length / normLen;
		normPtr[1] = sinTheta0 * _length / normLen;
		normPtr[2] = _radius / normLen;
		normPtr += 3;
		
		*indexPtr++ = idx++;
		
		vertPtr[0] = cosTheta2 * _radius;
		vertPtr[1] = sinTheta2 * _radius;
		vertPtr[2] = -halfLength;
		vertPtr += 3;
		
		normPtr[0] = cosTheta2 * _length / normLen;
		normPtr[1] = sinTheta2 * _length / normLen;
		normPtr[2] = 
		_radius / normLen;
		normPtr += 3;
		
		*indexPtr++ = idx++;
		
		theta += delta;
	}
	
	// Cap(positive Z)
	_capIdx = idx;
	_capStart = indexPtr;
	
	vertPtr[0] = 0.f;
	vertPtr[1] = 0.f;
	vertPtr[2] = -halfLength;
	vertPtr += 3;
	
	normPtr[0] = 0.f;
	normPtr[1] = 0.f;
	normPtr[2] = 1.f;
	normPtr += 3;
	
	*indexPtr++ = idx++;
	
	theta = 0;
	for (i=0; i<_slices; i++)
	{
		const float cosTheta = (float) cos( theta );
		const float sinTheta = (float) sin( theta );
		
		vertPtr[0] = cosTheta * _radius;
		vertPtr[1] = sinTheta * _radius;
		vertPtr[2] = -halfLength;
		vertPtr += 3;
		
		normPtr[0] = 0.f;
		normPtr[1] = 0.f;
		normPtr[2] = 1.f;
		normPtr += 3;
		
		*indexPtr++ = idx++;
		
		theta += delta;
	}
	
	vertPtr[0] = _radius;
	vertPtr[1] = 0.f;
	vertPtr[2] = -halfLength;
	vertPtr += 3;
	
	normPtr[0] = 0.f;
	normPtr[1] = 0.f;
	normPtr[2] = 1.f;
	normPtr += 3;
	
	*indexPtr++ = idx++;
	_idxEnd = idx;
	
	return( _valid = true );
}
