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
    glBegin(GL_LINES);                                                  // 선 그리기 시작
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(6.5, 0, 0);     // x축 그리기
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 4, 0);       // y축 그리기
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, -8);      // z축 그리기
    glEnd();                                                            // 선 그리기 종료
}

void drawPlane() {
    glColor3f(1.0, 1.0, 1.0);                   // Matrix의 색상을 흰색으로 설정

    glBegin(GL_LINES);                          // 선 그리기 시작
    for (GLfloat i = 0; i <= 6; i += 2) {       // 0부터 6까지 2씩 증가하면서 반복
        glVertex3f(i, 0, -6);                   // (i, 0, -6) 좌표로 이동하여 선 그리기 시작
        glVertex3f(i, 0, 0);                    // (i, 0, 0) 좌표로 이동하여 선 그리기 종료
        glVertex3f(6, 0, -i);                   // (6, 0, -i) 좌표로 이동하여 선 그리기 시작
        glVertex3f(0, 0, -i);                   // (0, 0, -i) 좌표로 이동하여 선 그리기 종료
    }
    glEnd();                                    // 선 그리기 종료
}

void drawControlPoints() {
    glPointSize(7.0);                               // 점의 크기 설정
    glColor3f(1.0, 0.0, 0.0);                       // 빨간색으로 설정
    glBegin(GL_POINTS);                             // 점 그리기 시작
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            glVertex3fv(&ctrlpoints[i][j][0]);      // 모든 컨트롤 포인트 그리기
        }
    }
    glEnd();                                        // 점 그리기 종료
}

void drawControlLines() {
    glColor3f(0.0, 0.0, 0.0);                       // 검은색으로 설정
    glLineWidth(2.0);                               // 두께를 2로 설정

    for (int i = 0; i < 4; ++i) {
        glBegin(GL_LINE_STRIP);                     // 선 그리기 시작
        for (int j = 0; j < 4; ++j) {
            glVertex3fv(&ctrlpoints[i][j][0]);      // 컨트롤 포인트를 이어 선 그리기
        }
        glEnd();                                    // 선 그리기 종료
    }

    for (int j = 0; j < 4; ++j) {
        glBegin(GL_LINE_STRIP);                     // 선 그리기 시작
        for (int i = 0; i < 4; ++i) {
            glVertex3fv(&ctrlpoints[i][j][0]);      // 컨트롤 포인트를 이어 선 그리기
        }
        glEnd();                                    // 선 그리기 종료
    }
}

// 이항 계수를 계산하는 함수
int binomialCoeff(int n, int k) {
    if (k == 0 || k == n)                                               // k가 0이거나 k가 n일 경우 1을 반환
        return 1;
    return binomialCoeff(n - 1, k - 1) + binomialCoeff(n - 1, k);       // 재귀적으로 이항 계수를 계산하여 반환
}

void drawBezierSurface() {
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);                                                      // 파란색으로 설정
    
    for (float u = 0.0f; u < 1.0f; u += 0.001f) {                                           // u값 증가 (0.001 간격으로 선을 그려 면을 만든다.)
        glBegin(GL_LINE_STRIP);                                                             // 선 그리기 시작
        
        for (float v = 0.0f; v < 1.0f; v += 0.001f) {                                       // v값 증가 (0.001 간격으로 선을 그려 면을 만든다.)
            float x = 0.0;
            float y = 0.0;
            float z = 0.0;
            
            for (int j = 0; j < 4; j++) {                                                   // j값 증가
                for (int k = 0; k < 4; k++) {                                               // k값 증가
                    float basisU = binomialCoeff(3, j) * pow(1 - u, 3 - j) * pow(u, j);     // u에 대한 기저함수 계산
                    float basisV = binomialCoeff(3, k) * pow(1 - v, 3 - k) * pow(v, k);     // v에 대한 기저함수 계산
                    x += basisU * basisV * ctrlpoints[j][k][0];                             // x좌표 계산
                    y += basisU * basisV * ctrlpoints[j][k][1];                             // y좌표 계산
                    z += basisU * basisV * ctrlpoints[j][k][2];                             // z좌표 계산
                }
            }
            glVertex3f(x, y, z);                                                            // 계산된 좌표로 선 그리기
        }
        glEnd();                                                                            // 선 그리기 종료
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // 색상 버퍼와 깊이 버퍼 초기화
    glEnable(GL_DEPTH_TEST);                                    // 깊이 버퍼 사용

    drawAxis();                                                 // 축 그리기
    drawPlane();                                                // 바닥 Matrix 그리기
    drawControlPoints();                                        // 제어점 그리기
    drawControlLines();                                         // 제어선 그리기
    drawBezierSurface();                                        // 베지어 곡면 그리기

    glFlush();                                                  // 명령어를 모두 실행
}

void init() {
    glClearColor(0.6, 0.6, 0.6, 1.0);                           // 배경색 설정

    glMatrixMode(GL_MODELVIEW);                                 // 모델뷰 매트릭스 설정
    glLoadIdentity();                                           // 현재 매트릭스를 단위행렬로 초기화
    gluLookAt(3, 3, 4.5, 3, -2, -20, 0, 1, 0);                  // 카메라 위치 설정

    glMatrixMode(GL_PROJECTION);                                // 투영 매트릭스 설정
    glLoadIdentity();                                           // 현재 매트릭스를 단위행렬로 초기화
    gluPerspective(60.0, 4.0 / 3.0, 1, 100);                    // 원근 투영 설정

    glEnable(GL_DEPTH_TEST);                                    // 깊이 버퍼 사용
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);                                          // GLUT 초기화
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);       // 디스플레이 모드 설정
    glutInitWindowPosition(120, 80);                                // 윈도우 위치 설정
    glutInitWindowSize(1280, 980);                                  // 윈도우 크기 설정
    glutCreateWindow("Bezier Surface");                             // 윈도우 생성
    init();                                                         // 초기화 함수 호출
    glutDisplayFunc(display);                                       // 디스플레이 콜백 함수 등록
    glutMainLoop();                                                 // 이벤트 루프 시작
    return 0;
}




