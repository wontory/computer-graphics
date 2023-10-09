#define GL_SILENCE_DEPRECATION                      // MacOS Deprecated 오류 미출력 코드
#include <GL/glut.h>

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
    for (GLfloat i = 0; i <= 6; i += 0.25) {
        glVertex3f(i, 0, -6);
        glVertex3f(i, 0, 0);
        glVertex3f(6, 0, -i);
        glVertex3f(0, 0, -i);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawPlane();
    drawAxis();
    
    // Cube
    glPushMatrix();
    glTranslatef(4.0, -0.07, -1.3);
    glColor3f(138.0f / 255.0f, 43.0f / 255.0f, 226.0f / 255.0f);
    glutSolidCube(0.75);
    glPopMatrix();
    
    // Teapot
    glPushMatrix();
    glTranslatef(1.5, 0.0, -3.3);
    glRotatef(180.0, 0.0, 1.0, 0.0);
    glColor3f(155.0f / 255.0f, 228.0f / 255.0f, 102.0f / 255.0f);
    glutSolidTeapot(0.6);
    glPopMatrix();
    
    // Cone
    glPushMatrix();
    glTranslatef(3.0, 0.0, -5.0);
    glColor3f(248.0f / 255.0f, 155.0f / 255.0f, 0.0f / 255.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.5, 1, 20, 20);
    glPopMatrix();
    
    glFlush();
}

void init() {
    glClearColor(0.6, 0.6, 0.6, 1.0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 4.0 / 3.0, 1.0, 7.0);
    /**
     gluLookAt의 Eye 위치(3, 3, 4.5)를 기준으로 fovy, aspect, near, far.
     
     즉,
     z 범위: 3.5 ~ -2.5
     의 영역을 원근 투영
     
     Cube의 z 범위: -0.55 ~ -2.05
     */
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3, 3, 4.5, 3, -2, -20, 0, 1, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(120, 80);
    glutInitWindowSize(1280, 980);
    glutCreateWindow("Objects");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}
