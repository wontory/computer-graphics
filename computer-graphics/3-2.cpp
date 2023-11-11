#define GL_SILENCE_DEPRECATION          // MacOS Deprecated 오류 미출력 코드
#include <GL/glut.h>
#include <stdio.h>

float P0[2] = { -5.0f, -7.0f };
float P1[2] = { -3.0f, 2.0f };
float P2[2] = { 8.0f, -4.0f };
float P3[2] = { 5.0f, 7.0f };
//float P0[2] = { -3.0f, -3.0f };
//float P1[2] = { -7.0f, 4.0f };
//float P2[2] = { 8.0f, 7.0f };
//float P3[2] = { 5.0f, -3.0f };

void drawAxis() {
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex2f(-10, 0); glVertex2f(10, 0);
    glColor3f(0, 0, 1); glVertex2f(0, -10); glVertex2f(0, 10);
    glEnd();
}

void drawGrid() {
    glBegin(GL_LINES);
    glColor3f(0.4, 0.4, 0.4);
    for (int i = -10; i <= 10; i++) {
        if (i != 0) {
            glVertex2f(-10, i); glVertex2f(10, i);
            glVertex2f(i, -10); glVertex2f(i, 10);
        }
    }
    glEnd();
}

void drawPoints() {
    glPointSize(5.0f);

    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glBegin(GL_POINTS);
    glVertex2f(P0[0], P0[1]);
    glVertex2f(P1[0], P1[1]);
    glVertex2f(P2[0], P2[1]);
    glVertex2f(P3[0], P3[1]);
    glEnd();
}

void drawText(float x, float y, const char* string) {
    glRasterPos2f(x, y);
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}

void drawControlLines() {
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(P0[0], P0[1]);
    glVertex2f(P1[0], P1[1]);
    glVertex2f(P1[0], P1[1]);
    glVertex2f(P2[0], P2[1]);
    glVertex2f(P2[0], P2[1]);
    glVertex2f(P3[0], P3[1]);
    glEnd();
}

void drawBezierCurve() {
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
    for (float t = 0.0f; t <= 1.0f; t += 0.01f) {
        float x = (1 - t) * (1 - t) * (1 - t) * P0[0] + 3 * (1 - t) * (1 - t) * t * P1[0] + 3 * (1 - t) * t * t * P2[0] + t * t * t * P3[0];
        float y = (1 - t) * (1 - t) * (1 - t) * P0[1] + 3 * (1 - t) * (1 - t) * t * P1[1] + 3 * (1 - t) * t * t * P2[1] + t * t * t * P3[1];
        glVertex2f(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxis();
    drawGrid();

    drawPoints();

    char label[20];
    sprintf(label, "P0(%.1f, %.1f)", P0[0], P0[1]);
    drawText(P0[0] + 0.2, P0[1], label);
    sprintf(label, "P1(%.1f, %.1f)", P1[0], P1[1]);
    drawText(P1[0] + 0.2, P1[1], label);
    sprintf(label, "P2(%.1f, %.1f)", P2[0], P2[1]);
    drawText(P2[0] + 0.2, P2[1], label);
    sprintf(label, "P3(%.1f, %.1f)", P3[0], P3[1]);
    drawText(P3[0] + 0.2, P3[1], label);

    drawControlLines();

    drawBezierCurve();

    glFlush();
}

void init() {
    glClearColor(0.6, 0.6, 0.6, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(900, 900);
    glutCreateWindow("2D Grid");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
