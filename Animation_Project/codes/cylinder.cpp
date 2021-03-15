#include "cylinder.h"

GLfloat GL_PI = 3.1415926f;
GLfloat plus_angle = GL_PI / 180.0f;
GLfloat full_angle = GL_PI * 2.0f;
/*
	�ظ�� ������ ������ ���̰� �ٸ� �����
	 -> +x �������� �߰���
	 -> startRadius : �ظ� ���� ������
	 -> finishRadius : ���� ���� ������
	 -> height : ������� ����
*/
void drawCylinder(GLfloat startRadius, GLfloat finishRadius, GLfloat height){
	GLfloat y, z, to_y, to_z, angle;

	// �����ϴ� �κ��� ��
	glBegin(GL_TRIANGLE_FAN);		// �߽��� �����ϴ� �ﰢ��(����)
	glNormal3f(-1.0f, 0.0f, 0.0f);	// ���� Vector (������ ������ �̷�� ����), (x�� �þ ���̱� ������.. -x ���� ���ƾ���)
	
		// ���� �׸���
	glVertex3f(0, 0, 0);	// �߾���
	for (angle = 0.0f; angle < full_angle; angle += plus_angle){
		y = startRadius * sin(angle);
		z = startRadius * cos(angle);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(0, y, z);
	}
	glEnd();

	// ����
	glBegin(GL_QUAD_STRIP);			// ����� �簢��(����)
	for (angle = 0.0f; angle < full_angle; angle += plus_angle){
		GLfloat sin_angle = sin(angle);
		GLfloat cos_angle = cos(angle);
		y = startRadius * sin_angle;
		z = startRadius * cos_angle;
		to_y = finishRadius * sin_angle;
		to_z = finishRadius * cos_angle;
		glNormal3f(0.0f, sin_angle, cos_angle);	// x �������� �þ�Ƿ� ���� �ٱ� ��
		glVertex3f(0, y, z);
		glVertex3f(height, to_y, to_z);
	}
	glEnd();

	// ������ �κ��� ��
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(1.0f, 0.0f, 0.0f);	// x�� �þ�Ƿ� �� �κ��� +x���� ���� �ȴ�.
	glVertex3f(height, 0, 0);
	// �Ʒ����̱� ������ �ݴ� �������� �ؾ� ��
	for (angle = full_angle; angle > 0.0f; angle -= plus_angle){
		y = finishRadius * sin(angle);
		z = finishRadius * cos(angle);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(height, y, z);
	}
	glEnd();
}