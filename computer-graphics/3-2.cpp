#define GL_SILENCE_DEPRECATION          // MacOS Deprecated 오류 미출력 코드
#include <GL/glut.h>
#include <stdio.h>

// 4개의 컨트롤 포인트를 정의합니다.
float P0[2] = { -5.0f, -7.0f };
float P1[2] = { -3.0f, 2.0f };
float P2[2] = { 8.0f, -4.0f };
float P3[2] = { 5.0f, 7.0f };
//float P0[2] = { -3.0f, -3.0f };
//float P1[2] = { -7.0f, 4.0f };
//float P2[2] = { 8.0f, 7.0f };
//float P3[2] = { 5.0f, -3.0f };

void drawAxis() {
    glBegin(GL_LINES);                                              // 선 그리기 시작
    glColor3f(1, 0, 0); glVertex2f(-10, 0); glVertex2f(10, 0);      // x축 그리기
    glColor3f(0, 0, 1); glVertex2f(0, -10); glVertex2f(0, 10);      // y축 그리기
    glEnd();                                                        // 선 그리기 종료
}

void drawGrid() {
    glBegin(GL_LINES);                                  // 선 그리기 시작
    glColor3f(0.4, 0.4, 0.4);                           // 회색으로 설정
    for (int i = -10; i <= 10; i++) {                   // -10부터 10까지 반복
        if (i != 0) {                                   // x축, y축을 제외하고 (drawAxis에서 그리므로)
            glVertex2f(-10, i); glVertex2f(10, i);      // 수평선 그리기
            glVertex2f(i, -10); glVertex2f(i, 10);      // 수직선 그리기
        }
    }
    glEnd();                                            // 선 그리기 종료
}

void drawPoints() {
    glPointSize(5.0f);                      // 점의 크기를 5로 설정합니다.

    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);      // 색상을 녹색으로 설정합니다.
    glBegin(GL_POINTS);                     // 점 그리기 시작
    glVertex2f(P0[0], P0[1]);               // P0 좌표에 점을 그립니다.
    glVertex2f(P1[0], P1[1]);               // P1 좌표에 점을 그립니다.
    glVertex2f(P2[0], P2[1]);               // P2 좌표에 점을 그립니다.
    glVertex2f(P3[0], P3[1]);               // P3 좌표에 점을 그립니다.
    glEnd();                                // 점 그리기 종료
}

void drawText(float x, float y, const char* string) {
    glRasterPos2f(x, y);                                        // 출력 위치를 설정합니다.
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);      // 문자열을 한 글자씩 출력합니다.
    }
}


void drawControlLines() {
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);      // 검은색으로 설정합니다.
    glBegin(GL_LINES);                      // 선 그리기 시작
    glVertex2f(P0[0], P0[1]);               // P0에서 시작하는 선을 그립니다.
    glVertex2f(P1[0], P1[1]);               // P1에서 끝나는 선을 그립니다.
    glVertex2f(P1[0], P1[1]);               // P1에서 시작하는 선을 그립니다.
    glVertex2f(P2[0], P2[1]);               // P2에서 끝나는 선을 그립니다.
    glVertex2f(P2[0], P2[1]);               // P2에서 시작하는 선을 그립니다.
    glVertex2f(P3[0], P3[1]);               // P3에서 끝나는 선을 그립니다.
    glEnd();                                // 선 그리기 종료
}

void drawBezierCurve() {
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);                                      // 곡선의 색상을 녹색으로 설정합니다.
    glBegin(GL_LINE_STRIP);                                                 // 선 그리기 시작
    for (float t = 0.0f; t <= 1.0f; t += 0.01f) {                           // t값을 0부터 1까지 0.01씩 증가시키며 반복합니다.
        float x = (1 - t) * (1 - t) * (1 - t) * P0[0] + 3 * (1 - t) * (1 - t) * t * P1[0] + 
                   3 * (1 - t) * t * t * P2[0] + t * t * t * P3[0];         // x좌표를 계산합니다. (Assignment03.pdf 20페이지의 수식 참고)
        float y = (1 - t) * (1 - t) * (1 - t) * P0[1] + 3 * (1 - t) * (1 - t) * t * P1[1] + 
                   3 * (1 - t) * t * t * P2[1] + t * t * t * P3[1];         // y좌표를 계산합니다. (Assignment03.pdf 20페이지의 수식 참고)
        glVertex2f(x, y);                                                   // 계산된 좌표를 이용하여 점을 그립니다.
    }
    glEnd();                                                                // 선 그리기 종료
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);   // 화면을 지웁니다.
    drawAxis();                     // 좌표축을 그립니다.
    drawGrid();                     // 격자를 그립니다.

    drawPoints();                   // 컨트롤 포인트를 그립니다.

    // 각 point마다 라벨 생성 및 출력
    char label[20];
    sprintf(label, "P0(%.1f, %.1f)", P0[0], P0[1]);
    drawText(P0[0] + 0.2, P0[1], label);
    sprintf(label, "P1(%.1f, %.1f)", P1[0], P1[1]);
    drawText(P1[0] + 0.2, P1[1], label);
    sprintf(label, "P2(%.1f, %.1f)", P2[0], P2[1]);
    drawText(P2[0] + 0.2, P2[1], label);
    sprintf(label, "P3(%.1f, %.1f)", P3[0], P3[1]);
    drawText(P3[0] + 0.2, P3[1], label);

    drawControlLines();             // 컨트롤 라인을 그립니다.

    drawBezierCurve();              // 베지어 곡선을 그립니다.

    glFlush();                      // 그리기 명령을 수행합니다.
}

void init() {
    glClearColor(0.6, 0.6, 0.6, 1.0);       // 배경색을 회색으로 설정합니다.
    glMatrixMode(GL_PROJECTION);            // 투영 행렬 모드를 설정합니다.
    glLoadIdentity();                       // 현재 행렬을 단위 행렬로 초기화합니다.
    gluOrtho2D(-10, 10, -10, 10);           // 2D 좌표계를 설정합니다.
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                              // GLUT 라이브러리를 초기화합니다.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);        // 디스플레이 모드를 설정합니다.
    glutInitWindowPosition(100, 100);                   // 윈도우의 위치를 설정합니다.
    glutInitWindowSize(900, 900);                       // 윈도우의 크기를 설정합니다.
    glutCreateWindow("2D Grid");                        // 윈도우를 생성합니다.
    init();                                             // 초기화 함수를 호출합니다.
    glutDisplayFunc(display);                           // 디스플레이 콜백 함수를 등록합니다.
    glutMainLoop();                                     // 이벤트 루프를 시작합니다.
    return 0;
}




