#define GL_SILENCE_DEPRECATION                      // MacOS Deprecated 오류 미출력 코드
#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);                   // Clear buffer
    
    glBegin(GL_LINES);                              // 선 그리기 시작
    
    glColor3f(1, 0, 0);                             // 색상 설정: Red
    glVertex3f(0, 0, 0);                            // x축 시작 점
    glVertex3f(5, 0, 0);                            // x축 끝 점
    
    glColor3f(0, 1, 0);                             // 색상 설정: Green
    glVertex3f(0, 0, 0);                            // y축 시작 점
    glVertex3f(0, 5, 0);                            // y축 끝 점
    
    glColor3f(0, 0, 1);                             // 색상 설정: Blue
    glVertex3f(0, 0, 0);                            // z축 시작 점
    glVertex3f(0, 0, 5);                            // z축 끝 점
    
    glEnd();                                        // 선 그리기 종료
    
    glFlush();                                      // 화면에 출력
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);               // 배경 색상 Clear: Black
    
    glMatrixMode(GL_PROJECTION);                    // 투영 행렬 모드
    glLoadIdentity();                               // 행렬 초기화
    gluPerspective(60.0, 5.0 / 3.0, 1, 100);        // 원근 투영 행렬 설정(3D, 거리에 따라 크기 조정) <-> 직교 투영(2D, glOrtho)
    
    glMatrixMode(GL_MODELVIEW);                     // 모델뷰 행렬 모드
    glLoadIdentity();                               // 행렬 초기화
    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);           // (5, 5, 5) 위치에서 (0, 0, 0) 방향으로 시점 설정, 카메라를 y축을 중심으로 세움(0, 1, 0)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                          // GLUT 초기화
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // 디스플레이 모드 설정(싱글 버퍼 사용(기본값) | 트루컬러 모드(기본값))
    glutInitWindowPosition(120, 80);                // 윈도우 위치 설정
    glutInitWindowSize(800, 620);                   // 윈도우 크기 설정
    glutCreateWindow("Init Axis");                  // 윈도우 생성
    glutDisplayFunc(display);                       // 콜백 함수 설정
    init();                                         // init 함수 호출
    glutMainLoop();                                 // 이벤트 루프
}
