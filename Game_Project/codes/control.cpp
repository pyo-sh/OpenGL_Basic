#include "control.h"

// 각도 계산을 위함
#define PI 3.14159265358979323846
#define CONVERT_PI PI / 180.0
// 점프했을 때 처음 올라간 거리
#define JUMPLIMIT 0.125f
// 중력
#define Gravity -(JUMPLIMIT / 32.0f)
// 힘
#define Force 0.007f
#define HalfForce Force / 2.0f

GLfloat camx = 0, camy = 1, camz = -15;
GLfloat cam2x = 0, cam2y = 1, cam2z = -20;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;
// 점프를 위해 원래 높이를 계산
GLfloat displayCamy = camy;
GLfloat displayCam2y = cam2y;

// 마우스 세팅
// --------------------------------------
// 마우스의 움직임 각도를 저장함으로써 다른 곳을 바라볼 수 있게

GLfloat xAngle = 0.0;
GLfloat yAngle = 0.0;

int stage = 0;
bool isStart = true;
bool isReady = false;
bool isFirst = true;
int readyAmount[4] = { 0, 0, 0, 0 };
GLfloat global_Ambient_value = 0.4f;

// 처음 세팅
void setStart() {
	camx = 0, camy = 2, camz = 0;
	cam2x = 0, cam2y = 2, cam2z = 10;
	cam_upx = 0, cam_upy = 1, cam_upz = 0;

	xAngle = 0.0;
	yAngle = 0.0;

	displayCamy = camy;
	displayCam2y = cam2y;
}

// Degree -> Radian 을 위한 함수
GLfloat getRadian(GLfloat angle) {
	return angle * CONVERT_PI;
}

// 마우스를 움직일 때 하는 계산
void moveMouseEvent(int x, int y) {
	if (1 <= stage && stage <= 2) {
		// glutWarpPointer로 인해서 생기는 mouse Event를 방지하기 위함
		if (x != _WINDOW_CENTER_WIDTH || y != _WINDOW_CENTER_HEIGHT) {
			GLfloat radianAngle, length;

			// 수직에 대한 Angle로 바라보는 y 좌표 지정
			GLfloat afterMove = yAngle + (_WINDOW_CENTER_HEIGHT - y) * 0.05f;
			// -70 ~ 70 사이 각도만을 저장하고 싶을 때
			if (-70.0f <= afterMove && afterMove <= 70.0f) {
				yAngle = afterMove;
			}
			radianAngle = getRadian(yAngle);

			cam2y = sin(radianAngle) * 0.15f + camy;
			length = cos(radianAngle) * 0.15f;


			// 수평에 대한 Angle로 바라보는 x, z 좌표지정
			xAngle += (_WINDOW_CENTER_WIDTH - x) * 0.05f;
			// -360 ~ 360 사이 각도만을 저장하고 싶을 때
			if (xAngle > 360.0f)
				xAngle -= 360.0f;
			else if (xAngle < -360.0f)
				xAngle += 360.0f;
			radianAngle = getRadian(xAngle);
			cam2x = sin(radianAngle) * length + camx;
			cam2z = cos(radianAngle) * length + camz;

			glutWarpPointer(_WINDOW_CENTER_WIDTH, _WINDOW_CENTER_HEIGHT);
			glutPostRedisplay();
		}
	}
}
// --------------------------------------

// 키보드 세팅
// --------------------------------------
bool isPressedW = false;
bool isPressedA = false;
bool isPressedS = false;
bool isPressedD = false;

bool canJump = true;
bool isJump = false;

void pressKeyboardEvent(unsigned char KeyPressed, int X, int Y) {


	if (stage == 0 || stage == 3) {
		switch (KeyPressed) {
		case 'w':
		case 's':
			isStart = !isStart;
			break;
		case 13:
		case 32:
			if (isStart) {
				isReady = true;
				// 마우스 커서가 보이지 않게 하기 위함

				glutSetCursor(GLUT_CURSOR_NONE);
			}
			else
				exit(0);
			break;
		case 27:
			exit(0);	break;
		}
	}
	else if (1 <= stage && stage <= 2) {
		switch (KeyPressed) {
		case 'w':
			isPressedW = true;
			printf("w, True\n");
			break;
		case 'a':
			isPressedA = true;
			printf("a, True\n");
			break;
		case 's':
			isPressedS = true;
			printf("s, True\n");
			break;
		case 'd':
			isPressedD = true;
			printf("d, True\n");
			break;
		case 32:
			if (!isJump && canJump) {
				isJump = true;
			}
			printf("jump\n", KeyPressed);
			break;
		case 27:
			exit(0);	break;
		}
	}
}

void offKeyboardEvent(unsigned char KeyPressed, int X, int Y) {
	if (1 <= stage && stage <= 2) {
		switch (KeyPressed) {
		case 'w':
			isPressedW = false;
			printf("w, False\n");
			break;
		case 'a':
			isPressedA = false;
			printf("a, False\n");
			break;
		case 's':
			isPressedS = false;
			printf("s, False\n");
			break;
		case 'd':
			isPressedD = false;
			printf("d, False\n");
			break;
		case 27:
			exit(0);	break;
		}
	}
}
// --------------------------------------
// 움직이는 바닥 {x, z, y}
GLfloat first_Floor[3] = { 16.0f, 73.0f, -3.0f };
int first_FloorAmount[3] = { 0, 0, 0 };
GLfloat second_Floor[3] = { 16.0f, 109.0f, -3.0f };
GLfloat third_Floor[3] = { 9.0f , 109.0f, -3.0f };

GLfloat* movingFloor[3] = { first_Floor , second_Floor, third_Floor };
int movingFloor_Length = 3;

// 벽을 판단하는 함수
#define CARE_SCREEN 0.5f
#define CARE_HEIGHT 2.0f

bool can_X_Go = true;
bool can_Z_Go = true;

GLfloat stage1_Object_X[5][2] = {
	{ 0.0f, 4.0f },
	{ -4.0f, 0.0f },
	{ 0.0f, 4.0f },
	{ -4.0f, 0.0f },
	{ 0.0f, 4.0f }
};
GLfloat stage1_Object_Z[5][2] = {
	{ 9.0f, 13.0f },
	{ 16.0f, 18.0f },
	{ 21.0f, 23.0f },
	{ 26.0f, 30.0f },
	{ 33.0f, 35.0f },
};

// stage 2 높이에 따라 저장
int stage2_Object_length = 27;
// x 의 범위 + y
GLfloat stage2_Object_X[27][3] = {
	{ 6.0f, 8.0f, -1.0f },
	{ 11.0f, 13.0f, -0.5f },
	{ 15.0f, 17.0f, 0.0f },
	{ 15.0f, 17.0f, -2.0f },
	{ 11.0f, 15.0f, -3.0f },

	{ 7.0f, 9.0f, -3.0f },
	{ 7.5f, 8.5f, -2.5f },
	{ -4.0f, 3.0f, -3.0f },
	{ -7.0f, -6.0f, -2.5f },

	{-11.0f, -9.0f, -2.0f },
	{-12.0f, -10.0f, -1.5f },
	{-11.0f, -9.0f, -1.0f },
	{-12.0f, -10.0f, -0.5f },
	{-11.0f, -9.0f, 0.0f },
	{-12.0f, -10.0f, 0.5f },

	{-17.0f, -15.0f, 1.0f },
	{-18.0f, -16.0f, 1.5f },
	{-17.0f, -15.0f, 2.0f },
	{-18.0f, -16.0f, 2.5f },
	{-17.0f, -15.0f, 3.0f },
	{-18.0f, -16.0f, 3.5f },

	{-17.0f, -15.0f, -3.0f },
	{-17.0f, -15.0f, -2.5f },
	{-17.0f, -15.0f, -2.0f },
	{-17.0f, -15.0f, -1.5f },
	{-12.0f, -10.0f, -1.0f },
	{ -7.0f, -5.0f, -0.5f }
};
// z의 범위 + y
GLfloat stage2_Object_Z[27][3] = {
	{ 56.0f, 58.0f, -1.0f },
	{ 57.0f, 59.0f, -0.5f },
	{ 60.0f, 62.0f, 0.0f },
	{ 68.0f, 70.0f, -2.0f },
	{ 108.0f, 110.0f, -3.0f},

	{ 88.0f, 90.0f, -3.0f },
	{76.0f, 86.0f, -2.5f },
	{76.0f, 77.0f, -3.0f },
	{76.0f, 86.0f, -2.5f },

	{79.0f, 81.0f, -2.0f },
	{74.0f, 76.0f, -1.5f },
	{69.0f, 71.0f, -1.0f },
	{64.0f, 66.0f, -0.5f },
	{59.0f, 61.0f, 0.0f },
	{54.0f, 56.0f, 0.5f },

	{54.0f, 56.0f, 1.0f },
	{59.0f, 61.0f, 1.5f },
	{64.0f, 66.0f, 2.0f },
	{69.0f, 71.0f, 2.5f },
	{74.0f, 76.0f, 3.0f },
	{79.0f, 81.0f, 3.5f },

	{ 92.0f, 94.0f, -3.0f },
	{ 97.0f, 99.0f, -2.5f },
	{ 102.0f, 104.0f, -2.0f },
	{ 107.0f, 109.0f, -1.5f },
	{ 106.0f, 108.0f, -1.0f },
	{ 105.0f, 107.0f, -0.5f }
};
// --------------------------------------
void canItGo_X(GLfloat x, GLfloat z, GLfloat height) {
	// 스테이지에 따라 벽을 달리할 생각이다.
	if (stage == 1) {
		bool is_In_Stage_X = -6.0f + CARE_SCREEN < x && x < 6.0f - CARE_SCREEN;
		// Stage 1 범위 안에 있을 때
		if (is_In_Stage_X) {			
			// 아래에 떨어졌을 때?
			if (height < 0.0f) {
				// 돌에 걸리는걸 막음 (걸리면 return)
				for (int i = 0; i < 5; i++) {
					if (stage1_Object_X[i][0] < x && x < stage1_Object_X[i][1] && stage1_Object_Z[i][0] < z && z < stage1_Object_Z[i][1]) {
						can_X_Go = false;
						return;
					}
				}
			}
			can_X_Go = true;
		}
		// 범위 밖일 경우
		else {
			can_X_Go = false;
		}
	}
	// --------------------------------------
	else if (stage == 2) {
		bool is_In_Wait_Z = (38.0f < z && z < 50.0f) || (110.0f < z && z < 122.0f);
		// 대기실
		if (is_In_Wait_Z) {
			// X 범위 안이면 true
			if (-6.0f + CARE_SCREEN < x && x < 6.0f - CARE_SCREEN)
				can_X_Go = true;
			// X 범위 밖이면 false
			else
				can_X_Go = false;
		}
		// 점프맵 안에서
		else {
			bool is_In_Stage_X = -20.0f + CARE_SCREEN < x && x < 20.0f - CARE_SCREEN;
			if (is_In_Stage_X) {
				// 이제 돌을 신경쓰자
				for (int i = 0; i < stage2_Object_length; i++) {
					if(height < stage2_Object_X[i][2])
						if (stage2_Object_X[i][0] < x && x < stage2_Object_X[i][1] && stage2_Object_Z[i][0] < z && z < stage2_Object_Z[i][1]) {
							can_X_Go = false;
							return;
						}
				}
				can_X_Go = true;
			}
			// 스테이지 밖이면 못가~
			else {
				can_X_Go = false;
			}
		}
	}
	// --------------------------------------
}
void canItGo_Z(GLfloat x, GLfloat z, GLfloat height) {
	// 스테이지에 따라 벽을 달리할 생각이다.
	if (stage == 1) {
		bool is_In_Stage_Z = -6.0f + CARE_SCREEN < z && z < 50.0f - CARE_SCREEN;
		// Stage 1 범위 안에 있을 때
		if (is_In_Stage_Z) {
			// Stage 2로 넘어감
			if (44.0f < z)
				stage = 2;
			// 아래에 떨어졌을 때?
			if (height < 0.0f) {
				// 돌에 걸리는걸 막음 (걸리면 return)
				for (int i = 0; i < 5; i++) {
					if (stage1_Object_X[i][0] < x && x < stage1_Object_X[i][1] && stage1_Object_Z[i][0] < z && z < stage1_Object_Z[i][1]) {
						can_Z_Go = false;
						return;
					}
				}
				// 돌에 안걸리면 아래에서 스테이지 밖으로 나가는걸 막음
				if (6.0f > z || z > 38.0f) {
					can_Z_Go = false;
					return;
				}
			}
			// 그냥 안에 있을 땐 움직일 수 있어야 함
			can_Z_Go = true;
		}
		// 범위 밖일 경우
		else {
			can_Z_Go = false;
		}
	}
	// --------------------------------------
	else if (stage == 2) {
		bool is_In_Stage_Z = 38.0f < z && z < 122.0f;
		// 범위 안이면
		if (is_In_Stage_Z) {
			// Stage 1으로 다시 돌아갈 때
			if (44.0f > z)
				stage = 1;
			// Stage 3으로 넘어감
			else if (116.0f < z)
				stage = 3;

			// 점프맵 안에서 벽을 뚫으려 할 때
			if (-6.0f + CARE_SCREEN > x || x > 6.0f - CARE_SCREEN) {
				if (!(50.0f + CARE_SCREEN < z && z < 110.0f - CARE_SCREEN)) {
					can_Z_Go = false;
					return;
				}
			}
			// 점프맵 아래에서 벽을 못뚫게
			else {
				if(height < 0.0f)
					if(!(50.0f + CARE_SCREEN < z && z < 110.0f - CARE_SCREEN)) {
						can_Z_Go = false;
						return;
					}
			}

			// 이제 돌을 신경쓰자
			for (int i = 0; i < stage2_Object_length; i++) {
				if (height < stage2_Object_Z[i][2])
					if (stage2_Object_X[i][0] < x && x < stage2_Object_X[i][1] && stage2_Object_Z[i][0] < z && z < stage2_Object_Z[i][1]) {
						can_Z_Go = false;
						return;
					}
			}

			can_Z_Go = true;
		}
		// 범위 밖일 경우
		else {
			can_Z_Go = false;
		}
	}
	// --------------------------------------
}
bool goDown(GLfloat x, GLfloat z, GLfloat y, GLfloat beforeY) {
	// 스테이지 1일 때
	if (stage == 1) {
		// 떨어질 수 있는 곳에 접근하면
		if (6.0f < z && z < 38.0f) {
			// stage1은 y가 일정하다
			if (y >= 0.0f) {
				for (int i = 0; i < 5; i++) {
					if (stage1_Object_X[i][0] < x && x < stage1_Object_X[i][1] && stage1_Object_Z[i][0] < z && z < stage1_Object_Z[i][1])
						return false;
				}
			}
			return true;
		}
		// 그냥 스테이지에선 가만히 있자
		else
			return false;
	}
	// 스테이지 2일 때
	else if (stage == 2) {
		// 떨어질 수 있는 곳에 접근하면
		if (50.0f < z && z < 110.0f) {
			for (int i = 0; i < stage2_Object_length; i++) {
				if (stage2_Object_X[i][2] <= y && beforeY < stage2_Object_X[i][2])
					if (stage2_Object_X[i][0] < x && x < stage2_Object_X[i][1] && stage2_Object_Z[i][0] < z && z < stage2_Object_Z[i][1]) {
						camy = stage2_Object_X[i][2] + CARE_HEIGHT;
						GLfloat radianAngle = getRadian(yAngle);
						cam2y = sin(radianAngle) * 0.15f + camy;
						return false;
					}
			}
			// 움직이는 돌 고려
			for (int i = 0; i < movingFloor_Length; i++) {
				if (movingFloor[i][0] - 1.0f < x && x < movingFloor[i][0] + 1.0f && movingFloor[i][1] - 1.0f < z && z < movingFloor[i][1] + 1.0f)
					if (movingFloor[i][2] <= y && beforeY < movingFloor[i][2]) {
						camy = movingFloor[i][2] + CARE_HEIGHT;
						GLfloat radianAngle = getRadian(yAngle);
						cam2y = sin(radianAngle) * 0.15f + camy;
						return false;
					}
			}
			return true;
		}
		// 그냥 스테이지에선 가만히 있자
		else {
			camy = CARE_HEIGHT;
			GLfloat radianAngle = getRadian(yAngle);
			cam2y = sin(radianAngle) * 0.15f + camy;
			return false;
		}
	}
	// 혹시 다른 스테이지 설정 시 default
	else
		return false;
}
// 점프하고 있을 때 확인
bool checkStay(GLfloat x, GLfloat z, GLfloat nowY, GLfloat afterY) {
	if (stage == 1) {
		for (int i = 0; i < 5; i++) {
			if (stage1_Object_X[i][0] < x && x < stage1_Object_X[i][1] && stage1_Object_Z[i][0] < z && z < stage1_Object_Z[i][1]) {
				if (0.0f <= nowY && afterY < 0.0f)
					return true;
			}
		}
		return false;
	}
	else if (stage == 2) {
		// 스테이지에서 높이 고려
		if (-6.0f < x && x < 6.0f && ((38.0f < z && z < 50.0f) || (110.0f < z && z < 122.0f)))
			if (0.0f <= nowY && afterY < 0.0f) {
				camy = 0.0 + CARE_HEIGHT;
				GLfloat radianAngle = getRadian(yAngle);
				cam2y = sin(radianAngle) * 0.15f + camy;
				return true;
			}
		// 돌에서 높이 고려
		for (int i = 0; i < stage2_Object_length; i++) {
			if (stage2_Object_X[i][0] < x && x < stage2_Object_X[i][1] && stage2_Object_Z[i][0] < z && z < stage2_Object_Z[i][1])
				if (stage2_Object_X[i][2] <= nowY && afterY < stage2_Object_X[i][2]) {
					camy = stage2_Object_X[i][2] + CARE_HEIGHT;
					GLfloat radianAngle = getRadian(yAngle);
					cam2y = sin(radianAngle) * 0.15f + camy;
					return true;
				}
		}
		// 움직이는 돌 고려
		for (int i = 0; i < movingFloor_Length; i++) {
			if (movingFloor[i][0] - 1.0f < x && x < movingFloor[i][0] + 1.0f && movingFloor[i][1] - 1.0f < z && z < movingFloor[i][1] + 1.0f)
				if (movingFloor[i][2] <= nowY && afterY < movingFloor[i][2]) {
					camy = movingFloor[i][2] + CARE_HEIGHT;
					GLfloat radianAngle = getRadian(yAngle);
					cam2y = sin(radianAngle) * 0.15f + camy;
					return true;
				}
		}
		return false;
	}
	else
		return false;
}
// --------------------------------------

// 타이머 구현
// --------------------------------------
// 손의 움직임
GLfloat left_hand_above = 0.0f;
GLfloat left_hand_side = 0.0f;
GLfloat right_hand_above = 0.0f;
GLfloat right_hand_side = 0.0f;
	// 숨 쉴때 움직이는 각도를 저장 (deltaTime 때문에 배열로)
int breathAmount[4] = { 0, 0, 0, 0 };
	// 뛰어갈 때 움직이는 각도를 저장
int runAmount[5] = { 0, 0, 0, 0, 0 };

// 점프했을 때 움직이는 각도를 저장
int jumpAmount[5] = { 0, 0, 0, 0, 0 };
// 점프했을 때 올라가는 높이
GLfloat userHeight = 0.0f;

int lastTime = glutGet(GLUT_ELAPSED_TIME);
void MyTimer(int value) {
	// 프레임에 따른 움직이는 속도 조정
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = (currentTime - lastTime);
	lastTime = currentTime;

	// 인트로
	if (stage == 0) {
		if (isReady) {
			readyAmount[0] += deltaTime;
			if (readyAmount[0] >= 1600) {
				readyAmount[1] += readyAmount[0] - 1600;
				readyAmount[0] = 1599;
			}
			if (readyAmount[1] >= 1000) {
				readyAmount[2] += readyAmount[1] - 1000;
				readyAmount[1] = 999;
			}
			if (readyAmount[2] > 0) {
				setStart();
				stage = 1;
			}
			global_Ambient_value = (799 - readyAmount[0]) * 0.00625f;
		}
	}
	// 처음 델타 타임이 - 여서 오류가 났다.
	if (deltaTime > 0 && 0 < stage && stage < 3)
	{
		if (isFirst) {
			readyAmount[2] += deltaTime;
			if (readyAmount[2] >= 1600) {
				readyAmount[3] += readyAmount[2] - 1600;
				readyAmount[2] = 1599;
			}
			if(readyAmount[2] < 800)
				global_Ambient_value = (readyAmount[2] - 799) * 0.00625f;
			else
				global_Ambient_value = readyAmount[2] * 0.00025f;
			if (readyAmount[3] > 0) {
				readyAmount[0] = 0;
				readyAmount[1] = 0;
				readyAmount[2] = 0;
				readyAmount[3] = 0;
				isFirst = false;
			}
		}
		else {
			// 보는 방향에 따라 움직이는 x, z 축이 다르다

			GLfloat radianAngle = getRadian(xAngle);
			// xAngle 각도에 따른 sin, cos 값 저장
			GLfloat angleSin = sin(radianAngle) * deltaTime;
			GLfloat angleCos = cos(radianAngle) * deltaTime;


			// 대각선 이동할 때 2배가 되므로 2배를 감소해야 한다.
			bool isOnlyFront = isPressedA ^ isPressedD;
			bool isOnlySide = isPressedW ^ isPressedS;

			// 최종적으로 움직일 힘
			// 앞 뒤로 움직일 때 주는 힘 (Z 축은 cos, X 축은 sin)
			GLfloat frontForceZ = 0.0f;
			GLfloat frontForceX = 0.0f;
			// 양 쪽으로 움직일 때 주는 힘 (Z 축은 sin, X 축은 cos)
			GLfloat sideForceZ = 0.0f;
			GLfloat sideForceX = 0.0f;

			// 앞으로 가는 키를 눌렀을 때
			if (isPressedW) {
				frontForceZ += isOnlyFront ? HalfForce : Force;
				frontForceX += isOnlyFront ? HalfForce : Force;
			}
			// 뒤로 가는 키를 눌렀을 때
			if (isPressedS) {
				frontForceZ += -(isOnlyFront ? HalfForce : Force);
				frontForceX += -(isOnlyFront ? HalfForce : Force);
			}
			// 왼쪽으로 가는 키를 눌렀을 때
			if (isPressedA) {
				sideForceZ += -(isOnlySide ? HalfForce : Force);
				sideForceX += isOnlySide ? HalfForce : Force;
			}
			// 오른쪽으로 가는 키를 눌렀을 때
			if (isPressedD) {
				sideForceZ += isOnlySide ? HalfForce : Force;
				sideForceX += -(isOnlySide ? HalfForce : Force);
			}

			// 손 움직임
			// 점프키 클릭 시 (무빙까지 포함)
			if (isJump) {
				jumpAmount[0] += deltaTime;

				int nextAmount = 0;

				if (jumpAmount[0] > 200) {
					nextAmount = jumpAmount[0] - 200;
					jumpAmount[0] = 199;
				}
				else	nextAmount = 0;
				jumpAmount[1] += nextAmount;

				if (jumpAmount[1] > 200) {
					nextAmount = jumpAmount[1] - 200;
					jumpAmount[1] = 199;
				}
				else	nextAmount = 0;
				jumpAmount[2] += nextAmount;

				if (jumpAmount[2] > 200) {
					nextAmount = jumpAmount[2] - 200;
					jumpAmount[2] = 199;
				}
				else	nextAmount = 0;

				jumpAmount[3] += nextAmount;
				if (jumpAmount[3] > 200) {
					nextAmount = jumpAmount[3] - 200;
					jumpAmount[3] = 199;
				}
				else nextAmount = 0;

				jumpAmount[4] += nextAmount;

				if (jumpAmount[4] > 0) {
					jumpAmount[0] = 0;
					jumpAmount[1] = 0;
					jumpAmount[2] = 0;
					jumpAmount[3] = 0;
					jumpAmount[4] = 0;
					isJump = false;
				}

				userHeight = (jumpAmount[0] - jumpAmount[3]) * 0.004f + (jumpAmount[1] - jumpAmount[2]) * 0.002f;

				left_hand_above = (jumpAmount[0] - 75) * 0.015f + jumpAmount[1] * 0.01f + jumpAmount[2] * 0.005f
					+ (125 - jumpAmount[3]) * (125 - jumpAmount[3] < 0 ? 0.1f : 0.005f);
				left_hand_side = 0.0f;
				right_hand_above = left_hand_above;
				right_hand_side = 0.0f;
			}

			// 달리고 있을 때
			else if (isPressedA || isPressedD || isPressedW || isPressedS) {
				// 손 움직임
				int nextAmount = 0;
				if (runAmount[4] > 0) {
					runAmount[0] = breathAmount[3];
					runAmount[1] = 0;
					runAmount[2] = 0;
					runAmount[3] = 0;
					runAmount[4] = 0;
				}

				runAmount[0] += deltaTime;
				if (runAmount[0] > 125) {
					nextAmount = runAmount[0] - 125;
					runAmount[0] = 124;
				}
				else	nextAmount = 0;

				runAmount[1] += nextAmount;
				if (runAmount[1] > 125) {
					nextAmount = runAmount[1] - 125;
					runAmount[1] = 124;
				}
				else nextAmount = 0;

				runAmount[2] += nextAmount;
				if (runAmount[2] > 125) {
					nextAmount = runAmount[2] - 125;
					runAmount[2] = 124;
				}
				else	nextAmount = 0;

				runAmount[3] += nextAmount;
				if (runAmount[3] > 125) {
					nextAmount = runAmount[3] - 125;
					runAmount[3] = 124;
				}
				else	nextAmount = 0;

				runAmount[4] += nextAmount;

				left_hand_above = (runAmount[0] + runAmount[1]) * 0.008f + runAmount[2] * -0.016f - 0.4f;
				left_hand_side = (runAmount[0] + runAmount[1]) * -0.006f + runAmount[2] * 0.009f + runAmount[3] * 0.003 + 1.5f;
				right_hand_above = (runAmount[0] + runAmount[2]) * -0.008f + (runAmount[1] + runAmount[3]) * 0.008f - 0.4f;
				right_hand_side = (runAmount[0] + runAmount[1]) * -0.008f + (runAmount[2] + runAmount[2]) * 0.008 - 1.5f;;
			}

			// 평소 손 움직임
			else {
				// 손 움직임
				int nextAmount = 0;
				if (breathAmount[3] > 0) {
					breathAmount[0] = breathAmount[3];
					breathAmount[1] = 0;
					breathAmount[2] = 0;
					breathAmount[3] = 0;
				}

				breathAmount[0] += deltaTime;
				if (breathAmount[0] > 900) {
					nextAmount = breathAmount[0] - 900;
					breathAmount[0] = 899;
				}
				else
					nextAmount = 0;
				breathAmount[1] += nextAmount;
				if (breathAmount[1] > 450) {
					nextAmount = breathAmount[1] - 450;
					breathAmount[1] = 449;
				}
				else
					nextAmount = 0;
				breathAmount[2] += nextAmount;
				if (breathAmount[2] > 900) {
					nextAmount = breathAmount[2] - 900;
					breathAmount[2] = 899;
				}
				else
					nextAmount = 0;
				breathAmount[3] += nextAmount;

				left_hand_above = breathAmount[0] * -0.0006f + breathAmount[1] * 0.0004f + breathAmount[2] * 0.0004;
				left_hand_side = breathAmount[0] * 0.0004f + breathAmount[1] * 0.0004f + breathAmount[2] * -0.0006;
				right_hand_above = -left_hand_above;
				right_hand_side = left_hand_side;
			}

			GLfloat frontSpeed = angleCos * frontForceZ + angleSin * sideForceZ;
			GLfloat sideSpeed = angleSin * frontForceX + angleCos * sideForceX;


			// can_X_Go 와 can_Z_Go 조정
			canItGo_X(camx + sideSpeed, camz + frontSpeed, displayCamy - CARE_HEIGHT);
			canItGo_Z(camx + sideSpeed, camz + frontSpeed, displayCamy - CARE_HEIGHT);
			if (can_Z_Go) {
				camz += frontSpeed;
				cam2z += frontSpeed;
			}
			if (can_X_Go) {
				camx += sideSpeed;
				cam2x += sideSpeed;
			}

			// 움직이는 바닥은 계속 움직임
			// { 16.0f, 73.0f, -3.0f }
			first_FloorAmount[0] += deltaTime;
			if (first_FloorAmount[0] >= 1800) {
				first_FloorAmount[1] += first_FloorAmount[0] - 1800;
				first_FloorAmount[0] = 1799;
			}
			if (first_FloorAmount[1] >= 1800) {
				first_FloorAmount[2] += first_FloorAmount[1] - 1800;
				first_FloorAmount[1] = 1799;
			}
			if (first_FloorAmount[2] > 0) {
				first_FloorAmount[0] = first_FloorAmount[2];
				first_FloorAmount[1] = 0;
				first_FloorAmount[2] = 0;
			}
			GLfloat floor_moveAmount[3];
			floor_moveAmount[0] = first_FloorAmount[0] * 0.01f + first_FloorAmount[1] * -0.01f - (first_Floor[1] - 73.0f);
			floor_moveAmount[1] = -floor_moveAmount[0];
			floor_moveAmount[2] = floor_moveAmount[1];
			first_Floor[1] += floor_moveAmount[0];
			second_Floor[1] += floor_moveAmount[1];
			third_Floor[1] += floor_moveAmount[2];

			for (int i = 0; i < movingFloor_Length; i++) {
				if (movingFloor[i][0] - 1.0f < camx && camx < movingFloor[i][0] + 1.0f && movingFloor[i][1] - 1.0f < camz && camz < movingFloor[i][1] + 1.0f)
					if (movingFloor[i][2] - 0.3f <= displayCamy - CARE_HEIGHT && displayCamy - CARE_HEIGHT < movingFloor[i][2] + 0.3f) {
						camz += floor_moveAmount[i];
						cam2z += floor_moveAmount[i];
					}
			}

			// 점프를 뛰고 있을 때
			if (isJump) {
				// 뛴 높이에 정착을 할 수 있으면? 점프를 멈추고 해당 높이에 멈춤
				if (checkStay(camx, camz, camy - CARE_HEIGHT + userHeight, camy - CARE_HEIGHT)) {
					jumpAmount[0] = 0;
					jumpAmount[1] = 0;
					jumpAmount[2] = 0;
					jumpAmount[3] = 0;
					jumpAmount[4] = 0;
					isJump = false;
				}
				// 아니면 점프 계속~
				else {
					displayCamy = camy + userHeight;
					displayCam2y = cam2y + userHeight;
				}
			}
			// 점프를 안하고 있을 때
			else {
				GLfloat downAmount = -0.01f * deltaTime;
				// 떨어져야 하는 곳인지 판단하고 계속 떨어진다
				if (goDown(camx, camz, camy - CARE_HEIGHT, camy - CARE_HEIGHT + downAmount)) {
					camy -= 0.004f * deltaTime;
					cam2y -= 0.004f * deltaTime;
					canJump = false;
					displayCamy = camy + userHeight;
					displayCam2y = cam2y + userHeight;
				}
				else {
					canJump = true;
					displayCamy = camy + userHeight;
					displayCam2y = cam2y + userHeight;
				}
				// 처음으로 돌아갈 때
				if (camy < -6.0f) {
					if (stage == 1) {
						camx = 0, camy = 2, camz = 0;
						cam2x = 0, cam2y = 2, cam2z = 2;
						xAngle = 0.0;
						yAngle = 0.0;
					}
					else if (stage == 2) { // 44 46 , 111 113
						camx = 0.0f, camy = 2.0f, camz = 111;
						cam2x = 0.0f, cam2y = 2.0f, cam2z = 113;
						xAngle = 0.0f;
						yAngle = 0.0f;
					}
				}
			}
		}
	}
	// 아웃트로
	if (stage == 3) {
		camx = 0, camy = 0.5, camz = -15;
		cam2x = 0, cam2y = 0.5, cam2z = -20;
		cam_upx = 0, cam_upy = 1, cam_upz = 0;
		readyAmount[0] += deltaTime;
		if (readyAmount[0] >= 1000) {
			readyAmount[1] += readyAmount[0] - 1000;
			readyAmount[0] = 999;
		}
		if (readyAmount[1] >= 5000) {
			readyAmount[2] += readyAmount[1] - 5000;
			readyAmount[1] = 4999;
		}
		if (readyAmount[0] < 800)
			global_Ambient_value = (readyAmount[0] - 800) * 0.00625f;
		else
			global_Ambient_value = readyAmount[0] * 0.002f;
		if (readyAmount[2] > 0) {
			setStart();
			stage = 0;
			isStart = true;
			isReady = false;
			isFirst = true;
			camx = 0, camy = 1, camz = -15;
			cam2x = 0, cam2y = 1, cam2z = -20;
			cam_upx = 0, cam_upy = 1, cam_upz = 0;
			// 점프를 위해 원래 높이를 계산
			displayCamy = camy;
			displayCam2y = cam2y;
			readyAmount[0] = 0;
			readyAmount[1] = 0;
			readyAmount[2] = 0;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(5, MyTimer, 1);
}
// --------------------------------------