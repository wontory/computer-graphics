#define GL_SILENCE_DEPRECATION                                          // MacOS Deprecated 오류 미출력 코드
#include <GL/glut.h>

void drawAxis() {
    glBegin(GL_LINES);                                                  // 선 그리기 시작
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(6.5, 0, 0);     // 색상 설정: Red, x축(0 ~ 6.5) 그리기
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 4, 0);       // 색상 설정: Green, y축(0 ~ 4) 그리기
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, -8);      // 색상 설정: Blue, z축(0 ~ -8) 그리기
    glEnd();                                                            // 선 그리기 종료
}

void drawPlane() {
    glColor3f(1.0, 1.0, 1.0);                                           // 색상 설정: White
    
    glBegin(GL_LINES);                                                  // 선 그리기 시작
    for (GLfloat i = 0; i <= 6; i += 0.25) {                            // 0부터 6까지 0.25 간격으로 Matrix 생성
        glVertex3f(i, 0, -6);                                           // 세로선 시작 점
        glVertex3f(i, 0, 0);                                            // 세로선 끝 점
        glVertex3f(6, 0, -i);                                           // 가로선 시작 점
        glVertex3f(0, 0, -i);                                           // 가로선 끝 점
    }
    glEnd();                                                            // 선 그리기 종료
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);                                       // Clear buffer
    
    drawPlane();                                                        // Matrix(Plane) 그리기
    drawAxis();                                                         // Axis 그리기
    
    // Cube
    glPushMatrix();                                                     // 행렬 스택에 현재 좌표축 저장
    glTranslatef(4.0, -0.07, -1.3);                                     // x, y, z축으로의 이동 값 정의, (4, -0.07, -1.3) 위치로 이동
    glColor3f(138.0f / 255.0f, 43.0f / 255.0f, 226.0f / 255.0f);        // 색상 설정: 보라색
    glutSolidCube(0.75);                                                // 크기(size): 0.75, 솔리드 타입 정육면체 생성
    glPopMatrix();                                                      // 변환 전 좌표축으로 복구
    
    // Teapot
    glPushMatrix();                                                     // 행렬 스택에 현재 좌표축 저장
    glTranslatef(1.5, 0.0, -3.3);                                       // x, y, z축으로의 이동 값 정의, (1.5, 0.0, -3.3) 위치로 이동
    glRotatef(180.0, 0.0, 1.0, 0.0);                                    // y축을 중심으로 180도 회전 -> 주전자 입이 반대방향을 바라보도록 회전
    glColor3f(155.0f / 255.0f, 228.0f / 255.0f, 102.0f / 255.0f);       // 색상 설정: 연두색
    glutSolidTeapot(0.6);                                               // 크기(size): 0.6, 솔리드 타입 주전자 생성
    glPopMatrix();                                                      // 변환 전 좌표축으로 복구
    
    // Cone
    glPushMatrix();                                                     // 행렬 스택에 현재 좌표축 저장
    glTranslatef(3.0, 0.0, -5.0);                                       // x, y, z축으로의 이동 값 정의, (3, 0, -5) 위치로 이동
    glColor3f(248.0f / 255.0f, 155.0f / 255.0f, 0.0f / 255.0f);         // 색상 설정: 주황색
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);                                // 뿔이 앞쪽 -> 위쪽 방향을 바라보도록 회전
    glutSolidCone(0.5, 1, 20, 20);                                      // 크기(base, height): (0.5, 1), 사각뿔 와이어프레임 생성 ((slices, stacks), (20, 20))
    glPopMatrix();                                                      // 변환 전 좌표축으로 복구
    
    glFlush();                                                          // 화면에 출력
}

void init() {
    glClearColor(0.6, 0.6, 0.6, 1.0);                                   // 배경 색상 Clear
    
    glMatrixMode(GL_PROJECTION);                                        // 투영 행렬 모드
    glLoadIdentity();                                                   // 행렬 초기화
    gluPerspective(60.0, 4.0 / 3.0, 6.8, 9);
    /**
     gluLookAt의 Eye 위치(3, 3, 4.5)를 기준으로 fovy, aspect, near, far.
     
     즉,
     z 범위: -2.3 ~ -4.5
     의 영역을 원근 투영
     
     Teapot의 z 범위: -2.7 ~ -3.9
     */
    
    glMatrixMode(GL_MODELVIEW);                                         // 모델뷰 행렬 모드
    glLoadIdentity();                                                   // 행렬 초기화
    gluLookAt(3, 3, 4.5, 3, -2, -20, 0, 1, 0);                          // (3, 3, 4.5) 위치에서 (3, -2, -20) 방향으로 시점 설정, 카메라를 y축을 중심으로 세움(0, 1, 0)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                                              // GLUT 초기화
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);                        // 디스플레이 모드 설정(싱글 버퍼 사용(기본값) | 트루컬러 모드(기본값))
    glutInitWindowPosition(120, 80);                                    // 윈도우 위치 설정
    glutInitWindowSize(1280, 980);                                      // 윈도우 크기 설정
    glutCreateWindow("Objects");                                        // 윈도우 생성
    glutDisplayFunc(display);                                           // 콜백 함수 설정
    init();                                                             // init 함수 호출
    glutMainLoop();                                                     // 이벤트 루프
}
