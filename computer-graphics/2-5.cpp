#define GL_SILENCE_DEPRECATION                                                          // MacOS Deprecated 오류 미출력 코드
#include <GL/glut.h>

GLfloat lightPosition[] = { 3, 4, 2 };                                                  // 빛의 위치를 저장할 배열

void drawAxis() {
    glPushMatrix();                                                                     // 행렬 스택에 현재 좌표축 저장
    glBegin(GL_LINES);                                                                  // 선 그리기 시작
    GLfloat red[] = { 255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f };                  // 색상 설정: Red
    glMaterialfv(GL_FRONT, GL_AMBIENT, red);                                            // Red 색 주변광 재질 설정
    glVertex3f(0, 0, 0); glVertex3f(6.5, 0, 0);                                         // x축(0 ~ 6.5) 그리기
    glPopMatrix();                                                                      // 변환 전 좌표축으로 복구

    glPushMatrix();                                                                     // 행렬 스택에 현재 좌표축 저장
    GLfloat green[] = { 0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f };                // 색상 설정: Green
    glMaterialfv(GL_FRONT, GL_AMBIENT, green);                                          // Green 색 주변광 재질 설정
    glVertex3f(0, 0, 0); glVertex3f(0, 4, 0);                                           // y축(0 ~ 4) 그리기
    glPopMatrix();                                                                      // 변환 전 좌표축으로 복구

    glPushMatrix();                                                                     // 행렬 스택에 현재 좌표축 저장
    GLfloat blue[] = { 0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f };                 // 색상 설정: Blue
    glMaterialfv(GL_FRONT, GL_AMBIENT, blue);                                           // Blue 색 주변광 재질 설정
    glVertex3f(0, 0, 0); glVertex3f(0, 0, -8);                                          // z축(0 ~ -8) 그리기
    glEnd();                                                                            // 선 그리기 종료
    glPopMatrix();                                                                      // 변환 전 좌표축으로 복구
}

void drawPlane() {
    GLfloat white[] = { 255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f };            // 색상 설정: White
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);                                          // White 색 주변광 재질 설정

    glBegin(GL_LINES);                                                                  // 선 그리기 시작
    for (GLfloat i = 0; i <= 6; i += 0.25) {                                            // 0부터 6까지 0.25 간격으로 Matrix 생성
        glVertex3f(i, 0, -6);                                                           // 세로선 시작 점
        glVertex3f(i, 0, 0);                                                            // 세로선 끝 점
        glVertex3f(6, 0, -i);                                                           // 가로선 시작 점
        glVertex3f(0, 0, -i);                                                           // 가로선 끝 점
    }
    glEnd();                                                                            // 선 그리기 종료
}

void drawObjects() {
    glPushMatrix();                                                                     // 행렬 스택에 현재 좌표축 저장
    glTranslatef(4.0, 0.5, -1.3);                                                       // x, y, z축으로의 이동 값 정의, (4, 0.5, -1.3) 위치로 이동
    GLfloat InePurple[] = { 138.0f / 255.0f, 43.0f / 255.0f, 226.0f / 255.0f };         // 색상 설정: InePurple
    glMaterialfv(GL_FRONT, GL_AMBIENT, InePurple);                                      // InePurple 색 주변광 재질 설정
    glutSolidCube(0.75);                                                                // 크기(size): 0.75, 솔리드 타입 정육면체 생성
    glPopMatrix();                                                                      // 변환 전 좌표축으로 복구

    glPushMatrix();                                                                     // 행렬 스택에 현재 좌표축 저장
    glTranslatef(1.5, 0.5, -3.3);                                                       // x, y, z축으로의 이동 값 정의, (1.5, 0.5, -3.3) 위치로 이동
    glRotatef(180.0, 0.0, 1.0, 0.0);                                                    // y축을 중심으로 180도 회전 -> 주전자 입이 반대방향을 바라보도록 회전
    GLfloat peridotGreen[] = { 155.0f / 255.0f, 228.0f / 255.0f, 102.0f / 255.0f };     // 색상 설정: PeridotGreen
    glMaterialfv(GL_FRONT, GL_AMBIENT, peridotGreen);                                   // PeridotGreen 색 주변광 재질 설정
    glutSolidTeapot(0.6);                                                               // 크기(size): 0.6, 솔리드 타입 주전자 생성
    glPopMatrix();                                                                      // 변환 전 좌표축으로 복구

    glPushMatrix();                                                                     // 행렬 스택에 현재 좌표축 저장
    glTranslatef(3.0, 0.0, -5.0);                                                       // x, y, z축으로의 이동 값 정의, (3, 0, -5) 위치로 이동
    GLfloat orange[] = { 248.0f / 255.0f, 155.0f / 255.0f, 0.0f / 255.0f };             // 색상 설정: Orange
    glMaterialfv(GL_FRONT, GL_AMBIENT, orange);                                         // Orange 색 주변광 재질 설정
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);                                                // 뿔이 앞쪽 -> 위쪽 방향을 바라보도록 회전
    glutSolidCone(0.5, 1, 20, 20);                                                      // 크기(base, height): (0.5, 1), 사각뿔 와이어프레임 생성 ((slices, stacks), (20, 20))
    glPopMatrix();                                                                      // 변환 전 좌표축으로 복구
}

void init() {
    glClearColor(0.6, 0.6, 0.6, 1.0);                                                   // 배경 색상 Clear

    glMatrixMode(GL_PROJECTION);                                                        // 투영 행렬 모드
    glLoadIdentity();                                                                   // 행렬 초기화

    gluPerspective(60.0, 4.0 / 3.0, 1.0, 15.0);                                         // 원근 투영 행렬 설정(3D, 거리에 따라 크기 조정)

    glMatrixMode(GL_MODELVIEW);                                                         // 모델뷰 행렬 모드
    glLoadIdentity();                                                                   // 행렬 초기화
    gluLookAt(3, 3, 4.5, 3, -2, -20, 0, 1, 0);                                          // (3, 3, 4.5) 위치에서 (3, -2, -20) 방향으로 시점 설정, 카메라를 y축을 중심으로 세움 (0, 1, 0)

    GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };                                           // 색상 설정: Black
    GLfloat yellow[] = { 0.0, 0.0, 0.0, 1.0 };                                          // 색상 설정: Yellow
    GLfloat cyan[] = { 0.0, 0.0, 0.0, 1.0 };                                            // 색상 설정: Cyan
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };                                           // 색상 설정: White
    GLfloat direction[] = { 3.0, 4.0, 2.0, 1.0 };                                       // 방향 초기값 설정 (3, 4, 2)

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);                               // 바깥 면 설정, 재질의 속성을 cyan 주변광 재질과 발산광 재질로 설정
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);                                         // 바깥 면 설정, 재질의 속성을 white 반사광 재질로 설정
    glMaterialf(GL_FRONT, GL_SHININESS, 30);                                            // 바깥 면 설정, 재질의 반사율을 30으로 설정
    /**
     glMaterialfv 함수
     ================================================================================
     첫 번째 인자: 어떤 면의 재질을 설정할 것인지 결정 (GL_FRONT, GL_BACK, GL_FRONT_AND_BACK)
     두 번째 인자: 어떤 속성을 설정할 것인지 결정(Ambient, Diffuse, Specular, Shininess, Emissive)
     세 번째 인자: RGBA 값이 담긴 배열로 속성 설정
     */

    glLightfv(GL_LIGHT0, GL_AMBIENT, black);                                            // 주변광(Ambient) 조명의 색을 black으로 설정
    glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);                                           // 발산광(Diffuse) 조명의 색을 black으로 설정
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);                                           // 반사광(Specular) 조명의 색을 black으로 설정
    glLightfv(GL_LIGHT0, GL_POSITION, direction);                                       // 조명의 위치를 direction{3, 4, 2}으로 설정한다.
    /**
     glLightfv 함수
     ================================================================================
     Ambient Light: 주변광, 특정한 방향 없이 주변을 덮고 있는 빛
     Diffuse Light: 분산광, 일정한 방향으로 빛이 들어와서 물체의 표면에서 여러 방향으로 분산된다. (RectAreaLight)
     Specular Light: 반사광, 특정한 방향으로 유입되어 한 방향으로 완전히 반사되는 빛의 형태 (Spotlight)
     */

    glEnable(GL_LIGHTING);                                                              // 조명 켜기
    glEnable(GL_LIGHT0);                                                                // 0번 조명 사용(0번부터 7번까지 총 8개의 조명이 있다.)
    glEnable(GL_DEPTH_TEST);                                                            // 깊이 테스트 활성화 (기본값: 비활성화)
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                                 // Clear buffer

    glPushMatrix();                                                                     // 행렬 스택에 현재 좌표축 저장
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);                                   // 조명의 위치를 lightPosition{3, 4, 2}으로 설정 -> key_input에 의해 변경될 수 있음

    drawObjects();                                                                      // Objects 그리기
    drawAxis();                                                                         // Axis 그리기
    drawPlane();                                                                        // Matrix(Plane) 그리기

    glPopMatrix();                                                                      // 변환 전 좌표축으로 복구

    glFlush();                                                                          // 화면에 출력
}

void key_input(int key, int x, int y) {                                                 // x, y는 키 입력 시의 마우스 커서 위치를 받을 수 있다.
    switch (key) {
    case GLUT_KEY_UP:                                                                   // 윗 방향키
        lightPosition[0] = 3;                                                           // 광원의 x 좌표를 3으로 이동
        lightPosition[1] = 4;                                                           // 광원의 y 좌표를 4로 이동
        lightPosition[2] = -8;                                                          // 광원의 z 좌표를 -8로 이동
        glMatrixMode(GL_MODELVIEW);                                                     // 모델뷰 행렬 모드
        glLoadIdentity();                                                               // 행렬 초기화
        gluLookAt(3, 3, -10.5, 3, -2, 14, 0, 1, 0);                                     // (3, 3, -10.5) 위치에서 (3, -2, 14) 방향으로 시점 설정, 카메라를 y축을 중심으로 세움 (0, 1, 0)
        break;
    case GLUT_KEY_DOWN:                                                                 // 아랫 방향키
        lightPosition[0] = 3;                                                           // 광원의 x 좌표를 3으로 이동
        lightPosition[1] = 4;                                                           // 광원의 y 좌표를 4로 이동
        lightPosition[2] = 2;                                                           // 광원의 z 좌표를 2로 이동
        glMatrixMode(GL_MODELVIEW);                                                     // 모델뷰 행렬 모드
        glLoadIdentity();                                                               // 행렬 초기화
        gluLookAt(3, 3, 4.5, 3, -2, -20, 0, 1, 0);                                      // (3, 3, 4.5) 위치에서 (3, -2, -20) 방향으로 시점 설정, 카메라를 y축을 중심으로 세움 (0, 1, 0)
        break;
    case GLUT_KEY_LEFT:                                                                 // 왼 방향키
        lightPosition[0] = -2;                                                          // 광원의 x 좌표를 -2로 이동
        lightPosition[1] = 4;                                                           // 광원의 y 좌표를 4로 이동
        lightPosition[2] = -3;                                                          // 광원의 z 좌표를 -3으로 이동
        glMatrixMode(GL_MODELVIEW);                                                     // 모델뷰 행렬 모드
        glLoadIdentity();                                                               // 행렬 초기화
        gluLookAt(-4.5, 3, -3, 20, -2, -3, 0, 1, 0);                                    // (-4.5, 3, -3) 위치에서 (20, -2, -3) 방향으로 시점 설정, 카메라를 y축을 중심으로 세움 (0, 1, 0)
        break;
    case GLUT_KEY_RIGHT:                                                                // 오른 방향키
        lightPosition[0] = 8;                                                           // 광원의 x 좌표를 8로 이동
        lightPosition[1] = 4;                                                           // 광원의 y 좌표를 4로 이동
        lightPosition[2] = -3;                                                          // 광원의 z 좌표를 -3으로 이동
        glMatrixMode(GL_MODELVIEW);                                                     // 모델뷰 행렬 모드
        glLoadIdentity();                                                               // 행렬 초기화
        gluLookAt(10.5, 3, -3, -14, -2, -3, 0, 1, 0);                                   // (10.5, 3, -3) 위치에서 (-14, -2, -3) 방향으로 시점 설정, 카메라를 y축을 중심으로 세움 (0, 1, 0)
        break;
    }
    /**
     방향키에 따른 camera의 lookAt 회전
     ================================================================================
     카메라 높이는 항상 3으로 고정이고, 바닥 매트릭스의 중간 좌표 (x, z)가 (3, -3)이다.
     (3, -3)을 중심으로 기본 상태(아랫 방향키)의 (x, z) 좌표인 (3, 4.5)를 90, 180, 270° 회전시켜주면 된다.
     윗 방향키: (3, -10.5)
     아랫 방향키: (3, 4.5)
     왼 방향키: (-4.5, -3)
     오른 방향키: (10.5, -3)
     */

    glutPostRedisplay();                                                                // 변경된 윈도우를 표시하도록 요청
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                                                              // GLUT 초기화
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    /**
     디스플레이 모드 설정(싱글 버퍼 사용(기본값) | 트루컬러 모드(기본값) | 깊이 버퍼 사용(두 물체가 겹쳤을 때 어떤 색을 출력할지 결정))
     */
    glutInitWindowPosition(120, 80);                                                    // 윈도우 위치 설정
    glutInitWindowSize(1280, 980);                                                      // 윈도우 크기 설정
    glutCreateWindow("Axis");                                                           // 윈도우 생성
    glutDisplayFunc(display);                                                           // 콜백 함수 설정
    glutSpecialFunc(key_input);
    /**
     특수 키(방향키, Function 키 등)를 입력받도록 설정.
     문자 키 입력은 glutKeyboardFunc, 마우스 입력은 glutMouseFunc을 사용하면 된다.
     */
    init();                                                                             // init 함수 호출
    glutMainLoop();                                                                     // 이벤트 루프
}
