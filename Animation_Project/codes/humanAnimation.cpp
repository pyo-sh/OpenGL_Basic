#include "human.h"

// 몸 전체의 움직임
// 왼쪽 (+), 오른쪽쪽(-) 회전
GLfloat angle_body_all = 0.0f;
// 위 아래 움직임 y 좌표
GLfloat move_body_all = -0.15f;

// 몸체 상의 부분의 움직임
// 몸을 왼쪽(+), 오른쪽(-)으로 뒤틀음 (90 ~ -90)
GLfloat angle_body_side = 0.0f;
// 몸을 앞(+), 뒤(-)로 기울임 (90 ~ -90)
GLfloat angle_body_axisForth = 15.0f;
// 몸을 오(+), 왼(-) 로 기울임 (40 ~ -40)
GLfloat angle_body_axisSide = 0.0f;

// 얼굴
// 앞(+), 뒤(-)로 향하는 고개 (50 ~ -50)
GLfloat angle_head_forth = 0.0f;
// 오(+), 왼(-)로 향하는 고개 (50 ~ -50)
GLfloat angle_head_side = 0.0f;
// 위(-), 아래(+)로 움직이는 눈썹 (40 ~ 60) 
GLfloat move_left_faceEyebrow = 45.0f;
GLfloat move_right_faceEyebrow = 45.0f;
// 안쪽이 아래로(+), 바깥쪽이 아래로(-) 기울인 눈썹 (50 ~ -50)
GLfloat angle_left_faceEyebrow = 0.0f;
GLfloat angle_right_faceEyebrow = 0.0f;
// 눈물이 있는지
int isTear = 0;
GLfloat move_Tear = 0.0f;

// 윗 팔의 움직임
// 위(+), 아래(-)로 향하는 angle (-75 ~ 85)
GLfloat angle_left_upperArm_above = -60.0f;
GLfloat angle_right_upperArm_above = 50.0f;
// 앞(+), 뒤(-)로 향하는 angle
GLfloat angle_left_upperArm_forth = 0.0f;
GLfloat angle_right_upperArm_forth = 20.0f;
// 아랫 팔의 움직임
// 위(+), 아래(-)로 향하는 angle
GLfloat angle_left_lowerArm_above = 0.0f;
GLfloat angle_right_lowerArm_above = 110.0f;
// 앞(+), 뒤(-)로 향하는 angle (130 ~ -130)
GLfloat angle_left_lowerArm_forth = 0.0f;
GLfloat angle_right_lowerArm_forth = 0.0f;

// 윗 다리의 움직임
// 앞(+), 뒤(-)로 향하는 angle (-90 ~ 90)
GLfloat angle_left_upperLeg_forth = 60.0f;
GLfloat angle_right_upperLeg_forth = 60.0f;
// 양 옆으로 향하는 angle 바깥쪽(+), 안쪽 (-) (0 ~ 80)
GLfloat angle_left_upperLeg_side = 20.0f;
GLfloat angle_right_upperLeg_side = 20.0f;
// 아랫 다리의 움직임
// 뒤(+)로 움직이는 angle (0 ~ 100)
GLfloat angle_left_lowerLeg_back = 60.0f;
GLfloat angle_right_lowerLeg_back = 60.0f;

// 걷는 모션을 구현하는 함수 (count 가 200인 작동)
// 다리만 15도씩 꺾어주고, 팔은 위만 -60
GLfloat walk[9] = {};
void walking(int count) {
	if (count < 50) {
		walk[0] = 0.001f; walk[1] = 0.75f; walk[2] = 0.75f; walk[3] = -0.75f; walk[4] = 0.0f;
		walk[5] = -0.4f; walk[6] = 0.2f; walk[7] = 0.4f; walk[8] = 0.4f;
	}
	else if (count < 100) {
		walk[0] = -0.001f; walk[1] = -0.75f; walk[2] = -0.75f; walk[3] = 0.75f; walk[4] = 0.0f;
		walk[5] = 0.4f; walk[6] = -0.2f; walk[7] = -0.4f; walk[8] = -0.4f;
	}
	else if (count < 150) {
		walk[0] = 0.001f; walk[1] = -0.75f; walk[2] = -0.0f; walk[3] = 0.75f; walk[4] = 0.75f;
		walk[5] = 0.4f; walk[6] = 0.4f; walk[7] = -0.4f; walk[8] = 0.2f;
	}
	else {
		walk[0] = -0.001f; walk[1] = 0.75f; walk[2] = -0.0f; walk[3] = -0.75f; walk[4] = -0.75f;
		walk[5] = -0.4f; walk[6] = -0.4f; walk[7] = 0.4f; walk[8] = -0.2f;
	}
	move_body_all += walk[0];
	angle_left_upperLeg_forth += walk[1];
	angle_left_lowerLeg_back += walk[2];
	angle_right_upperLeg_forth += walk[3];
	angle_right_lowerLeg_back += walk[4];

	angle_left_upperArm_forth += walk[5];
	angle_left_lowerArm_forth += walk[6];
	angle_right_upperArm_forth += walk[7];
	angle_right_lowerArm_forth += walk[8];
}
// 벽돌을 들고 다리만 걷는 모션
GLfloat legWalk[5] = {};
void legWalking(int count) {
	if (count < 50) {
		walk[0] = 0.001f; walk[1] = 0.75f; walk[2] = 0.75f; walk[3] = -0.75f; walk[4] = 0.0f;
	}
	else if (count < 100) {
		walk[0] = -0.001f; walk[1] = -0.75f; walk[2] = -0.75f; walk[3] = 0.75f; walk[4] = 0.0f;
	}
	else if (count < 150) {
		walk[0] = 0.001f; walk[1] = -0.75f; walk[2] = -0.0f; walk[3] = 0.75f; walk[4] = 0.75f;
	}
	else {
		walk[0] = -0.001f; walk[1] = 0.75f; walk[2] = -0.0f; walk[3] = -0.75f; walk[4] = -0.75f;
	}
	move_body_all += walk[0];
	angle_left_upperLeg_forth += walk[1];
	angle_left_lowerLeg_back += walk[2];
	angle_right_upperLeg_forth += walk[3];
	angle_right_lowerLeg_back += walk[4];
}

GLfloat ledderUp[4] = {};
void ledderUping(int count) {
	if (count < 50) {
		ledderUp[0] = 0.8f;
		ledderUp[1] = -0.15f;
		ledderUp[2] = 0.8f;
		ledderUp[3] = 0.0f;
	}
	else if (count < 100) {
		ledderUp[0] = -0.8f;
		ledderUp[1] = 0.15f;
		ledderUp[2] = -0.8f;
		ledderUp[3] = 0.0f;
	}
	else if (count < 150) {
		ledderUp[0] = -0.15f;
		ledderUp[1] = 0.8f;
		ledderUp[2] = 0.0f;
		ledderUp[3] = 0.8f;
	}
	else if (count < 200) {
		ledderUp[0] = 0.15f;
		ledderUp[1] = -0.8f;
		ledderUp[2] = 0.0f;
		ledderUp[3] = -0.8f;
	}
	angle_left_upperLeg_forth += ledderUp[0];
	angle_right_upperLeg_forth += ledderUp[1];
	angle_left_lowerLeg_back += ledderUp[2];
	angle_right_lowerLeg_back += ledderUp[3];
}

GLfloat strokeHead[3] = {};

void humanAnimation(int count) {
	// 맨 처음 모션
	if (count < 200) {
		// 머리 긁기
		if (count < 100) {
			strokeHead[0] = 0.2f; strokeHead[1] = -0.25f; strokeHead[2] = 0.05f;
		}
		else if (count < 200) {
			strokeHead[0] = -0.2f; strokeHead[1] = +0.25f; strokeHead[2] = -0.05f;
		}
		angle_right_upperArm_above += strokeHead[0];
		angle_right_lowerArm_above += strokeHead[1];
		angle_right_lowerArm_forth += strokeHead[2];
	}
	// 통나무에서 일어나기 위한 모션
	else if (count < 400) {
		// 팔 내리기
		if (count < 300) {
			angle_right_upperArm_above -= 1.1f;
			angle_right_upperArm_forth -= 0.2f;
			angle_right_lowerArm_above -= 1.1f;
		}
		// 일어나기
		else if (count < 400) {
			angle_left_upperLeg_forth -= 0.6f;
			angle_right_upperLeg_forth -= 0.6f;
			angle_left_upperLeg_side -= 0.2f;
			angle_right_upperLeg_side -= 0.2f;
			angle_left_lowerLeg_back -= 0.6f;
			angle_right_lowerLeg_back -= 0.6f;
			move_body_all += 0.0015f;
			angle_body_axisForth -= 0.15f;
			angle_left_upperArm_above -= 0.15f;
			angle_right_upperArm_above -= 0.15f;
		}
	}
	// 걸어가는 자세잡기
	else if (count < 450) {
		// 다리 10도씩
		angle_left_upperLeg_forth += 0.2f;
		angle_right_upperLeg_forth += 0.2f;
		angle_left_lowerLeg_back += 0.2f;
		angle_right_lowerLeg_back += 0.2f;
		// 0.175 까지
		move_body_all -= 0.0035;
	}
	else if (count < 650) {
		walking(count - 450);
	}
	// 옆으로 돌기
	else if (count < 700) {
		angle_body_all -= 1.8f;
	}
	else if (count < 900) {
		walking(count - 700);
	}
	// 허리 숙이기
	else if (count < 950) {
		// 전체 몸의 움직임
		move_body_all += -0.003f;
		angle_body_axisForth += 0.6f;
		// 다리의 움직임
		angle_left_upperLeg_forth += 0.3f;
		angle_right_upperLeg_forth += 0.3f;

		angle_left_upperLeg_side += 0.4f;
		angle_right_upperLeg_side += 0.4f;

		angle_left_lowerLeg_back += 0.3f;
		angle_right_lowerLeg_back += 0.3f;
		// 팔의 움직임
		angle_left_upperArm_above += 1.0f;
		angle_right_upperArm_above += 1.0f;

		angle_left_upperArm_forth += 1.0f;
		angle_right_upperArm_forth += 1.0f;

		angle_left_lowerArm_above += -0.5f;
		angle_right_lowerArm_above += -0.5f;

		angle_left_lowerArm_forth += 0.6f;
		angle_right_lowerArm_forth += 0.6f;
	}
	// 블럭 들기
	else if (count < 1050) {
		// 전체 몸의 움직임
		move_body_all += 0.0015f;
		angle_body_axisForth += -0.3f;
		// 팔의 움직임
		angle_left_upperArm_above += -0.3f;
		angle_right_upperArm_above += -0.3f;

		angle_left_upperArm_forth += -0.1f;
		angle_right_upperArm_forth += -0.1f;

		angle_left_lowerArm_forth += 0.3f;
		angle_right_lowerArm_forth += 0.3f;

		// 다리의 움직임
		angle_left_upperLeg_forth += -0.15f;
		angle_right_upperLeg_forth += -0.15f;

		angle_left_upperLeg_side += -0.2f;
		angle_right_upperLeg_side += -0.2f;

		angle_left_lowerLeg_back += -0.15f;
		angle_right_lowerLeg_back += -0.15f;

		// 눈썹
		// 위(+), 아래(-)로 움직이는 눈썹 (40 ~ 60) 
		move_left_faceEyebrow += 0.001f;
		move_right_faceEyebrow += 0.001f;
		// 안쪽이 아래로(+), 바깥쪽이 아래로(-) 기울인 눈썹 (50 ~ -50)
		angle_left_faceEyebrow += 0.05f;
		angle_right_faceEyebrow += 0.05f;
	}
	// 벽돌을 어깨 위로 올리는 모션
	else if (count < 1150) {
		angle_left_upperArm_above += 0.55f;
		angle_right_upperArm_above += 0.3f;

		angle_left_upperArm_forth += -0.4f;
		angle_right_upperArm_forth += 0.7f;

		if (count < 1080) {
			angle_left_lowerArm_above += 3.5f;
		}
		angle_right_lowerArm_above += -0.1f;

		angle_left_lowerArm_forth += -0.6f;
		angle_right_lowerArm_forth += 0.2f;
	}
	// 눈썹 재위치
	else if (count < 1200) {
		move_left_faceEyebrow += -0.001f;
		move_right_faceEyebrow += -0.001f;
		angle_left_faceEyebrow += -0.05f;
		angle_right_faceEyebrow += -0.05f;
	}
	// 몸을 180도 돌리는 모션
	else if (count < 1300) {
		angle_body_all -= 1.8f;
		angle_left_upperLeg_forth += 0.05f;
		angle_left_lowerLeg_back += 0.05f;
		angle_right_upperLeg_forth += 0.05f;
		angle_right_lowerLeg_back += 0.05f;
	}
	// 벽돌을 들고 걸어가는 모션
	else if (count < 1900) {
		legWalking((count - 1300) % 200);
	}
	// 사다리를 타기 위한 모션 
	else if (count < 1950) {
		angle_body_axisForth += 0.5f;
		angle_head_forth += -0.3f;

		angle_right_upperArm_above += -1.0f;
		angle_right_upperArm_forth += -1.0f;
		angle_right_lowerArm_above += 0.7f;
		angle_right_lowerArm_forth += -1.6f;
	}
	// 사다리를 타는 모션
	else if (count < 2250) {
		ledderUping((count - 1950) % 200);
		move_body_all += 0.008f;
		if (count >= 2200)
			angle_head_forth += +0.3f;
	}
	// 사다리에서 몸을 일으킨다
	else if (count < 2300) {
		angle_body_axisForth += -0.5f;

		angle_right_upperArm_above += 1.0f;
		angle_right_upperArm_forth += 1.0f;
		angle_right_lowerArm_above += -0.7f;
		angle_right_lowerArm_forth += 1.6f;
	}
	// 사다리 위에서 벽돌을 앞으로 옮김
	else if (count < 2400) {
		angle_left_upperArm_above += -0.55f;
		angle_right_upperArm_above += -0.3f;

		angle_left_upperArm_forth += 0.4f;
		angle_right_upperArm_forth += -0.7f;

		if (count >= 2370) {
			angle_left_lowerArm_above += -3.5f;
		}
		angle_right_lowerArm_above += 0.1f;

		angle_left_lowerArm_forth += 0.6f;
		angle_right_lowerArm_forth += -0.2f;
	}
	// 지진이 날 때 아무것도 안함
	else if (count < 2600) {}
	// 놀라는 모션
	else if (count < 2700) {
		move_left_faceEyebrow += -0.001f;
		move_right_faceEyebrow += -0.001f;
		angle_left_faceEyebrow += 0.05f;
		angle_right_faceEyebrow += 0.05f;

		angle_left_upperArm_above += 0.05f;
		angle_right_upperArm_above += 0.05f;
		angle_left_upperArm_forth += -0.05f;
		angle_right_upperArm_forth += -0.05f;
	}
	// 떨어지는 모션
	else if (count < 2800) {
		move_body_all += -0.03f;
		// 팔을 위로 올린다
		angle_left_upperArm_above += 0.6f;
		angle_left_upperArm_forth += -0.7f;
		angle_left_lowerArm_above += 0.7f;
		angle_left_lowerArm_forth += -0.6f;
		angle_right_upperArm_above += 0.6f;
		angle_right_upperArm_forth += -0.7f;
		angle_right_lowerArm_above += 0.7f;
		angle_right_lowerArm_forth += -0.6f;
		// 다리를 쭉 펴고 벌린다
		angle_left_upperLeg_forth += -0.15f;
		angle_left_upperLeg_side += 0.1f;
		angle_left_lowerLeg_back += -0.15f;
		angle_right_upperLeg_forth += -0.15f;
		angle_right_upperLeg_side += 0.1f;
		angle_right_lowerLeg_back += -0.15f;
	}
	// 넘어지고 카메라 이동은 아무것도 안함
	else if (count < 2900) {}
	// 눈물을 흘리는 장면
	else if (count < 3000) {
	if (count == 2900)
		isTear = 1;
	move_Tear -= 0.005;
	}
}
// 끝까지 다 갔을 때 사람을 다시 초기화 자세로 만들기 위함
void initHuman() {
	angle_body_all = 0.0f;
	move_body_all = -0.15f;
	angle_body_side = 0.0f;
	angle_body_axisForth = 15.0f;
	angle_body_axisSide = 0.0f;
	angle_head_forth = 0.0f;
	angle_head_side = 0.0f;
	move_left_faceEyebrow = 45.0f;
	move_right_faceEyebrow = 45.0f;
	angle_left_faceEyebrow = 0.0f;
	angle_right_faceEyebrow = 0.0f;
	isTear = 0;
	move_Tear = 0.0f;
	angle_left_upperArm_above = -60.0f;
	angle_right_upperArm_above = 50.0f;
	angle_left_upperArm_forth = 0.0f;
	angle_right_upperArm_forth = 20.0f;
	angle_left_lowerArm_above = 0.0f;
	angle_right_lowerArm_above = 110.0f;
	angle_left_lowerArm_forth = 0.0f;
	angle_right_lowerArm_forth = 0.0f;
	angle_left_upperLeg_forth = 60.0f;
	angle_right_upperLeg_forth = 60.0f;
	angle_left_upperLeg_side = 20.0f;
	angle_right_upperLeg_side = 20.0f;
	angle_left_lowerLeg_back = 60.0f;
	angle_right_lowerLeg_back = 60.0f;
}