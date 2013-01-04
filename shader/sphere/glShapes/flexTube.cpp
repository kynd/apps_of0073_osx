
#include "flexTube.h"
#include "ofMain.h"

FlexTube::FlexTube(int _length, int _slices, float* coords, float* broadth, bool _drawCap1, bool _drawCap2):
length(_length),
slices(_slices),
drawCap1(_drawCap1),
drawCap2(_drawCap2)
{
	
	
	
	for (int i = 0; i < length; i ++) {
		for (int j = 0; j < slices; j ++) {
			vertices.push_back(new PolyVertex(0,0,0, 1.0 / length * i, 1.0 / slices * i));
			if (i > 0 && j > 0) {
				int p0 = (i - 1) * slices + j - 1;
				int p1 = (i - 1) * slices + j;
				int p2 = i * slices + j - 1;
				int p3 = i * slices + j;
				triangles.push_back(new PolyTriangle(p0, p2, p3));
				triangles.push_back(new PolyTriangle(p0, p3, p1));
				if (j == slices - 1) {
					int p4 = (i - 1) * slices;
					int p5 = i * slices;
					triangles.push_back(new PolyTriangle(p1, p3, p5));
					triangles.push_back(new PolyTriangle(p1, p5, p4));
				}
			}
		}
	}
	if (drawCap1) {
		capIndex1 = vertices.size();
		vertices.push_back(new PolyVertex(0,0,0,0,0));
		for (int i = 0; i < slices ; i ++) {
			vertices.push_back(new PolyVertex(0,0,0,0,1.0 / slices * i));
			
			if (i > 0) {
				triangles.push_back(new PolyTriangle(capIndex1 + i + 1, capIndex1, capIndex1 + i));
				if (i == slices - 1) {
					triangles.push_back(new PolyTriangle(capIndex1 + 1, capIndex1, capIndex1 + i + 1));
				}
			}
		}
	}
	
	if (drawCap2) {
		capIndex2 = vertices.size();
		vertices.push_back(new PolyVertex(0,0,0,1.0,0.0));
		for (int i = 0; i < slices ; i ++) {
			vertices.push_back(new PolyVertex(0,0,0,1.0,1.0 / slices * i));
			
			if (i > 0) {
				triangles.push_back(new PolyTriangle(capIndex2 + i + 1, capIndex2 + i, capIndex2));
				if (i == slices - 1) {
					triangles.push_back(new PolyTriangle(capIndex2 + 1, capIndex2 + i + 1, capIndex2));
				}
			}
		}
	}
	
	for (int i = 0; i < vertices.size(); i ++) {
		polygon.addVertex(vertices[i]);
	}
	for (int i = 0; i < triangles.size(); i ++) {
		polygon.addTriangle(triangles[i]);
	}
	for (int i = 0; i < vertices.size(); i ++) {
		vertices[i]->saveOriginal();
	}
	
	update(coords, broadth);
}
FlexTube::~FlexTube() {}

void FlexTube::update(float* coords, float* broadth) {
	Vector3D d(0,0,1);
	Vector3D* circle[slices];
	for (int i = 0; i < slices; i ++) {
		circle[i]->x = cos(TWO_PI / slices * i);
		circle[i]->y = sin(TWO_PI / slices * i);
	}
	
	for (int i = 0; i < length; i ++) {
		Vector3D c(coords[i * 3], coords[i * 3 + 1], coords[i * 3 + 2]);
			
		Vector3D nd;
		if (i == 0) {
			nd.x = coords[3] - coords[0];
			nd.y = coords[4] - coords[1];
			nd.z = coords[5] - coords[2];
		} else if (i == length - 1) {
			nd.x = coords[i * 3] - coords[(i - 1) * 3];
			nd.y = coords[i * 3 + 1] - coords[(i - 1) * 3 + 1];
			nd.z = coords[i * 3 + 2] - coords[(i - 1) * 3 + 2];
		} else {
			nd.x = coords[(i + 1) * 3] - coords[(i - 1) * 3];
			nd.y = coords[(i + 1) * 3 + 1] - coords[(i - 1) * 3 + 1];
			nd.z = coords[(i + 1) * 3 + 2] - coords[(i - 1) * 3 + 2];
		}

		d.normalize();
		nd.normalize();
		
		if (abs(d.z) > abs(d.x) && abs(d.z) > abs(d.y)) {
			float xr, yr, xr0, yr0, xr1, yr1;
			d.getAngleXY(xr0, yr0);
			nd.getAngleXY(xr1, yr1);
			xr = xr1 - xr0;
			yr = yr1 - yr0;
			for (int j = 0; j <= slices; j ++) {
				circle[j]->rotateX(xr);
				circle[j]->rotateY(yr);
			}
		} else {
			float yr, zr, yr0, zr0, yr1, zr1;
			d.getAngleYZ(yr0, zr0);
			nd.getAngleYZ(yr1, zr1);
			yr = yr1 - yr0;
			zr = zr1 - zr0;
			for (int j = 0; j < slices; j ++) {
				circle[j]->rotateY(yr);
				circle[j]->rotateZ(zr);
			}
		}

		for (int j = 0; j < slices; j ++) {
			vertices[i * slices + j]->x = c.x + circle[j]->x * broadth[i];
			vertices[i * slices + j]->y = c.y + circle[j]->y * broadth[i];
			vertices[i * slices + j]->z = c.z + circle[j]->z * broadth[i];
		}
		
		// cap1
		
		//if (drawCap1 && i == 0) {
		if (i == 0) {	
			vertices[capIndex1]->x = c.x;
			vertices[capIndex1]->y = c.y;
			vertices[capIndex1]->z = c.z;
			for (int j = 0; j < slices ; j ++) {
				vertices[capIndex1 + j + 1]->x = c.x + circle[j]->x * broadth[i];
				vertices[capIndex1 + j + 1]->y = c.y + circle[j]->y * broadth[i];
				vertices[capIndex1 + j + 1]->z = c.z + circle[j]->z * broadth[i];
			}
		}
		
		if (i == length - 1) {	
			vertices[capIndex2]->x = c.x;
			vertices[capIndex2]->y = c.y;
			vertices[capIndex2]->z = c.z;
			for (int j = 0; j < slices ; j ++) {
				vertices[capIndex2 + j + 1]->x = c.x + circle[j]->x * broadth[i];
				vertices[capIndex2 + j + 1]->y = c.y + circle[j]->y * broadth[i];
				vertices[capIndex2 + j + 1]->z = c.z + circle[j]->z * broadth[i];
			}
		}
		d.x = nd.x;
		d.y = nd.y;
		d.z = nd.z;
	}
	polygon.init();
}



void FlexTube::draw() {	
	polygon.draw();
}