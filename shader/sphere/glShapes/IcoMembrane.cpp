#include "IcoMembrane.h"


IcoMembrane::IcoMembrane(int _length, float* coords, float _max, float _min, int _maxPolygon)
{
    maxPolygon =  _maxPolygon;
    minThreshold = _min;
    maxThreshold = _max;
    update(_length, coords);
}

IcoMembrane::~IcoMembrane() {
    delete _vertices;
    delete _normals;
    delete _indices;
}

void IcoMembrane::draw() {
	glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, _vertices );
    glNormalPointer( GL_FLOAT, 0, _normals );
    glDrawElements( GL_TRIANGLES, numTriangle * 3, GL_UNSIGNED_SHORT, _indices );
}


void IcoMembrane::update(int _length, float* coords) {
    
    
    
    
    vector<PolyVertex> vertices;
    multimap<float, PolyTriangle> triangles;
    map<int, int> lineChache;
    
    for (int i = 0; i < _length; i ++) {
        vertices.push_back(PolyVertex(
                                      coords[i * 3],
                                      coords[i * 3 + 1],
                                      coords[i * 3 + 2]
                                      ));
    }
    
    for (int i = 0; i < vertices.size() - 2; i ++) {
        for (int j = i + 1; j < vertices.size() - 1; j ++) {
            
            float dist = distance(vertices[i], vertices[j]);
            float mindist = distance(vertices[i],vertices[j]);
            if (dist >= maxThreshold || mindist <= minThreshold || triangles.size() > maxPolygon) {
                continue;
            }
            for (int k = j + 1; k < vertices.size(); k ++) {
                dist = max(distance(vertices[j], vertices[k]), distance(vertices[k], vertices[i]));
                mindist = min(distance(vertices[j], vertices[k]), distance(vertices[k], vertices[i]));
                if (dist >= maxThreshold || mindist <= minThreshold || triangles.size() > maxPolygon) {
                    continue;
                }
                PolyTriangle t = PolyTriangle(i, j, k);
                triangles.insert(multimap<float, PolyTriangle>::value_type(dist, t));
            }
        }
    }
    
    _vertices = new GLfloat[triangles.size() * 3 * 3];
    _normals = new GLfloat[triangles.size() * 3 * 3];
    _indices = new GLushort[triangles.size() * 3];
    
    multimap<float, PolyTriangle>::iterator it = triangles.begin();
    int cnt = 0;
    while(it != triangles.end()) {
        PolyTriangle t = (*it).second;
        int a = t.indices[0];
        int b = t.indices[1];
        int c = t.indices[2];
        _vertices[cnt * 9] = vertices[a].x;
        _vertices[cnt * 9 + 1] = vertices[a].y;
        _vertices[cnt * 9 + 2] = vertices[a].z;
        _vertices[cnt * 9 + 3] = vertices[b].x;
        _vertices[cnt * 9 + 4] = vertices[b].y;
        _vertices[cnt * 9 + 5] = vertices[b].z;
        _vertices[cnt * 9 + 6] = vertices[c].x;
        _vertices[cnt * 9 + 7] = vertices[c].y;
        _vertices[cnt * 9 + 8] = vertices[c].z;
        
        
        float x1,y1,z1, x2,y2,z2, x3,y3,z3;
        x1 = vertices[a].x - vertices[b].x;
        y1 = vertices[a].y - vertices[b].y;
        z1 = vertices[a].z - vertices[b].z;
        x2 = vertices[c].x - vertices[a].x;
        y2 = vertices[c].y - vertices[a].y;
        z2 = vertices[c].z - vertices[a].z;
        x3 = y1 * z2 - z1 * y2;
        y3 = z1 * x2 - x1 * z2;
        z3 = x1 * y2 - y1 * x2;
        float len = sqrt(x3 * x3 + y3 * y3 + z3 * z3);
        x3 /= len;
        y3 /= len;
        z3 /= len;
        
        _normals[cnt * 9] = x3;
        _normals[cnt * 9 + 1] = y3;
        _normals[cnt * 9 + 2] = z3;
        _normals[cnt * 9 + 3] = x3;
        _normals[cnt * 9 + 4] = y3;
        _normals[cnt * 9 + 5] = z3;
        _normals[cnt * 9 + 6] = x3;
        _normals[cnt * 9 + 7] = y3;
        _normals[cnt * 9 + 8] = z3;
        
        _indices[cnt * 3] = cnt * 3;
        _indices[cnt * 3 + 1] = cnt * 3 + 1;
        _indices[cnt * 3 + 2] = cnt * 3 + 2;
        cnt ++;
        it ++;
        if (cnt > pow(2.0, 12)) {
            break;
        }
    }
    
    numTriangle = cnt - 1;
}

float IcoMembrane::distance(PolyVertex v1, PolyVertex v2) {
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    float dz = v1.z - v2.z;
    
    return sqrt(dx * dx + dy * dy + dz * dz);
}
