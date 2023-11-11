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

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    drawAxis();
    drawPlane();
    drawControlPoints();
    drawControlLines();

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
