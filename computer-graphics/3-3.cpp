#define GL_SILENCE_DEPRECATION          // MacOS Deprecated 오류 미출력 코드
#include <GL/glut.h>
#include <math.h>

GLfloat ctrlpoints[4][4][3] = {
    {{0.0, 0.2, 0.0}, {2.0, 1.5, 0.0}, {4.0, 0.1, 0.0}, {6.0, -0.2, 0.0}},
    {{0.0, 1.5, -2.0}, {2.0, 1.6, -2.0}, {4.0, 0.3, -2.0}, {6.0, 2.0, -2.0}},
    {{0.0, 1.6, -4.0}, {2.0, 1.8, -4.0}, {4.0, 0.3, -4.0}, {6.0, -1.0, -4.0}},
    {{0.0, 0.6, -6.0}, {2.0, 0.0, -6.0}, {4.0, 0.8, -6.0}, {6.0, 2.3, -6.0}}
};

void drawAxis() {
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(6.5, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 4, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, -8);
    glEnd();
}

void drawPlane() {
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_LINES);
    for (GLfloat i = 0; i <= 6; i += 2) {
        glVertex3f(i, 0, -6);
        glVertex3f(i, 0, 0);
        glVertex3f(6, 0, -i);
        glVertex3f(0, 0, -i);
    }
    glEnd();
}

void drawControlPoints() {
    glPointSize(7.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            glVertex3fv(&ctrlpoints[i][j][0]);
        }
    }
    glEnd();
}

void drawControlLines() {
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);

    for (int i = 0; i < 4; ++i) {
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < 4; ++j) {
            glVertex3fv(&ctrlpoints[i][j][0]);
        }
        glEnd();
    }

    for (int j = 0; j < 4; ++j) {
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < 4; ++i) {
            glVertex3fv(&ctrlpoints[i][j][0]);
        }
        glEnd();
    }
}

int binomialCoeff(int n, int k) {
    if (k == 0 || k == n)
        return 1;
    return binomialCoeff(n - 1, k - 1) + binomialCoeff(n - 1, k);
}

void drawBezierSurface() {
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    
    for (float u = 0.0f; u < 1.0f; u += 0.001f) {
        glBegin(GL_LINE_STRIP);
        
        for (float v = 0.0f; v < 1.0f; v += 0.001f) {
            float x = 0.0;
            float y = 0.0;
            float z = 0.0;
            
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    float basisU = binomialCoeff(3, j) * pow(1 - u, 3 - j) * pow(u, j);
                    float basisV = binomialCoeff(3, k) * pow(1 - v, 3 - k) * pow(v, k);
                    x += basisU * basisV * ctrlpoints[j][k][0];
                    y += basisU * basisV * ctrlpoints[j][k][1];
                    z += basisU * basisV * ctrlpoints[j][k][2];
                }
            }
            glVertex3f(x, y, z);
        }
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    drawAxis();
    drawPlane();
    drawControlPoints();
    drawControlLines();
    drawBezierSurface();

    glFlush();
}

void init() {
    glClearColor(0.6, 0.6, 0.6, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3, 3, 4.5, 3, -2, -20, 0, 1, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 4.0 / 3.0, 1, 100);

    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(120, 80);
    glutInitWindowSize(1280, 980);
    glutCreateWindow("Bezier Surface");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
