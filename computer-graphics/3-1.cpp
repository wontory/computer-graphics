#define GL_SILENCE_DEPRECATION          // MacOS Deprecated 오류 미출력 코드
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <GL/glut.h>

struct Vertex {         // 정점 좌표를 저장하는 구조체
    float x, y, z;      // x, y, z
};

enum FaceType {     // 면 유형을 저장하는 열거형
    TRIANGLE,       // 삼각형
    SQUARE,         // 사각형
    UNKNOWN         // 알 수 없는 형태
};

struct Face {                       // 면 정보를 저장하는 구조체
    std::vector<int> vertices;      // 정점의 index를 저장하는 벡터
    FaceType type;                  // 면의 형태
};

std::vector<Vertex> vertices;       // 모델의 정점들을 저장하는 벡터
std::vector<Face> faces;            // 모델의 면들을 저장하는 벡터

bool loadOBJ(const char* path, std::vector<Vertex>& out_vertices, std::vector<Face>& out_faces) {       // Wavefront OBJ 파일을 로드하는 함수
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

Vertex crossProduct(const Vertex& a, const Vertex& b) {         // 두 벡터의 외적을 계산하는 함수
    Vertex result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

void normalize(Vertex& v) {             // 벡터를 정규화하는 함수
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

    for (const auto& face : faces) {        // faces의 element(면)를 순회하면서 모든 면을 그린다.
        if (face.type == TRIANGLE) {        // 현재 면이 삼각형인 경우,
            glBegin(GL_TRIANGLES);          // 삼각형 그리기 시작
            if (face.vertices.size() >= 3) {                    // 면의 정점이 3개 이상이면,
                Vertex& v1 = vertices[face.vertices[0]];        // 면의 첫 번째 정점
                Vertex& v2 = vertices[face.vertices[1]];        // 면의 두 번째 정점
                Vertex& v3 = vertices[face.vertices[2]];        // 면의 세 번째 정점

                Vertex vector1 = { v2.x - v1.x, v2.y - v1.y, v2.z - v1.z };     // v1에서 v2으로 향하는 벡터를 계산
                Vertex vector2 = { v3.x - v1.x, v3.y - v1.y, v3.z - v1.z };     // v1에서 v3으로 향하는 벡터를 계산
                Vertex normal = crossProduct(vector1, vector2);                 // 두 벡터를 외적합니다. (법선 벡터 구하기)
                normalize(normal);                                              // 법선 벡터를 정규화 (크기를 1로 변경)
                glNormal3f(normal.x, normal.y, normal.z);                       // OpenGL에 정규화된 법선 벡터를 설정
            }
            for (int vertexIndex : face.vertices) {
                glVertex3f(vertices[vertexIndex].x, vertices[vertexIndex].y, vertices[vertexIndex].z);      // 삼각형의 세 점 그리기 (for loop)
            }
            glEnd();        // 삼각형 그리기 종료
        }
        else if (face.type == SQUARE) {     // 현재 면이 사각형인 경우
            glBegin(GL_QUADS);              // 사각형 그리기 시작
            if (face.vertices.size() >= 4) {                    // 면의 정점이 4개 이상이면,
                Vertex& v1 = vertices[face.vertices[0]];        // 면의 첫 번째 정점
                Vertex& v2 = vertices[face.vertices[1]];        // 면의 두 번째 정점
                Vertex& v3 = vertices[face.vertices[2]];        // 면의 세 번째 정점

                Vertex vector1 = { v2.x - v1.x, v2.y - v1.y, v2.z - v1.z };     // v1에서 v2으로 향하는 벡터를 계산
                Vertex vector2 = { v3.x - v1.x, v3.y - v1.y, v3.z - v1.z };     // v1에서 v3으로 향하는 벡터를 계산
                Vertex normal = crossProduct(vector1, vector2);                 // 두 벡터를 외적합니다. (법선 벡터 구하기)
                normalize(normal);                                              // 법선 벡터를 정규화 (크기를 1로 변경)
                glNormal3f(normal.x, normal.y, normal.z);                       // OpenGL에 정규화된 법선 벡터를 설정
            }
            for (int vertexIndex : face.vertices) {
                glVertex3f(vertices[vertexIndex].x, vertices[vertexIndex].y, vertices[vertexIndex].z);      // 사각형의 네 점 그리기 (for loop)
            }
            glEnd();        // 사각형 그리기 종료
        }
    }
    
    /**
    법선벡터를 설정하는 이유(glNormal3f)
    ================================================================================
    삼각형이나 사각형의 표면 법선 벡터를 OpenGL에 제공함으로써, 광원이 어떻게 표면에 반사되는지를 결정합니다.
    법선 벡터가 없으면 광원 계산이 제대로 이루어지지 않아 조명이 이상하게 나타날 수 있습니다.
     */

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
