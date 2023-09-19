#define GL_SILENCE_DEPRECATION              // MacOS Deprecated 오류 미출력 코드
#include <GL/glut.h>
#include <OpenGL/GL.h>
#include <OpenGL/GLU.h>

void Display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // 배경 색상 Clear: Black
    glClear(GL_COLOR_BUFFER_BIT);           // Clear buffer
    
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);      // 색상 설정: Green
    
    glBegin(GL_POLYGON);                    // 다각형 그리기 시작
    glVertex3f(-0.5, -0.5, 0.0);            // 첫 번째 점
    glVertex3f(0.5, -0.5, 0.0);             // 두 번째 점
    glVertex3f(0.5, 0.5, 0.0);              // 세 번째 점
    glVertex3f(-0.5, 0.5, 0.0);             // 네 번째 점
    glEnd();                                // 다각형 그리기 종료
    
    glFlush();                              // 화면에 출력
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                  // GLUT 초기화
    
    glutInitWindowPosition(150, 150);       // 윈도우 위치 설정
    glutInitWindowSize(500, 500);           // 윈도우 크기 설정
    glutCreateWindow("No 1");               // 윈도우 생성
    
    glutDisplayFunc(Display);               // 콜백 함수 설정
    glutMainLoop();                         // 이벤트 루프
    return 0;
}
