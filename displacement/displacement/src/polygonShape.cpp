#include "polygonShape.h"

PolygonShape::PolygonShape():
_vertices( NULL ),
_normals( NULL ),
_indices( NULL ),
_texCoords( NULL ),
_valid( false )
{
}
PolygonShape::~PolygonShape() {
	if (_valid) {
		delete _texCoords;
		delete _vertices;
		delete _normals;
		delete _indices;
	}
}
	
void PolygonShape::draw() {
	if (!_valid) {
		return;
	}
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, _vertices );
	glTexCoordPointer(2, GL_FLOAT, 0, _texCoords);
	glNormalPointer( GL_FLOAT, 0, _normals );
	glDrawElements( GL_TRIANGLES, triangles.size() * 3, GL_UNSIGNED_SHORT, _indices );
	//glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	/*
	for (int i = 0; i < vertices.size(); i++) {
		ofDrawBitmapString(ofToString(i) + "---" + ofToString(vertices[i]->x)+" : "+ofToString(vertices[i]->y)+" : "+ofToString(vertices[i]->z), -600, i * 20-100);
	}
	*/
}

void PolygonShape::addVertex(PolyVertex* v) {
	vertices.push_back(v);
	triangleGroups.push_back(new PolyTriangleGroup);
}
void PolygonShape::addTriangle(PolyTriangle* t) {
	triangles.push_back(t);
	triangleGroups[t->indices[0]]->add(t);
	triangleGroups[t->indices[1]]->add(t);
	triangleGroups[t->indices[2]]->add(t);
}

bool PolygonShape::init() {
	if (!_valid) {
		_valid = true;
	} else {
		delete _vertices;
		delete _normals;
		delete _texCoords;
		delete _indices;
	}
	_vertices = new GLfloat[vertices.size() * 3 ];
	_texCoords = new GLfloat[vertices.size() * 2 ];
	_normals = new GLfloat[vertices.size() * 3 ];
	_indices = new GLushort[triangles.size() * 3];
	
	
	GLfloat* vertPtr = _vertices;
	GLfloat* texCoordPtr = _texCoords;
	GLfloat* normPtr = _normals;
	GLushort* indexPtr = _indices;
	
	for (int i = 0; i < vertices.size(); i ++) {
		vertPtr[0] = vertices[i]->x;
		vertPtr[1] = vertices[i]->y;
		vertPtr[2] = vertices[i]->z;
		texCoordPtr[0] = vertices[i]->s;
		texCoordPtr[1] = vertices[i]->t;
        //cout << texCoordPtr[0] << " / " << texCoordPtr[1] << "\n";
		vertPtr += 3;
		texCoordPtr += 2;
	}
	
	for (int i = 0; i < vertices.size(); i ++) {
		int count = 0;
		float x1,y1,z1, x2,y2,z2, x3,y3,z3,x4 = 0.f,y4 = 0.f,z4 = 0.f;
		for (int j = 0; j < triangleGroups[i]->triangles.size(); j ++) {
			PolyTriangle* t = triangleGroups[i]->triangles[j];
			
			x1 = vertices[t->indices[0]]->x - vertices[t->indices[1]]->x;
			y1 = vertices[t->indices[0]]->y - vertices[t->indices[1]]->y;
			z1 = vertices[t->indices[0]]->z - vertices[t->indices[1]]->z;
			x2 = vertices[t->indices[2]]->x - vertices[t->indices[0]]->x;
			y2 = vertices[t->indices[2]]->y - vertices[t->indices[0]]->y;
			z2 = vertices[t->indices[2]]->z - vertices[t->indices[0]]->z;
			x3 = y1 * z2 - z1 * y2;
			y3 = z1 * x2 - x1 * z2;
			z3 = x1 * y2 - y1 * x2;
			float len = sqrt(x3 * x3 + y3 * y3 + z3 * z3);
			
			
			x4 += x3 / len;
			y4 += y3 / len;
			z4 += z3 / len;
		}
		
		x4 /= triangleGroups[i]->triangles.size();
		y4 /= triangleGroups[i]->triangles.size();
		z4 /= triangleGroups[i]->triangles.size();
		float len = sqrt(x4 * x4 + y4 * y4 + z4 * z4);
		x4 /= len;
		y4 /= len;
		z4 /= len;
		
		normPtr[0] = x4;
		normPtr[1] = y4;
		normPtr[2] = z4;
		normPtr += 3;
	}
	
	for (int i = 0; i < triangles.size(); i ++) {
		indexPtr[0] = triangles[i]->indices[0];
		indexPtr[1] = triangles[i]->indices[1];
		indexPtr[2] = triangles[i]->indices[2];
		indexPtr += 3;
	}
}
