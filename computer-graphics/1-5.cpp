#define GL_SILENCE_DEPRECATION                      // MacOS Deprecated 오류 미출력 코드
#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);                   // Clear buffer

    glBegin(GL_LINES);                              // 선 그리기 시작
    
    /** Axis 그리기 **/
    glColor3f(1, 0, 0);                             // 색상 설정: Red
    glVertex3f(0, 0, 0);                            // x축 시작 점
    glVertex3f(6, 0, 0);                            // x축 끝 점
    
    glColor3f(0, 1, 0);                             // 색상 설정: Green
    glVertex3f(0, 0, 0);                            // y축 시작 점
    glVertex3f(0, 4, 0);                            // y축 끝 점
    
    glColor3f(0, 0, 1);                             // 색상 설정: Blue
    glVertex3f(0, 0, 0);                            // z축 시작 점
    glVertex3f(0, 0, -10);                          // z축 끝 점, - 방향으로 다시 그리기
    
    /** Matrix 그리기 **/
    float gap = 0.5;                                // 간격 설정 0.5
    glColor3f(1, 1, 1);                             // 색상 설정: White
    for (float x = gap; x <= 6.0; x += gap) {       // x 좌표를 0.5부터 0.5씩 더하면서 6까지 진행 (세로 선)
        glVertex3f(x, 0.0, 0.0);                    // 세로선 시작 점
        glVertex3f(x, 0.0, -6.0);                   // 세로선 끝 점
    }
    for (float z = gap; z <= 6.0; z += gap) {       // z 좌표를 0.5부터 0.5씩 더하면서 6까지 진행 (가로 선)
        glVertex3f(-0.0, 0.0, -z);                  // 가로선 시작 점
        glVertex3f(6.0, 0.0, -z);                   // 가로선 끝 점
    }
    
    glEnd();                                        // 선 그리기 종료
    
    glFlush();                                      // 화면에 출력
}

void init() {
    glClearColor(0.5, 0.5, 0.5, 1.0);               // 배경 색상 Clear: Gray, 가시성을 위한 배경색 변경
    
    glMatrixMode(GL_PROJECTION);                    // 투영 행렬 모드
    glLoadIdentity();                               // 행렬 초기화
    gluPerspective(60.0, 5.0 / 3.0, 1, 100);        // 원근 투영 행렬 설정(3D, 거리에 따라 크기 조정) <-> 직교 투영(2D, glOrtho)
    
    glMatrixMode(GL_MODELVIEW);                     // 모델뷰 행렬 모드
    glLoadIdentity();                               // 행렬 초기화
    gluLookAt(3, 3.3, 4, 3, 1, -4, 0, 1, 0);        // (3, 3.3, 4) 위치에서 (3, 1, -4) 방향으로 시점 설정, 카메라를 y축을 중심으로 세움(0, 1, 0)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                          // GLUT 초기화
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // 디스플레이 모드 설정(싱글 버퍼 사용(기본값) | 트루컬러 모드(기본값))
    glutInitWindowPosition(120, 80);                // 윈도우 위치 설정
    glutInitWindowSize(800, 620);                   // 윈도우 크기 설정
    glutCreateWindow("Matrix");                     // 윈도우 생성
    glutDisplayFunc(display);                       // 콜백 함수 설정
    init();                                         // init 함수 호출
    glutMainLoop();                                 // 이벤트 루프
}
