#include "human.h"

// �� ��ü�� ������
// ���� (+), ��������(-) ȸ��
GLfloat angle_body_all = 0.0f;
// �� �Ʒ� ������ y ��ǥ
GLfloat move_body_all = -0.15f;

// ��ü ���� �κ��� ������
// ���� ����(+), ������(-)���� ��Ʋ�� (90 ~ -90)
GLfloat angle_body_side = 0.0f;
// ���� ��(+), ��(-)�� ����� (90 ~ -90)
GLfloat angle_body_axisForth = 15.0f;
// ���� ��(+), ��(-) �� ����� (40 ~ -40)
GLfloat angle_body_axisSide = 0.0f;

// ��
// ��(+), ��(-)�� ���ϴ� �� (50 ~ -50)
GLfloat angle_head_forth = 0.0f;
// ��(+), ��(-)�� ���ϴ� �� (50 ~ -50)
GLfloat angle_head_side = 0.0f;
// ��(-), �Ʒ�(+)�� �����̴� ���� (40 ~ 60) 
GLfloat move_left_faceEyebrow = 45.0f;
GLfloat move_right_faceEyebrow = 45.0f;
// ������ �Ʒ���(+), �ٱ����� �Ʒ���(-) ����� ���� (50 ~ -50)
GLfloat angle_left_faceEyebrow = 0.0f;
GLfloat angle_right_faceEyebrow = 0.0f;
// ������ �ִ���
int isTear = 0;
GLfloat move_Tear = 0.0f;

// �� ���� ������
// ��(+), �Ʒ�(-)�� ���ϴ� angle (-75 ~ 85)
GLfloat angle_left_upperArm_above = -60.0f;
GLfloat angle_right_upperArm_above = 50.0f;
// ��(+), ��(-)�� ���ϴ� angle
GLfloat angle_left_upperArm_forth = 0.0f;
GLfloat angle_right_upperArm_forth = 20.0f;
// �Ʒ� ���� ������
// ��(+), �Ʒ�(-)�� ���ϴ� angle
GLfloat angle_left_lowerArm_above = 0.0f;
GLfloat angle_right_lowerArm_above = 110.0f;
// ��(+), ��(-)�� ���ϴ� angle (130 ~ -130)
GLfloat angle_left_lowerArm_forth = 0.0f;
GLfloat angle_right_lowerArm_forth = 0.0f;

// �� �ٸ��� ������
// ��(+), ��(-)�� ���ϴ� angle (-90 ~ 90)
GLfloat angle_left_upperLeg_forth = 60.0f;
GLfloat angle_right_upperLeg_forth = 60.0f;
// �� ������ ���ϴ� angle �ٱ���(+), ���� (-) (0 ~ 80)
GLfloat angle_left_upperLeg_side = 20.0f;
GLfloat angle_right_upperLeg_side = 20.0f;
// �Ʒ� �ٸ��� ������
// ��(+)�� �����̴� angle (0 ~ 100)
GLfloat angle_left_lowerLeg_back = 60.0f;
GLfloat angle_right_lowerLeg_back = 60.0f;

// �ȴ� ����� �����ϴ� �Լ� (count �� 200�� �۵�)
// �ٸ��� 15���� �����ְ�, ���� ���� -60
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
// ������ ��� �ٸ��� �ȴ� ���
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
	// �� ó�� ���
	if (count < 200) {
		// �Ӹ� �ܱ�
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
	// �볪������ �Ͼ�� ���� ���
	else if (count < 400) {
		// �� ������
		if (count < 300) {
			angle_right_upperArm_above -= 1.1f;
			angle_right_upperArm_forth -= 0.2f;
			angle_right_lowerArm_above -= 1.1f;
		}
		// �Ͼ��
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
	// �ɾ�� �ڼ����
	else if (count < 450) {
		// �ٸ� 10����
		angle_left_upperLeg_forth += 0.2f;
		angle_right_upperLeg_forth += 0.2f;
		angle_left_lowerLeg_back += 0.2f;
		angle_right_lowerLeg_back += 0.2f;
		// 0.175 ����
		move_body_all -= 0.0035;
	}
	else if (count < 650) {
		walking(count - 450);
	}
	// ������ ����
	else if (count < 700) {
		angle_body_all -= 1.8f;
	}
	else if (count < 900) {
		walking(count - 700);
	}
	// �㸮 ���̱�
	else if (count < 950) {
		// ��ü ���� ������
		move_body_all += -0.003f;
		angle_body_axisForth += 0.6f;
		// �ٸ��� ������
		angle_left_upperLeg_forth += 0.3f;
		angle_right_upperLeg_forth += 0.3f;

		angle_left_upperLeg_side += 0.4f;
		angle_right_upperLeg_side += 0.4f;

		angle_left_lowerLeg_back += 0.3f;
		angle_right_lowerLeg_back += 0.3f;
		// ���� ������
		angle_left_upperArm_above += 1.0f;
		angle_right_upperArm_above += 1.0f;

		angle_left_upperArm_forth += 1.0f;
		angle_right_upperArm_forth += 1.0f;

		angle_left_lowerArm_above += -0.5f;
		angle_right_lowerArm_above += -0.5f;

		angle_left_lowerArm_forth += 0.6f;
		angle_right_lowerArm_forth += 0.6f;
	}
	// �� ���
	else if (count < 1050) {
		// ��ü ���� ������
		move_body_all += 0.0015f;
		angle_body_axisForth += -0.3f;
		// ���� ������
		angle_left_upperArm_above += -0.3f;
		angle_right_upperArm_above += -0.3f;

		angle_left_upperArm_forth += -0.1f;
		angle_right_upperArm_forth += -0.1f;

		angle_left_lowerArm_forth += 0.3f;
		angle_right_lowerArm_forth += 0.3f;

		// �ٸ��� ������
		angle_left_upperLeg_forth += -0.15f;
		angle_right_upperLeg_forth += -0.15f;

		angle_left_upperLeg_side += -0.2f;
		angle_right_upperLeg_side += -0.2f;

		angle_left_lowerLeg_back += -0.15f;
		angle_right_lowerLeg_back += -0.15f;

		// ����
		// ��(+), �Ʒ�(-)�� �����̴� ���� (40 ~ 60) 
		move_left_faceEyebrow += 0.001f;
		move_right_faceEyebrow += 0.001f;
		// ������ �Ʒ���(+), �ٱ����� �Ʒ���(-) ����� ���� (50 ~ -50)
		angle_left_faceEyebrow += 0.05f;
		angle_right_faceEyebrow += 0.05f;
	}
	// ������ ��� ���� �ø��� ���
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
	// ���� ����ġ
	else if (count < 1200) {
		move_left_faceEyebrow += -0.001f;
		move_right_faceEyebrow += -0.001f;
		angle_left_faceEyebrow += -0.05f;
		angle_right_faceEyebrow += -0.05f;
	}
	// ���� 180�� ������ ���
	else if (count < 1300) {
		angle_body_all -= 1.8f;
		angle_left_upperLeg_forth += 0.05f;
		angle_left_lowerLeg_back += 0.05f;
		angle_right_upperLeg_forth += 0.05f;
		angle_right_lowerLeg_back += 0.05f;
	}
	// ������ ��� �ɾ�� ���
	else if (count < 1900) {
		legWalking((count - 1300) % 200);
	}
	// ��ٸ��� Ÿ�� ���� ��� 
	else if (count < 1950) {
		angle_body_axisForth += 0.5f;
		angle_head_forth += -0.3f;

		angle_right_upperArm_above += -1.0f;
		angle_right_upperArm_forth += -1.0f;
		angle_right_lowerArm_above += 0.7f;
		angle_right_lowerArm_forth += -1.6f;
	}
	// ��ٸ��� Ÿ�� ���
	else if (count < 2250) {
		ledderUping((count - 1950) % 200);
		move_body_all += 0.008f;
		if (count >= 2200)
			angle_head_forth += +0.3f;
	}
	// ��ٸ����� ���� ����Ų��
	else if (count < 2300) {
		angle_body_axisForth += -0.5f;

		angle_right_upperArm_above += 1.0f;
		angle_right_upperArm_forth += 1.0f;
		angle_right_lowerArm_above += -0.7f;
		angle_right_lowerArm_forth += 1.6f;
	}
	// ��ٸ� ������ ������ ������ �ű�
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
	// ������ �� �� �ƹ��͵� ����
	else if (count < 2600) {}
	// ���� ���
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
	// �������� ���
	else if (count < 2800) {
		move_body_all += -0.03f;
		// ���� ���� �ø���
		angle_left_upperArm_above += 0.6f;
		angle_left_upperArm_forth += -0.7f;
		angle_left_lowerArm_above += 0.7f;
		angle_left_lowerArm_forth += -0.6f;
		angle_right_upperArm_above += 0.6f;
		angle_right_upperArm_forth += -0.7f;
		angle_right_lowerArm_above += 0.7f;
		angle_right_lowerArm_forth += -0.6f;
		// �ٸ��� �� ��� ������
		angle_left_upperLeg_forth += -0.15f;
		angle_left_upperLeg_side += 0.1f;
		angle_left_lowerLeg_back += -0.15f;
		angle_right_upperLeg_forth += -0.15f;
		angle_right_upperLeg_side += 0.1f;
		angle_right_lowerLeg_back += -0.15f;
	}
	// �Ѿ����� ī�޶� �̵��� �ƹ��͵� ����
	else if (count < 2900) {}
	// ������ �긮�� ���
	else if (count < 3000) {
	if (count == 2900)
		isTear = 1;
	move_Tear -= 0.005;
	}
}
// ������ �� ���� �� ����� �ٽ� �ʱ�ȭ �ڼ��� ����� ����
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