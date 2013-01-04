#ifndef __POLYGON_SHAPE__
#define __POLYGON_SHAPE__

#include "ofMain.h"
#include "Poly_triangle.h"
#include "Poly_vertex.h"
#include "Poly_triangleGroup.h"
#include "shape.h"

class PolygonShape : public Shape {
public:
    PolygonShape();
    ~PolygonShape();
	
    virtual void draw();
	
	vector<PolyTriangle*> triangles;
	vector<PolyVertex*> vertices;
	vector<PolyTriangleGroup*> triangleGroups;
	void addVertex(PolyVertex*);
	void addTriangle(PolyTriangle*);
    bool init();
private:
    GLfloat* _vertices;
    GLfloat* _normals;
    GLfloat* _texCoords;
    GLushort* _indices;
    bool _valid;
};


#endif