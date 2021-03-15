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
	// ��������
	GLfloat ratio = (float)(NewWidth - left) / (NewHeight - bottom);
	gluPerspective(40, ratio, 0.01, 100);
}

// ��� ������ ����
GLfloat move_x_human = 0.0f;
GLfloat move_z_human = 0.08f;
// ������ ����� ���� ����
int isHold = 0;
GLfloat move_x_brick = -2.0f;
GLfloat move_y_brick = BRICK_SIZE;
GLfloat move_z_brick = 1.0f;
GLfloat angle_brick = -90.0f;
// �ǹ��� �������� ���� ����
int isBlow = 0;
// ����� ������ �� ȸ���ϱ� ���� ����
GLfloat angle_z_human = 0.0f;

void MyDisplay() {
	// ���� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// drawAxis();
	glMatrixMode(GL_MODELVIEW);
	// �ʱ�ȭ
	glLoadIdentity();
	// ���� ����
	gluLookAt(camx, camy, camz,	// ���� �����ϴ� ��ġ
		cam2x, cam2y, cam2z,	// ���� ���� ���͸� ���� �ִ�.
		cam_upx, cam_upy, cam_upz);	// ī�޶��� ���� (y ���ϰ� �����ϴ�)

	// ���
	// �볪�� ����
	drawChair();
	// ��
	glPushMatrix();
	glRotatef(-50, 1, 0, 0);
	glTranslatef(-0.6f, -0.4f, 0.35f);
	drawShovel();
	glPopMatrix();
	// ���� ��ġ
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
	// �ǹ��� ��ٸ�
	glPushMatrix();
	glTranslatef(4.0f, 0.0f, 1.0f);
	drawHouse(isBlow);
	glTranslatef(- 1.525f, 0.0f, 0.0f);
	glRotatef(-90, 0, 1, 0);
	drawLadder(isBlow);
	glPopMatrix();

	// ���
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
		// a�� ���� ��� mode �� �����
	case '*':
		isBlow = (isBlow + 1) % 2;
		break;
		// ���α׷��� ���� �� �ְ� ��
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
		// ���� ����
		// �ʱ� �� camx = -8, camy = 16, camz = -8;
		if (count < 450) {
			GLfloat theta = count < 350 ? -0.0075f : -0.015f;
			GLfloat temp_x = camx;
			camx = cos(theta) * camx + sin(theta) * camz;
			camz = -sin(theta) * temp_x + cos(theta) * camz;
			camy -= 0.025f;
		}
		// ����� ������
		else if (count < 650) {
			// ī�޶� ������
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
		// �㸮 ���̴� 50��
		else if (count < 950) {
			if (count == 900) {
				camx = -6.0f;
				camz = 1.0f;
				cam2x = -2.0f;
				cam2z = 1.0f;
				camy = 1.2f;
			}
		}
		// ���ø��� 100��
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
		// ������ ��� ���� ��� �ø�
		else if (count < 1150) {
			angle_brick += 0.9f;
			move_x_brick += 0.004f;
			move_y_brick += 0.0023f;
			move_z_brick += 0.003f;
		}
		// ���� Ÿ��
		else if(count < 1200){}
		// ������ ��� ȸ��1
		else if (count < 1250) {
			// ������ 90�� ���� ���� �����̴� ��
			angle_brick -= 1.8f;
			move_x_brick += -0.008f;
			move_z_brick += -0.006f;
			// ķ ������ �����̷� õõ�� �����δ�.
			camy += -0.001f;
			camx += 0.0235f;
		}
		// ������ ��� ȸ��2
		else if (count < 1300) {
			// ������ 90�� ���� ���� �����̴� ��
			angle_brick -= 1.8f;
			move_x_brick += 0.008f;
			move_z_brick += -0.006f;
			// ķ ������ �����̷� õõ�� �����δ�
			camy += -0.001f;
			camx += 0.0235f;
		}
		// ������ ��� �ɾ�� ���
		else if (count < 1900) {
			int count2 = count % 100;
			// ķ�� ������
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
			// ����� ������ ������
			if (count2 < 50)
				move_y_brick += 0.001f;
			else if (count2 < 100)
				move_y_brick += -0.001f;
			move_x_human += 0.006167f;
		}
		// ��ٸ��� �ö󰡱� ��
		else if (count < 1950) {
			// ī�޶� �þ߿��� ������ ������ ��¦ ������ ���־�� �Ѵ�.
			camx += 0.005f;
			cam2x += 0.005f;
			cam2y += 0.02f;
		}
		// ��ٸ��� �ö󰡴� ��
		else if (count < 2150) {
			int count2 = (count - 1950) % 100;
			// ī�޶� ��ٸ��� �ö󰡴� ��
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
			// ĳ���ʹ� �ϴ� ���� ����.
			move_x_human += 0.0047f;
			move_y_brick += 0.008f;
		}
		// ������ ��ٸ� ���� �� �ǹ��� ���ƾ� �ϱ� ����
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
		// �ǹ� ������ ȭ���� ���ƾ� �Ѵ�.
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
		// ��ٸ� ������ ������ �ø��� ���� ������
		else if (count < 2400) {
			angle_brick += -0.9f;
			move_x_brick += 0.004f;
			move_y_brick += -0.0023f;
			move_z_brick += 0.003f;
		}
		// ������ 2�ʵ��� �䳻 ���� ���� ī�޶� ������
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
		// �������� ���� ���� up
		else if (count < 2700) {}
		// �ǹ��� �������� �� ON
		else if (count < 2800) {
			// ����� ������ �������� �������
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
		// ī�޶� �󱼷� ����
		else if (count < 2900) {
			camx += -0.0589f;
			cam2x += -0.017f;
			camy += -0.0435f;
			cam2y += -0.0165f;
		}
		// �������� �ٽ� ó������ ���ư��� ���Ѽ���
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

	// display �� �̺�Ʈ
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	// �� �������� ���� �� �ο�
	initBlow();

	glutTimerFunc(10, MyTimer, 1);
	// �Լ� Loopx
	glutMainLoop();
	return 0;
}