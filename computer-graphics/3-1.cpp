#define GL_SILENCE_DEPRECATION          // MacOS Deprecated 오류 미출력 코드
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <GL/glut.h>

struct Vertex {
    float x, y, z;
};

enum FaceType {
    TRIANGLE,
    SQUARE,
    UNKNOWN
};

struct Face {
    std::vector<int> vertices;
    FaceType type;
};

std::vector<Vertex> vertices;
std::vector<Face> faces;

bool loadOBJ(const char* path, std::vector<Vertex>& out_vertices, std::vector<Face>& out_faces) {
    std::ifstream inFile(path);
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file: " << path << std::endl;
        return false;
    }

    std::string line;
    while (getline(inFile, line)) {
        if (line.substr(0, 2) == "v ") {
            std::istringstream s(line.substr(2));
            Vertex v;
            s >> v.x;
            s >> v.y;
            s >> v.z;
            out_vertices.push_back(v);
        }
        else if (line.substr(0, 2) == "f ") {
            std::istringstream s(line.substr(2));
            Face f;
            int vIndex;
            while (s >> vIndex) {
                f.vertices.push_back(vIndex - 1);
            }
            if (f.vertices.size() == 3) {
                f.type = TRIANGLE;
            }
            else if (f.vertices.size() == 4) {
                f.type = SQUARE;
            }
            else {
                f.type = UNKNOWN;
                std::cerr << "Error: Only triangle and square faces are supported." << std::endl;
            }
            out_faces.push_back(f);
        }
    }

    inFile.close();
    return true;
}

Vertex crossProduct(const Vertex& a, const Vertex& b) {
    Vertex result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

void normalize(Vertex& v) {
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (length != 0.0f) {
        v.x /= length;
        v.y /= length;
        v.z /= length;
    }
}

void init() {
    int argc = 1;
    char* argv[1] = { (char*)"Something" };
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("OBJ Loader");
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightpos[] = { 0.0, 0.0, 10.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);


    glColor3f(0.8, 0.2, 1.0);
    GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess[] = { 100.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void resize(int width, int height) {
    if (height == 0) height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0, -3, 5, 0, 0, 0, 0, 0, 1); // gourd
    //gluLookAt(3, 3, 3, 0, 0, 0, 0, 0, 1); // icosahedron
    //gluLookAt(8, 15, 8, 0, 4, 0, 0, 1, 0); // lamp
    //gluLookAt(-10, 10, 15, 0, 0, 0, 0, 0, 1); // shuttle
    //gluLookAt(3, 3, 3, 0, 0, 0, 0, 0, 1); // violin_case

    for (const auto& face : faces) {
        if (face.type == TRIANGLE) {
            glBegin(GL_TRIANGLES);
            if (face.vertices.size() >= 3) {
                Vertex& v1 = vertices[face.vertices[0]];
                Vertex& v2 = vertices[face.vertices[1]];
                Vertex& v3 = vertices[face.vertices[2]];

                Vertex vector1 = { v2.x - v1.x, v2.y - v1.y, v2.z - v1.z };
                Vertex vector2 = { v3.x - v1.x, v3.y - v1.y, v3.z - v1.z };
                Vertex normal = crossProduct(vector1, vector2);
                normalize(normal);
                glNormal3f(normal.x, normal.y, normal.z);
            }
            for (int vertexIndex : face.vertices) {
                glVertex3f(vertices[vertexIndex].x, vertices[vertexIndex].y, vertices[vertexIndex].z);
            }
            glEnd();
        }
        else if (face.type == SQUARE) {
            glBegin(GL_QUADS);
            if (face.vertices.size() >= 4) {
                Vertex& v1 = vertices[face.vertices[0]];
                Vertex& v2 = vertices[face.vertices[1]];
                Vertex& v3 = vertices[face.vertices[2]];

                Vertex vector1 = { v2.x - v1.x, v2.y - v1.y, v2.z - v1.z };
                Vertex vector2 = { v3.x - v1.x, v3.y - v1.y, v3.z - v1.z };
                Vertex normal = crossProduct(vector1, vector2);
                normalize(normal);
                glNormal3f(normal.x, normal.y, normal.z);
            }
            for (int vertexIndex : face.vertices) {
                glVertex3f(vertices[vertexIndex].x, vertices[vertexIndex].y, vertices[vertexIndex].z);
            }
            glEnd();
        }
    }

    glutSwapBuffers();
}

int main() {
    std::string objFilePath = "./gourd.obj";
    //std::string objFilePath = "./icosahedron.obj";
    //std::string objFilePath = "./lamp.obj";
    //std::string objFilePath = "./shuttle.obj";
    //std::string objFilePath = "./violin_case.obj";

    if (!loadOBJ(objFilePath.c_str(), vertices, faces)) {
        return 1;
    }

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMainLoop();

    return 0;
}
