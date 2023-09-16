#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>
#include <OpenGL/GL.h>
#include <OpenGL/GLU.h>
#include <cmath>

void Display() {
    glClearColor(1.0f, 0.411765f, 0.705882f, 1.0f);     // 배경 색상 Clear: Hot Pink, (2) 배경 색상 변경
    glClear(GL_COLOR_BUFFER_BIT);                       // Clear buffer
    
    glColor4f(0.627451f, 0.12549f, 0.941176f, 1.0f);    // 색상 설정: Purple, (2) 도형 색상 변경
    
    glBegin(GL_POLYGON);                                // 다각형 그리기 시작, (1) 사각형을 제외한 도형 생성
    // Todo
    glEnd();                                            // 다각형 그리기 종료
    
    glFlush();                                          // 화면에 출력
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                              // GLUT 초기화
    
    glutInitWindowPosition(150, 150);                   // 윈도우 위치 설정
    glutInitWindowSize(500, 500);                       // 윈도우 크기 설정
    glutCreateWindow("AI컴퓨터공학부 조성원");               // 윈도우 생성, (3) 생성된 윈도우의 Title을 본인 이름으로 변경
    
    glutDisplayFunc(Display);                           // 콜백 함수 설정
    glutMainLoop();                                     // 이벤트 루프
    return 0;
}
