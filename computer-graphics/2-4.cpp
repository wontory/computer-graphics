#define GL_SILENCE_DEPRECATION                      // MacOS Deprecated 오류 미출력 코드
#include <GL/glut.h>

GLfloat lightPosition[] = { 3, 4, 2 };

void drawAxis() {
    glPushMatrix();
    glBegin(GL_LINES);
    GLfloat red[] = { 255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f }; // colour
    glMaterialfv(GL_FRONT, GL_AMBIENT, red);
    glVertex3f(0, 0, 0); glVertex3f(6.5, 0, 0);
    glPopMatrix();

    glPushMatrix();
    GLfloat green[] = { 0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f }; // colour
    glMaterialfv(GL_FRONT, GL_AMBIENT, green);
    glVertex3f(0, 0, 0); glVertex3f(0, 4, 0);
    glPopMatrix();

    glPushMatrix();
    GLfloat blue[] = { 0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f }; // colour
    glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
    glVertex3f(0, 0, 0); glVertex3f(0, 0, -8);
    glEnd();
    glPopMatrix();
}

void drawPlane() {
    GLfloat white[] = { 255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f }; // colour
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);

    glBegin(GL_LINES);
    for (GLfloat i = 0; i <= 6; i += 0.25) {
        glVertex3f(i, 0, -6);
        glVertex3f(i, 0, 0);
        glVertex3f(6, 0, -i);
        glVertex3f(0, 0, -i);
    }
    glEnd();
}

void drawObjects() {
    glPushMatrix();
    glTranslatef(4.0, 0.5, -1.3); // location
    GLfloat InePurple[] = { 138.0f / 255.0f, 43.0f / 255.0f, 226.0f / 255.0f }; // colour
    glMaterialfv(GL_FRONT, GL_AMBIENT, InePurple);
    glutSolidCube(0.75);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5, 0.5, -3.3); // location
    glRotatef(180.0, 0.0, 1.0, 0.0); // rotate
    GLfloat peridotGreen[] = { 155.0f / 255.0f, 228.0f / 255.0f, 102.0f / 255.0f }; // colour
    glMaterialfv(GL_FRONT, GL_AMBIENT, peridotGreen);
    glutSolidTeapot(0.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0, 0.0, -5.0); // location
    GLfloat orange[] = { 248.0f / 255.0f, 155.0f / 255.0f, 0.0f / 255.0f }; // colour
    glMaterialfv(GL_FRONT, GL_AMBIENT, orange);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.5, 1, 20, 20);
    glPopMatrix();
}

void init() {
    glClearColor(0.6, 0.6, 0.6, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, 4.0 / 3.0, 1.0, 15.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3, 3, 4.5, 3, -2, -20, 0, 1, 0);

    GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat yellow[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat cyan[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat direction[] = { 3.0, 4.0, 2.0, 1.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);

    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_POSITION, direction);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    drawObjects();
    drawAxis();
    drawPlane();

    glPopMatrix();

    glFlush();
}

void key_input(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        lightPosition[0] = 3;
        lightPosition[1] = 4;
        lightPosition[2] = -8;
        break;
    case GLUT_KEY_DOWN:
        lightPosition[0] = 3;
        lightPosition[1] = 4;
        lightPosition[2] = 2;
        break;
    case GLUT_KEY_LEFT:
        lightPosition[0] = -2;
        lightPosition[1] = 4;
        lightPosition[2] = -3;
        break;
    case GLUT_KEY_RIGHT:
        lightPosition[0] = 8;
        lightPosition[1] = 4;
        lightPosition[2] = -3;
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(120, 80);
    glutInitWindowSize(1280, 980);
    glutCreateWindow("Axis");
    glutDisplayFunc(display);
    glutSpecialFunc(key_input);
    init();
    glutMainLoop();
}
