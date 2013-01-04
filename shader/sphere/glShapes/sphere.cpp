#include "sphere.h"


Sphere::Sphere( float radius, int vSlices, int hSlices )
: _radius( radius ),
_vSlices( vSlices ),
_hSlices( hSlices ),
_vertices( NULL ),
_normals( NULL ),
_indices( NULL ),
_valid( false ),
_numSideVerts( 0 ),
_numCapVerts( 0 )
{
	init();
}

Sphere::~Sphere()
{
	if ( _valid )
	{
		if (_vertices)
			delete[] _vertices;
		if (_normals)
			delete[] _normals;
		if (_indices)
			delete[] _indices;
		if (_texCoords)
			delete[] _texCoords;
		_vertices = _normals = NULL;
		_indices = NULL;
		_valid = false;
	}
}


void Sphere::draw(){
	if (!_valid)
	{
		if (!init())
			return;
	}
	
	glPushClientAttrib( GL_CLIENT_VERTEX_ARRAY_BIT );
	
	// enable and allocate data
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, _vertices );
	glNormalPointer( GL_FLOAT, 0, _normals );
	glTexCoordPointer(2, GL_FLOAT, 0, _texCoords);
	
    // draw
	glDrawElements( GL_TRIANGLE_STRIP, _numSideVerts, GL_UNSIGNED_SHORT, _indices );
	glDrawElements( GL_TRIANGLE_FAN, _numCapVerts, GL_UNSIGNED_SHORT, _cap1Start );
	glDrawElements( GL_TRIANGLE_FAN, _numCapVerts, GL_UNSIGNED_SHORT, _cap2Start );
	
	glPopClientAttrib();
}

bool Sphere::init() {
	_numSideVerts = (_vSlices + 1) * (_hSlices - 2) * 2;
	_numCapVerts = _vSlices + 2;
	
	const int totalVerts = _numSideVerts + (_numCapVerts * 2);
	
	_vertices = new GLfloat[ ( _numSideVerts + 2) * 3 ];
	_normals = new GLfloat[ ( _numSideVerts + 2) * 3 ];
	_texCoords = new GLfloat[ ( _numSideVerts + 2) * 2 ];
	_indices = new GLushort[ totalVerts ];
	
	const double hDelta = PI * 2 / _hSlices;
	const double vDelta = PI * 2 / _vSlices;
	
	GLfloat* vertPtr = _vertices;
	GLfloat* normPtr = _normals;
	GLfloat* texCoordPtr = _texCoords;
	GLushort* indexPtr = _indices;
	int idx = 0;
	
	//top
	
	vertPtr[0] = 0.f;
	vertPtr[1] = 0.f;
	vertPtr[2] = - _radius;
	vertPtr += 3;
	
	normPtr[0] = 0.f;
	normPtr[1] = 0.f;
	normPtr[2] = -1.f;
	normPtr += 3;
    
    texCoordPtr[0] = 0.5;
    texCoordPtr[1] = 0.0;
    texCoordPtr += 2;
	
	idx ++;
	
	// body
	int i , j;
	for (i=1; i<_hSlices; i++) {
		double vTheta2 = PI / _hSlices * (i) - PI / 2;
		double cosVTheta2 = cos(vTheta2);
		double sinVTheta2 = sin(vTheta2);
		for (j=0; j<_vSlices; j++) {
			
			
			const float cosTheta = (float) cos(PI * 2 / _vSlices * j);
			const float sinTheta = (float) sin(PI * 2 / _vSlices * j);
			
			vertPtr[0] = cosTheta * cosVTheta2 * _radius;
			vertPtr[1] = sinTheta * cosVTheta2 * _radius;
			vertPtr[2] = sinVTheta2 * _radius;
			vertPtr += 3;
			
			normPtr[0] = cosTheta * cosVTheta2 ;
			normPtr[1] = sinTheta * cosVTheta2 ;
			normPtr[2] = sinVTheta2;
            
            
			texCoordPtr[0] = 1.0 / (_vSlices) * j;
			texCoordPtr[1] = 1.0 / (_hSlices) * (i + 1) ;
			texCoordPtr += 2;
		}
	}
	
	for (i=1; i<_hSlices - 1; i++) {
		int sIdx = idx;
		for (j=0; j<_vSlices; j++) {
			*indexPtr++ = idx;
			*indexPtr++ = idx + _vSlices;
			idx ++;
		}
		*indexPtr++ = sIdx;
		*indexPtr++ = sIdx + _vSlices;
	}	
	idx += _vSlices;
	
	
	//bottom
	
	vertPtr[0] = 0.f;
	vertPtr[1] = 0.f;
	vertPtr[2] = _radius;
	vertPtr += 3;
	
	normPtr[0] = 0.f;
	normPtr[1] = 0.f;
	normPtr[2] = 1.f;
	normPtr += 3;
    
    texCoordPtr[0] = 0.5;
    texCoordPtr[1] = 1.0;
    texCoordPtr += 2;
	
	//Cap 1 (negative Z)
	_cap1Start = indexPtr;
	*indexPtr++ = 0;
	for (i=0; i<_vSlices; i++) {
		*indexPtr++ = i + 1;
	}
	*indexPtr++ = 1;
	
	//Cap 2 (positive Z)
	
	_cap2Start = indexPtr;
	*indexPtr++ = idx;
	for (i=0; i<_vSlices; i++) {
		*indexPtr++ = idx - i - 1;
	}
	
	*indexPtr++ = idx - 1;
	
    
    for (int i = 0 ; i < ( _numSideVerts + 2) * 2; i ++) {
        cout << _texCoords[i] << "/";
    }
    
	return( _valid = true );
}
