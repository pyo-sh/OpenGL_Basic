#include "background.h"
#include "cylinder.h"

void drawBrick(GLfloat moveX, GLfloat moveY, GLfloat moveZ, GLfloat angle) {
	glPushMatrix();
	glTranslatef(moveX, moveY, moveZ);
	glRotatef(angle, 1, 1, 1);
	glScalef(BRICK_SCALE, 1, 1);
	glColor3f(179.0f / 255.0f, 57.0f / 255.0f, 57.0f / 255.0f);
	glutSolidCube(BRICK_SIZE);
	glColor3f(0,0,0);
	glutWireCube(BRICK_SIZE);
	glPopMatrix();
}

void drawBase() {
	glPushMatrix();
	drawBrick(-BRICK_SIZE, 0, 0, 0);
	drawBrick(BRICK_SIZE, 0, 0, 0);
	glTranslatef(BRICK_SIZE * 1.5f, 0.15f, -0.29f);
	glRotatef(90, 0, 1, 0);
	glRotatef(-60, 0, 0, 1);
	drawBrick(0, 0, 0, 0);
	glPopMatrix();
}

// z축으로 움직여야 하는 숫자를 포함하는 배열
GLfloat blow_temp[HOUSE_HEIGHT][HOUSE_SCALE];
// Y축으로 이동할 메모리
GLfloat blowY[HOUSE_HEIGHT][HOUSE_SCALE];
// Z축으로 이동할 메모리
GLfloat blowZ[HOUSE_HEIGHT][HOUSE_SCALE];
// 무너지면서 움직일 angle
GLfloat blowAngle[HOUSE_HEIGHT][HOUSE_SCALE];
// z축으로 움직일 때, 움직일 size를 지정해준다.
GLfloat moveSize = (BRICK_SIZE * HOUSE_SCALE) / (HOUSE_SCALE + HOUSE_HEIGHT);

// 사다리의 축을 움직이는 angle
GLfloat ladderAngleBlow = -30.0f;

void initBlow() {
	ladderAngleBlow = -30.0f;
	srand((unsigned int)time(NULL));
	for (int a = 0; a < HOUSE_HEIGHT; a++)
		for (int b = 0; b < HOUSE_SCALE; b++){
			GLfloat moveCount = ((HOUSE_SCALE + 1) - abs(b - HOUSE_SCALE / 2)) * a / 2.5f;
			blowZ[a][b] = 0.0f;
			blowY[a][b] = 0.0f;
			blow_temp[a][b] = moveCount * moveSize;
			if (a == 0)
				blow_temp[a][b] = 0.0f;
			else 
				blowAngle[a][b] = (GLfloat)(rand() % 800 / 10.0f - 40);
		}
}

void drawHouse(int isBlow) {
	GLfloat pushZ = BRICK_SIZE / 2.0f;

	for (int y = 0; y < HOUSE_HEIGHT; y++) {
		glPushMatrix();
		glTranslatef(0, BRICK_SIZE * y, 0);
		for (int i = 0; i < 4; i++) {
			glPushMatrix();
			// 앞면, 옆면, 뒷면에 따라 Matrix의 이동이 다르다
			GLfloat moveDirection = 1;
			// 앞면
			if (i == 0) {
				glTranslatef(BRICK_SIZE + BRICK_SIZE * (y % 2), 0, pushZ);
				moveDirection = -1;
			}
			// 왼쪽면
			else if (i == 1) {
				glRotatef(90.0f, 0, 1.0f, 0);
				glTranslatef(BRICK_SIZE - BRICK_SIZE * (y % 2), 0, pushZ);
			}
			// 오른쪽 면
			else if (i == 2) {
				glTranslatef(BRICK_X * HOUSE_SCALE + pushZ, 0, -BRICK_SIZE * (y % 2));
				glRotatef(90.0f, 0, 1.0f, 0);
				moveDirection = -1;
			}
			// 뒷면
			else
				glTranslatef(BRICK_SIZE + BRICK_SIZE * ((y + 1) % 2), 0, -BRICK_X * HOUSE_SCALE + pushZ);
			//glRotatef(90.0f, 0, 1.0f, 0);

			// 벽돌의 갯수만큼 반복하여 짓는다.
			for (int x = 0; x < HOUSE_SCALE; x++) {
				// 무너지는 것을 활성화 한다?
				if (isBlow) {
					if (blowY[y][x] < blow_temp[y][x])
						blowY[y][x] += 0.005f;
					if (blowZ[y][x] < blow_temp[y][x])
						blowZ[y][x] += moveSize / 10.0f;
					drawBrick(BRICK_X * x, -blowY[y][x], moveDirection * blowZ[y][x], blowAngle[y][x]);
				}
				else
					drawBrick(BRICK_X * x, 0, 0, 0);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
}

void drawShovel() {
	glPushMatrix();
	// 중심을 맞추는 이동
	glTranslatef(-0.1f, 0, 0.0f);

	// 손잡이 아랫부분
	glColor3f(249.0f / 255.0f, 127.0f / 255.0f, 81.0f / 255.0f);
	drawCylinder(0.02f, 0.02f, 0.2f);
	// 왼쪽 손잡이 45도
	glPushMatrix();
	glRotatef(45, 0, 0, 1);
	drawCylinder(0.02f, 0.02f, 0.15f);
	glPopMatrix();
	// 오른쪽 손잡이 45도
	glPushMatrix();
	glTranslatef(0.2f, 0, 0);
	glRotatef(135, 0, 0, 1);
	drawCylinder(0.02f, 0.02f, 0.15f);
	glPopMatrix();
	// 손잡이 기둥
	glTranslatef(0.1f, 0.1f, 0.0f);
	glRotatef(90.0f, 0, 0, 1);
	drawCylinder(0.02f, 0.02f, 0.4f);
	// 삽의 철부분
	glTranslatef(0.4f, 0, 0);
	glColor3f(75.0f / 255.0f, 75.0f / 255.0f, 75.0f / 255.0f);

	// 앞면
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, -0.05f);
	glVertex3f(0, 0.1f, 0);
	glVertex3f(0.15f, 0.1f, 0);
	glVertex3f(0.3f, 0.01f, 0);
	glVertex3f(0.3f, -0.01f, 0);
	glVertex3f(0.15f, -0.1f, 0);
	glVertex3f(0, -0.1f, 0);
	glEnd();
	// 뒷면
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, -0.06f);
	glVertex3f(0, -0.1f, -0.01f);
	glVertex3f(0.15f, -0.1f, -0.01f);
	glVertex3f(0.3f, -0.01f, -0.01f);
	glVertex3f(0.3f, 0.01f, -0.01f);
	glVertex3f(0.15f, 0.1f, -0.01f);
	glVertex3f(0, 0.1f, -0.01f);
	glEnd();
	// 아랫면
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, -0.06f);
	glVertex3f(0, 0.1f, -0.01f);
	glVertex3f(0, 0.1f, 0);
	glVertex3f(0, -0.1f, 0);
	glVertex3f(0, -0.1f, -0.01f);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, -0.1f, 0);
	glVertex3f(0, 0.1f, 0);
	glVertex3f(0, 0, -0.05f);
	glEnd();

	// 옆면
	glBegin(GL_QUADS);
	glVertex3f(0, 0.1f, 0);
	glVertex3f(0, 0.1f, -0.01f);
	glVertex3f(0.15f, 0.1f, -0.01f);
	glVertex3f(0.15f, 0.1f, 0);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(0.15f, 0.1f, 0);
	glVertex3f(0.15f, 0.1f, -0.01f);
	glVertex3f(0.3f, 0.01f, -0.01f);
	glVertex3f(0.3f, 0.01f, 0);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(0.3f, 0.01f, 0);
	glVertex3f(0.3f, 0.01f, -0.01f);
	glVertex3f(0.3f, -0.01f, -0.01f);
	glVertex3f(0.3f, -0.01f, 0);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(0.15f, -0.1f, 0);
	glVertex3f(0.15f, -0.1f, -0.01f);
	glVertex3f(0.3f, -0.01f, -0.01f);
	glVertex3f(0.3f, -0.01f, 0);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(0, -0.1f, 0);
	glVertex3f(0, -0.1f, -0.01f);
	glVertex3f(0.15f, -0.1f, -0.01f);
	glVertex3f(0.15f, -0.1f, 0);
	glEnd();

	glPopMatrix();
}

void drawChair() {
	glPushMatrix();
	// 중심을 맞추는 이동
	glTranslatef(-0.8f, 0.262f, 0.0f);

	glColor3f(205.0f / 255.0f, 97.0f / 255.0f, 51.0f / 255.0f);
	// 큰 통나무
	drawCylinder(0.1f, 0.1f, 1.6f);
	// 다리를 만들기 위함
	glPushMatrix();
	// 아래로 향하는 rotate
	glRotatef(-90, 0, 0, 1);
	// 첫 번째 다리
	glPushMatrix();
	glTranslatef(0.05f, 0.4f, 0.0f);
	glRotatef(45, 0, 1, 0);
	drawCylinder(0.05f, 0.03f, 0.3f);
	glRotatef(-90, 0, 1, 0);
	drawCylinder(0.05f, 0.03f, 0.3f);
	glPopMatrix();
	// 두  번째 다리
	glTranslatef(0.05f, 1.2f, 0.0f);
	glRotatef(45, 0, 1, 0);
	drawCylinder(0.05f, 0.03f, 0.3f);
	glRotatef(-90, 0, 1, 0);
	drawCylinder(0.05f, 0.03f, 0.3f);
	glPopMatrix();

	glPopMatrix();
}

void drawLadder(int blow) {
	glColor3f(200.0f / 255.0f, 200.0f / 255.0f, 220.0f / 255.0f);
	if (blow && ladderAngleBlow > -70) {
		ladderAngleBlow += -1.0f;
	}
	glPushMatrix();
	// 눕히기
	glRotatef(ladderAngleBlow, 1, 0, 0);
	// 기둥이 위로 솟아야 하므로 x축으로 늘어나는 cylinder 를 y로 늘어나게 하기 위함
	glRotatef(90, 0, 0, 1);
	// 기둥
	glPushMatrix();
	// 왼쪽 몸탱이
	glTranslatef(0, -LADDER_PLATFORM_WIDTH, 0);
	drawCylinder(0.035f, 0.035f, LADDER_HEIGHT);
	// 오른쪽 몸탱이
	glTranslatef(0, LADDER_PLATFORM_WIDTH * 2, 0);
	drawCylinder(0.035f, 0.035f, LADDER_HEIGHT);
	glPopMatrix();

	glPushMatrix();
	for (int i = 1; i < HOUSE_HEIGHT; i++) {
		glTranslatef(LADDER_PLATFORM_HEIGHT, 0, 0);
		glPushMatrix();
		glScalef(0.5, 4, 1);
		glutSolidCube(0.08f);
		glPopMatrix();
	}
	glPopMatrix();

	glPopMatrix();
}