#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_LINES);
    
    // Axis 그리기
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(6, 0, 0);
    
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 4, 0);
    
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, -10);
    
    // Matrix 그리기
    float gap = 0.5;
    glColor3f(1, 1, 1);
    for (float x = gap; x <= 6.0; x += gap) {
        glVertex3f(x, 0.0, 0.0);
        glVertex3f(x, 0.0, -6.0);
    }
    
    for (float z = gap; z <= 6.0; z += gap) {
        glVertex3f(-0.0, 0.0, -z);
        glVertex3f(6.0, 0.0, -z);
    }
    
    glEnd();
    
    glFlush();
}

void init() {
    glClearColor(0.5, 0.5, 0.5, 1.0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 5.0 / 3.0, 1, 100);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3, 3.3, 4, 3, 1, -4, 0, 1, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(120, 80);
    glutInitWindowSize(800, 620);
    glutCreateWindow("Matrix");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}