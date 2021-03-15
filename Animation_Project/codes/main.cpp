#include "human.h"
#include "background.h"

#define _WINDOW_WIDTH	1000
#define _WINDOW_HEIGHT	700

int start = 0;

void InitVisibility() {
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
}

GLfloat camx = -8, camy = 16, camz = -8;
GLfloat cam2x = 0, cam2y = 1, cam2z = 0.08f;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;
void MyReshape(int NewWidth, int NewHeight) {
	GLint left = 0;
	GLint bottom = 0;
	glViewport(left, bottom, NewWidth - left, NewHeight - bottom);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// 원근투영
	GLfloat ratio = (float)(NewWidth - left) / (NewHeight - bottom);
	gluPerspective(40, ratio, 0.01, 100);
}

// 사람 움직임 변수
GLfloat move_x_human = 0.0f;
GLfloat move_z_human = 0.08f;
// 벽돌을 들고가기 위한 변수
int isHold = 0;
GLfloat move_x_brick = -2.0f;
GLfloat move_y_brick = BRICK_SIZE;
GLfloat move_z_brick = 1.0f;
GLfloat angle_brick = -90.0f;
// 건물이 무너지기 위한 변수
int isBlow = 0;
// 사람이 떨어질 때 회전하기 위한 변수
GLfloat angle_z_human = 0.0f;

void MyDisplay() {
	// 색을 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// drawAxis();
	glMatrixMode(GL_MODELVIEW);
	// 초기화
	glLoadIdentity();
	// 보는 방향
	gluLookAt(camx, camy, camz,	// 눈이 존재하는 위치
		cam2x, cam2y, cam2z,	// 보는 방향 센터를 보고 있다.
		cam_upx, cam_upy, cam_upz);	// 카메라의 방향 (y 축하고 동일하다)

	// 배경
	// 통나무 의자
	drawChair();
	// 삽
	glPushMatrix();
	glRotatef(-50, 1, 0, 0);
	glTranslatef(-0.6f, -0.4f, 0.35f);
	drawShovel();
	glPopMatrix();
	// 벽돌 뭉치
	glPushMatrix();
	glTranslatef(-2.0f, 0.0f, 1.0f);
	glRotatef(90, 0, 1, 0);
	drawBase();
	glPopMatrix();
	if (!isHold) {
		glPushMatrix();
		glTranslatef(move_x_brick, move_y_brick, move_z_brick);
		glRotatef(angle_brick, 0, 1, 0);
		drawBrick(0, 0, 0, 0);
		glPopMatrix();
	}
	// 건물과 사다리
	glPushMatrix();
	glTranslatef(4.0f, 0.0f, 1.0f);
	drawHouse(isBlow);
	glTranslatef(- 1.525f, 0.0f, 0.0f);
	glRotatef(-90, 0, 1, 0);
	drawLadder(isBlow);
	glPopMatrix();

	// 사람
	glPushMatrix();
	glTranslatef(move_x_human, 0, move_z_human);
	glRotatef(angle_z_human,0,0,1);
	drawHuman();
	if (isHold) {
		glPushMatrix();
		glTranslatef(move_x_brick, move_y_brick, move_z_brick);
		glRotatef(angle_brick, 0, 1, 0);
		drawBrick(0, 0, 0, 0);
		glPopMatrix();
	}
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
	switch (KeyPressed) {
		// a를 누를 경우 mode 가 변경됨
	case '*':
		isBlow = (isBlow + 1) % 2;
		break;
		// 프로그램을 나갈 수 있게 함
	case '-':
		start = (start + 1) % 2;
		break;
	case 'q':
	case 27:
		exit(0);	break;
	}
}

int count = 0;

void MyTimer(int value) {
	if (start) {
		// 시점 변경
		// 초기 값 camx = -8, camy = 16, camz = -8;
		if (count < 450) {
			GLfloat theta = count < 350 ? -0.0075f : -0.015f;
			GLfloat temp_x = camx;
			camx = cos(theta) * camx + sin(theta) * camz;
			camz = -sin(theta) * temp_x + cos(theta) * camz;
			camy -= 0.025f;
		}
		// 사람의 움직임
		else if (count < 650) {
			// 카메라 움직임
			if (count < 500) {
				camx += 0.044512f;
				camy -= 0.055002f;
				camz -= 0.121852f;
			}
			move_z_human += 0.0046f;
			camz += 0.0046f;
			cam2z += 0.0046f;
		}
		else if (count < 900) {
			if (700 <= count) {
				move_x_human -= 0.0075f;
			}
			camy += 0.005f;
		}
		// 허리 숙이는 50초
		else if (count < 950) {
			if (count == 900) {
				camx = -6.0f;
				camz = 1.0f;
				cam2x = -2.0f;
				cam2z = 1.0f;
				camy = 1.2f;
			}
		}
		// 들어올리는 100초
		else if (count < 1050) {
			if (count == 950) {
				move_x_brick = -0.5f;
				move_y_brick = BRICK_SIZE;
				move_z_brick = 0.0f;
				isHold = 1;
			}
			move_x_brick += 0.0015f;
			move_y_brick += 0.005f;
		}
		// 벽돌을 어깨 위로 들어 올림
		else if (count < 1150) {
			angle_brick += 0.9f;
			move_x_brick += 0.004f;
			move_y_brick += 0.0023f;
			move_z_brick += 0.003f;
		}
		// 쉬는 타임
		else if(count < 1200){}
		// 벽돌을 들고 회전1
		else if (count < 1250) {
			// 벽돌이 90도 돌기 위해 움직이는 것
			angle_brick -= 1.8f;
			move_x_brick += -0.008f;
			move_z_brick += -0.006f;
			// 캠 각도를 눈높이로 천천히 움직인다.
			camy += -0.001f;
			camx += 0.0235f;
		}
		// 벽돌을 들고 회전2
		else if (count < 1300) {
			// 벽돌이 90도 돌기 위해 움직이는 것
			angle_brick -= 1.8f;
			move_x_brick += 0.008f;
			move_z_brick += -0.006f;
			// 캠 각도를 눈높이로 천천히 움직인다
			camy += -0.001f;
			camx += 0.0235f;
		}
		// 벽돌을 들고 걸어가는 사람
		else if (count < 1900) {
			int count2 = count % 100;
			// 캠의 움직임
			if (count < 1400) {
				camy += -0.001f;
				camx += 0.0235f;
				cam2x += 0.0235f;
			}
			else {
				if (count2 < 50) {
					camy += 0.001f;
					cam2y += 0.001f;
				}
				else {
					camy -= 0.001f;
					cam2y -= 0.001f;
				}
			}
			camx += 0.006167f;
			cam2x += 0.006167f;
			// 사람과 벽돌의 움직임
			if (count2 < 50)
				move_y_brick += 0.001f;
			else if (count2 < 100)
				move_y_brick += -0.001f;
			move_x_human += 0.006167f;
		}
		// 사다리를 올라가기 전
		else if (count < 1950) {
			// 카메라 시야에서 나오기 때문에 살짝 앞으로 가주어야 한다.
			camx += 0.005f;
			cam2x += 0.005f;
			cam2y += 0.02f;
		}
		// 사다리를 올라가는 것
		else if (count < 2150) {
			int count2 = (count - 1950) % 100;
			// 카메라가 사다리를 올라가는 것
			if (count2 < 50) {
				camx += 0.00313f;
				cam2x += 0.00313f;
				camy += 0.0106f;
				cam2y += 0.0106f;
			}
			else if (count2 < 100) {
				camx += 0.00626f;
				cam2x += 0.00626f;
				camy += 0.0053f;
				cam2y += 0.0053f;
			}
			// 캐릭터는 일단 같이 간다.
			move_x_human += 0.0047f;
			move_y_brick += 0.008f;
		}
		// 마지막 사다리 오를 땐 건물을 보아야 하기 때문
		else if (count < 2250) {
			int count2 = (count - 1950) % 100;
			if (count2 < 50) {
				camx += 0.00313f;
				cam2x += -0.00313f;
				camy += 0.0106f;
				cam2y += -0.0106f;
			}
			else if (count2 < 100) {
				camx += 0.00626f;
				//cam2x += -0.00626f;
				camy += 0.0053f;
				//cam2y += -0.0053f;
			}
			move_x_human += 0.0047f;
			move_y_brick += 0.008f;
			
		}
		// 건물 위에서 화면을 보아야 한다.
		else if (count < 2300) {
			if (count == 2250) {
				camx = 8.0f;
				camy = 6.0f;
				camz = 1.0f;
				cam2x = move_x_human;
				cam2y = 2.0f;
				cam2z = move_z_human;
			}
		}
		// 사다리 위에서 벽돌을 올리기 위한 움직임
		else if (count < 2400) {
			angle_brick += -0.9f;
			move_x_brick += 0.004f;
			move_y_brick += -0.0023f;
			move_z_brick += 0.003f;
		}
		// 지진을 2초동안 흉내 내기 위한 카메라 움직임
		else if (count < 2600) {
			int count2 = (count - 2400) % 40;
			if (count2 < 10) {
				camx += 0.01f;
				cam2x += 0.01f;
				camy += 0.007f;
				camy += 0.007f;
			}
			else if (count2 < 20) {
				camx += -0.01f;
				cam2x += -0.01f;
				camy += -0.007f;
				cam2y += -0.007f;
			}
			else if (count2 < 30) {
				camx += -0.01f;
				cam2x += -0.01f;
				camy += 0.007f;
				cam2y += 0.007f;
			}
			else if (count2 < 40) {
				camx += 0.01f;
				cam2x += 0.01f;
				camy += -0.007f;
				cam2y += -0.007f;
			}
			move_x_brick += 0.001f;
			move_y_brick += -0.002f;
		}
		// 무너지기 전의 감정 up
		else if (count < 2700) {}
		// 건물이 무너지는 것 ON
		else if (count < 2800) {
			// 사람과 벽돌의 움직임을 때어놓음
			if (count == 2700) {
				isBlow = 1;
				isHold = 0;
				move_x_brick = move_x_human + move_x_brick;
				move_y_brick = 2.375;
				move_z_brick = move_z_human + move_z_brick;
			}
			move_y_brick += -0.02f;
			move_x_human += -0.015f;
			angle_z_human += 0.9f;
		}
		// 카메라를 얼굴로 무빙
		else if (count < 2900) {
			camx += -0.0589f;
			cam2x += -0.017f;
			camy += -0.0435f;
			cam2y += -0.0165f;
		}
		// 마지막에 다시 처음으로 돌아가기 위한선언
		else if (count == 3049) {
			isBlow = 0;
			initBlow();
			initHuman();
			camx = -8; camy = 16; camz = -8;
			cam2x = 0; cam2y = 1; cam2z = 0.08f;
			cam_upx = 0; cam_upy = 1; cam_upz = 0;
			move_x_human = 0.0f;
			move_z_human = 0.08f;
			isHold = 0;
			move_x_brick = -2.0f;
			move_y_brick = BRICK_SIZE;
			move_z_brick = 1.0f;
			angle_brick = -90.0f;
			isBlow = 0;
			angle_z_human = 0.0f;
		}
		
		humanAnimation(count);
		count = (count + 1) % 3050;
	}
	glutTimerFunc(10, MyTimer, 1);
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
	glutCreateWindow("Animation");
	glClearColor(1, 1, 1, 0);
	InitVisibility();

	// display 밑 이벤트
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	// 블럭 무너짐을 위한 값 부여
	initBlow();

	glutTimerFunc(10, MyTimer, 1);
	// 함수 Loopx
	glutMainLoop();
	return 0;
}