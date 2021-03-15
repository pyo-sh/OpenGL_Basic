#include "cylinder.h"

GLfloat GL_PI = 3.1415926f;
GLfloat plus_angle = GL_PI / 180.0f;
GLfloat full_angle = GL_PI * 2.0f;
/*
	밑면과 윗면의 반지름 길이가 다른 원기둥
	 -> +x 방향으로 추가됨
	 -> startRadius : 밑면 원의 반지름
	 -> finishRadius : 윗면 원의 반지름
	 -> height : 원기둥의 높이
*/
void drawCylinder(GLfloat startRadius, GLfloat finishRadius, GLfloat height){
	GLfloat y, z, to_y, to_z, angle;

	// 시작하는 부분의 면
	glBegin(GL_TRIANGLE_FAN);		// 중심을 공유하는 삼각형(도형)
	glNormal3f(-1.0f, 0.0f, 0.0f);	// 법선 Vector (도형과 수직을 이루는 벡터), (x로 늘어날 것이기 때문에.. -x 에서 보아야함)
	
		// 도형 그리기
	glVertex3f(0, 0, 0);	// 중앙점
	for (angle = 0.0f; angle < full_angle; angle += plus_angle){
		y = startRadius * sin(angle);
		z = startRadius * cos(angle);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(0, y, z);
	}
	glEnd();

	// 옆면
	glBegin(GL_QUAD_STRIP);			// 연결된 사각형(도형)
	for (angle = 0.0f; angle < full_angle; angle += plus_angle){
		GLfloat sin_angle = sin(angle);
		GLfloat cos_angle = cos(angle);
		y = startRadius * sin_angle;
		z = startRadius * cos_angle;
		to_y = finishRadius * sin_angle;
		to_z = finishRadius * cos_angle;
		glNormal3f(0.0f, sin_angle, cos_angle);	// x 방향으로 늘어나므로 면의 바깥 쪽
		glVertex3f(0, y, z);
		glVertex3f(height, to_y, to_z);
	}
	glEnd();

	// 끝나는 부분의 면
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(1.0f, 0.0f, 0.0f);	// x로 늘어나므로 윗 부분은 +x에서 보게 된다.
	glVertex3f(height, 0, 0);
	// 아랫면이기 때문에 반대 방향으로 해야 함
	for (angle = full_angle; angle > 0.0f; angle -= plus_angle){
		y = finishRadius * sin(angle);
		z = finishRadius * cos(angle);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(height, y, z);
	}
	glEnd();
}