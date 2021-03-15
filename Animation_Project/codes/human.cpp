#include "human.h"
#include "cylinder.h"

#define direction_left 1.0f
#define direction_right -1.0f

// RGB[0] = ���� ��
// RGB[1] = ���� ��
// RGB[2] = �Ǻλ�
// RGB[3] = �Ź�
GLfloat RGB[4][3] = {
	{46.0f / 255.0f, 204.0f / 255.0f, 133 / 255.0f},
	{127.0f / 255.0f, 140.0f / 255.0f, 141.0f / 255.0f},
	{255.0f / 255.0f, 204.0f / 255.0f, 204.0f / 255.0f},
	{87.0f / 255.0f, 75.0f / 255.0f, 144.0f / 255.0f}
};

// ��
GLfloat body_upper_height = 0.475f;
GLfloat body_upper_radius = 0.15f;
GLfloat body_lower_radius = 0.15f;
// �� 0.04 + 0.14
GLfloat neck_radius = 0.06f;
GLfloat head_radius = 0.14f;
GLfloat face_eyebrow_size = 0.015f;
GLfloat face_eye_size = 0.015f;
// ����
extern int isTear;
extern GLfloat move_Tear;

// �� ����
GLfloat arm_upper_length = 0.30f;
GLfloat arm_lower_length = 0.225f;
// �� ũ��
GLfloat arm_upper_radius = 0.08f;
GLfloat arm_lower_radius = 0.05f;
GLfloat arm_hand_radius = 0.035f;

// �ٸ� ����
GLfloat leg_upper_length = 0.30f;
GLfloat leg_lower_length = 0.225f;
// �ٸ� ũ��
GLfloat leg_upper_radius = body_lower_radius / 2.0f;
GLfloat leg_lower_radius = 0.05f;
GLfloat leg_foot_radius = 0.035f;

// �� �׸���
void drawBody() {
	glPushMatrix();
	// x�� �þ�� ���� y�� �þ�� �ؾ��ϹǷ�
	glRotatef(90, 0, 0, 1);
	// ����
	glColor3f(RGB[1][0], RGB[1][1], RGB[1][2]);
	drawCylinder(body_lower_radius, 0.2f, 0.15f);
	// ����
	glTranslatef(0.15f, 0, 0);
	glColor3f(RGB[0][0], RGB[0][1], RGB[0][2]);
	drawCylinder(0.2f, body_upper_radius, body_upper_height - 0.15f);
	glPopMatrix();
}

void drawTear(GLfloat tearDown) {
	glPushMatrix();
	glColor3f(0, 0, 1);
	glScalef(0.25, 0.25, 0.25);
	glTranslatef(0, tearDown - 0.25, 0);
	glRotatef(-90.0f, 1, 0, 0);
	glutSolidCone(0.08, 0.2, 100, 100);
	glTranslatef(0, 0, -0.06);
	glutSolidSphere(0.1, 100, 100);
	glPopMatrix();
}
void drawFace(GLfloat leftEyebrowUp, GLfloat rightEyeBrowUp, GLfloat angleLeftEyebrow, GLfloat angleRightEyebrow) {
	glColor3f(0, 0, 0);
	GLfloat x = face_eyebrow_size + 0.03f;
	GLfloat left_eyebrow_y = head_radius * cos(leftEyebrowUp);
	GLfloat right_eyebrow_y = head_radius * cos(rightEyeBrowUp);
	GLfloat eye_x = face_eye_size + 0.03f;
	GLfloat eye_y = head_radius * cos(30.0f);
	// ���� ����
	glPushMatrix();
	// ������ ��ġ
	glTranslatef(x, left_eyebrow_y, head_radius);
	// ������ ����
	glRotatef(angleLeftEyebrow, 0, 0, 1);
	glScalef(3, 1, 1);
	glutSolidCube(face_eyebrow_size);
	glPopMatrix();
	// ������ ����
	glPushMatrix();
	// ������ ��ġ
	glTranslatef(-x, right_eyebrow_y, head_radius);
	// ������ ����
	glRotatef(- angleRightEyebrow, 0, 0, 1);
	glScalef(3, 1, 1);
	glutSolidCube(face_eyebrow_size);
	glPopMatrix();
	// ��
	glPushMatrix();
	glTranslatef(eye_x, eye_y, head_radius);
	glutSolidSphere(face_eye_size, 100, 100);
	if(isTear)
		drawTear(move_Tear);
	glColor3f(0, 0, 0);
	glTranslatef(-2 * eye_x, 0, 0);
	glutSolidSphere(face_eye_size, 100, 100);
	glPopMatrix();
	glColor3f(1, 1, 1);
}
void drawHead(GLfloat angleForth, GLfloat angleSide, GLfloat face1, GLfloat face2, GLfloat face3, GLfloat face4){
	glPushMatrix();
	glTranslatef(0, body_upper_height, 0);	// ���� ũ�⿡ ���缭 �Ӹ��� ��ġ ����
	glutSolidSphere(neck_radius, 100, 100);
	// ��(+), ��(-)�� ���ϴ� angle
	glRotatef(angleForth, 1, 0, 0);
	// ��(+), ��(-)�� ���ϴ� angle
	glRotatef(angleSide, 0, 0, 1);
	glTranslatef(0, head_radius - neck_radius / 2.0f, 0);	// �Ӹ��� ũ�⿡ ���缭 ��ġ ����
	glutSolidSphere(head_radius, 100, 100);
	drawFace(face1, face2, face3, face4);		// ǥ��
	glPopMatrix();
}
// �� �׸���
// �� ��(direction = 1) / ���� ��(direction = -1)
void drawUpperArm(GLfloat direction, GLfloat angleAbove, GLfloat angleForth) {
	glColor3f(RGB[0][0], RGB[0][1], RGB[0][2]);
	glTranslatef(direction * body_upper_radius, body_upper_height - arm_upper_radius, 0);	// ���� ũ�⿡ ���缭 ���� ��ġ ����
	glutSolidSphere(arm_upper_radius + 0.01f, 30, 30);
	// ��(+), �Ʒ�(-)�� ���ϴ� angle
	glRotatef(direction * angleAbove, 0, 0, 1);
	// ��(+), ��(-)���� ���ϴ� angle
	glRotatef(- direction * angleForth, 0, 1, 0);
	drawCylinder(arm_upper_radius, arm_lower_radius, direction * arm_upper_length);
}
void drawLowerArm(GLfloat direction, GLfloat angleAbove, GLfloat angleForth) {
	glColor3f(RGB[0][0], RGB[0][1], RGB[0][2]);
	glTranslatef(direction * arm_upper_length, 0, 0);	// upper_arm �� ���̿� ���缭 ���� ��ġ ����
	glutSolidSphere(arm_lower_radius + 0.005f, 30, 30);
	// ��(+), �Ʒ�(-)�� ���ϴ� angle
	glRotatef(direction * angleAbove, 0, 0, 1);
	// ��(+), ��(-)���� ���ϴ� angle
	glRotatef(- direction * angleForth, 0, 1, 0);
	drawCylinder(arm_lower_radius, arm_hand_radius, direction * arm_lower_length);
}
void drawHand(GLfloat direction) {
	glColor3f(RGB[2][0], RGB[2][1], RGB[2][2]);
	glTranslatef(direction * arm_lower_length, 0, 0);	// lower_arm �� ���̿� ���缭 ���� ��ġ ����
	glutSolidSphere(arm_hand_radius + 0.005f, 20, 20);
}

// �ٸ� �׸���
void drawUpperLeg(GLfloat direction, GLfloat angleForth, GLfloat angleSide) {
	glColor3f(RGB[1][0], RGB[1][1], RGB[1][2]);
	glTranslatef(direction * leg_upper_radius, 0, 0);	// �ٸ��� ũ�⸦ ����ؼ� ����, ���������� �̵�
	glutSolidSphere(leg_upper_radius + 0.005f, 20, 20);
	glRotatef(-90, 0, 0, 1);	// �ٸ��� �Ʒ��� ���� �ؾ���
	// ��(+), ��(-)�� ���ϴ� angle
	glRotatef(- angleForth, 0, 1, 0);
	// �� ������ ���ϴ� angle �ٱ���(+), ���� (-)
	glRotatef(direction * angleSide, 0, 0, 1);
	drawCylinder(leg_upper_radius, leg_lower_radius, leg_upper_length);
}
void drawLowerLeg(GLfloat angleForth) {
	glColor3f(RGB[1][0], RGB[1][1], RGB[1][2]);
	glTranslatef(leg_upper_length, 0, 0);	// upper_leg �� ���̿� ���缭 ���� ��ġ ����
	glutSolidSphere(leg_lower_radius + 0.005f, 20, 20);
	// ��(-)�� ���ϴ� angle
	glRotatef(angleForth, 0, 1, 0);
	drawCylinder(leg_lower_radius, leg_foot_radius, leg_lower_length);
}
void drawFeet() {
	glColor3f(RGB[3][0], RGB[3][1], RGB[3][2]);
	// �߸�
	glTranslatef(leg_lower_length, 0, 0);
	drawCylinder(leg_foot_radius, leg_foot_radius, leg_foot_radius);
	// ��
	glPushMatrix();
	glTranslatef(leg_foot_radius / 2.0f, 0, leg_foot_radius * 2.5f);
	glScalef(1, 1, 3);
	glutSolidSphere(leg_foot_radius, 20, 20);
	glPopMatrix();
}

// �����ӿ� ����� ������������ humanAnimation.c ���� �����´�.
extern GLfloat angle_body_all;
extern GLfloat move_body_all;

extern GLfloat angle_body_side;
extern GLfloat angle_body_axisForth;
extern GLfloat angle_body_axisSide;

extern GLfloat angle_head_forth;
extern GLfloat angle_head_side;
extern GLfloat move_left_faceEyebrow;
extern GLfloat move_right_faceEyebrow;
extern GLfloat angle_left_faceEyebrow;
extern GLfloat angle_right_faceEyebrow;

extern GLfloat angle_left_upperArm_above;
extern GLfloat angle_left_upperArm_forth;
extern GLfloat angle_left_lowerArm_above;
extern GLfloat angle_left_lowerArm_forth;

extern GLfloat angle_right_upperArm_above;
extern GLfloat angle_right_upperArm_forth;
extern GLfloat angle_right_lowerArm_above;
extern GLfloat angle_right_lowerArm_forth;

extern GLfloat angle_left_upperLeg_forth;
extern GLfloat angle_left_upperLeg_side;
extern GLfloat angle_left_lowerLeg_back;

extern GLfloat angle_right_upperLeg_forth;
extern GLfloat angle_right_upperLeg_side;
extern GLfloat angle_right_lowerLeg_back;

void drawHuman() {
	glPushMatrix();

	glTranslatef(0, move_body_all + 0.56f, 0);
	glRotatef(angle_body_all, 0, 1, 0);

	// �޹�
	glPushMatrix();
	drawUpperLeg(direction_left, angle_left_upperLeg_forth, angle_left_upperLeg_side);
	drawLowerLeg(angle_left_lowerLeg_back);
	drawFeet();
	glPopMatrix();
	// ������
	glPushMatrix();
	drawUpperLeg(direction_right, angle_right_upperLeg_forth, angle_right_upperLeg_side);
	drawLowerLeg(angle_right_lowerLeg_back);
	drawFeet();
	glPopMatrix();

	// ��ü ���� �κ��� ������
	// ���� ����, ���������� ��Ʋ��
	glRotatef(angle_body_side, 0, 1, 0);
	// ���� ��(+), ��(-)�� �����
	glRotatef(angle_body_axisForth, 1, 0, 0);
	// ���� ��(-), ��(+) �� �����
	glRotatef(angle_body_axisSide, 0, 0, 1);

	// ��
	drawBody();

	// �޼�
	glPushMatrix();
	drawUpperArm(direction_left, angle_left_upperArm_above, angle_left_upperArm_forth);
	drawLowerArm(direction_left, angle_left_lowerArm_above, angle_left_lowerArm_forth);
	drawHand(direction_left);
	glPopMatrix();
	// ������
	glPushMatrix();
	drawUpperArm(direction_right, angle_right_upperArm_above, angle_right_upperArm_forth);
	drawLowerArm(direction_right, angle_right_lowerArm_above, angle_right_lowerArm_forth);
	drawHand(direction_right);
	glPopMatrix();

	// �Ӹ�
	glColor3f(RGB[2][0], RGB[2][1], RGB[2][2]);
	drawHead(angle_head_forth, angle_head_side, move_left_faceEyebrow, move_right_faceEyebrow, angle_left_faceEyebrow, angle_right_faceEyebrow);
	glPopMatrix();
}
