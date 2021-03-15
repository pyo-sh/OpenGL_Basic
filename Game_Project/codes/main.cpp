#include "control.h"
#include "object.h"

extern GLfloat camx, camy, camz;
extern GLfloat cam2x, cam2y, cam2z;
extern GLfloat cam_upx, cam_upy, cam_upz;

extern GLfloat displayCamy;
extern GLfloat displayCam2y;

extern int stage;
extern GLfloat global_Ambient_value;

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat ratio = (float)width / height;
	gluPerspective(40, ratio, 0.1, 1000);
}

void init_light() {
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void set_light() {
	// ���� ���� & ��ġ ����
	GLfloat light_global_ambient[] = { global_Ambient_value, global_Ambient_value, global_Ambient_value, 1.0 };
	GLfloat light_0_pos[] = { camx, 3, camz, 1.0 };
	GLfloat light_0_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat light_0_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat light_0_specular[] = { 0.45, 0.45, 0.45, 1.0 };

	// �� Ȱ��ȭ, �� ���� & ��ġ����
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_global_ambient);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_0_pos);
}

void set_background_material_color() {
	// ��ü ���� ���� & ����
	glDisable(GL_COLOR_MATERIAL);
	GLfloat material_0_ambient[] = { 131.0 / 255.0, 149.0 / 255.0, 167.0 / 255.0, 1.0 };
	GLfloat material_0_diffuse[] = { 60.0 / 255.0, 99.0 / 255.0, 130.0 / 255.0, 1.0 };
	GLfloat material_0_specular[] = { 235.0 / 255.0, 47.0 / 255.0, 6.0 / 255.0, 1.0 };
	GLfloat material_0_shininess[] = { 50.0 };	// 0 ~ 128
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_0_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_0_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_0_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_0_shininess);
}
void set_material_color() {
	// ��ü ���� ���� & ����
	glDisable(GL_COLOR_MATERIAL);
	GLfloat material_0_ambient[] = { 164.0 / 255.0, 176.0 / 255.0, 190.0 / 255.0, 1.0 };
	GLfloat material_0_diffuse[] = { 116.0 / 255.0, 125.0 / 255.0, 140.0 / 255.0, 1.0 };
	GLfloat material_0_specular[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat material_0_shininess[] = { 75.0 };	// 0 ~ 128
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_0_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_0_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_0_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_0_shininess);
}

Mat image[7];
GLuint tex_ids[7] = { 1, 2, 3, 4, 5, 6, 7 };
int nTex = 7;
void init_texture() {
	glGenTextures(nTex, tex_ids);
	glEnable(GL_TEXTURE_2D);
}

extern GLfloat userHeight;

extern GLfloat xAngle;
extern GLfloat yAngle;

extern GLfloat left_hand_above;
extern GLfloat left_hand_side;
extern GLfloat right_hand_above;
extern GLfloat right_hand_side;

CModel point;
extern bool isStart;
CModel intro;
int intro_id[1] = { 7 };

CModel background;
CModel background_cube;
CModel background_lava;
int lava_id[1] = { 6 };
CModel leftHand;
CModel rightHand;
int hand_id[2] = { 1, 2 };
CModel knife;
int knife_id[3] = { 3, 4, 5 };

CModel outtro;

extern GLfloat first_Floor[3];
extern GLfloat second_Floor[3];
extern GLfloat third_Floor[3];

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(camx, displayCamy, camz, cam2x, displayCam2y, cam2z, cam_upx, cam_upy, cam_upz);

	if (stage == 0) {
		glPushMatrix();
		GLfloat pointHeight = isStart ? 0.9f : 0.4f;
		glTranslatef(-0.7f, pointHeight, 0.0f);
		display_objs_texture(&point, intro_id, 1);
		glPopMatrix();

		display_objs_texture(&intro, intro_id, 1);
		set_light();
	}
	else if (1 <= stage && stage <= 2) {
		// ���
		set_background_material_color();
		display_objs_texture(&background, lava_id, 1);
		display_objs_texture(&background_lava, lava_id, 1);
		set_material_color();
		display_objs(&background_cube);
		// �����̴� �ٴ�
		glPushMatrix();
		glTranslatef(first_Floor[0], first_Floor[2] - 1.0f, first_Floor[1]);
		glutSolidCube(2);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(second_Floor[0], second_Floor[2] - 1.0f, second_Floor[1]);
		glutSolidCube(2);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(third_Floor[0], third_Floor[2] - 1.0f, third_Floor[1]);
		glutSolidCube(2);
		glPopMatrix();

		set_light();
		// ��
		glPushMatrix();
		// ķ�� �ִ� ��ġ�� ���� �����δ�
		glTranslatef(camx, displayCamy, camz);

		// ķ�� ������ ���� ������
		glRotatef(xAngle, 0, 1.0, 0);
		glRotatef(yAngle, -1.0, 0, 0);

		// �޼�
		glPushMatrix();
		// ������
		glRotatef(left_hand_side, 0, 1.0, 0);
		// �� �Ʒ�
		glRotatef(left_hand_above, -1.0, 0, 0);
		display_objs_texture(&leftHand, hand_id, 2);
		glPopMatrix();

		// ������
		glPushMatrix();
		// ������
		glRotatef(right_hand_side, 0, 1.0, 0);
		// �� �Ʒ�
		glRotatef(right_hand_above, -1.0, 0, 0);
		display_objs_texture(&rightHand, hand_id, 2);
		display_objs_texture(&knife, knife_id, 3);
		glPopMatrix();

		glPopMatrix();
	}
	if (stage == 3) {
		glTranslatef(0.0f, 0.3f, 0.0f);
		display_objs_texture(&outtro, intro_id, 1);
		set_light();
	}

	glFlush();
}

int main(int argc, char** argv) {
	// ������Ʈ �ҷ�����
	string filepath = "D:/CG/Blender/hand.obj";
	ifstream fin1(filepath);
	loadObj(fin1, &leftHand);
	fin1.close();

	filepath = "D:/CG/Blender/righthand.obj";
	ifstream fin2(filepath);
	loadObj(fin2, &rightHand);
	fin2.close();

	filepath = "D:/CG/Blender/knife.obj";
	ifstream fin3(filepath);
	loadObj(fin3, &knife);
	fin3.close();

	filepath = "D:/CG/Blender/background.obj";
	ifstream fin4(filepath);
	loadObj(fin4, &background);
	fin4.close();

	filepath = "D:/CG/Blender/background_cube.obj";
	ifstream fin5(filepath);
	loadObj(fin5, &background_cube);
	fin5.close();

	filepath = "D:/CG/Blender/lava.obj";
	ifstream fin6(filepath);
	loadObj(fin6, &background_lava);
	fin6.close();

	filepath = "D:/CG/Blender/firstText.obj";
	ifstream fin7(filepath);
	loadObj(fin7, &intro);
	fin7.close();

	filepath = "D:/CG/Blender/point.obj";
	ifstream fin8(filepath);
	loadObj(fin8, &point);
	fin8.close();

	filepath = "D:/CG/Blender/lastText.obj";
	ifstream fin9(filepath);
	loadObj(fin9, &outtro);
	fin9.close();

	// �ؽ�ó �ҷ�����
	image[0] = imread("D:\\CG\\OpenCV\\skin.jpg", IMREAD_COLOR);
	cvtColor(image[0], image[0], COLOR_BGR2RGB);
	image[1] = imread("D:\\CG\\OpenCV\\blackLeather.jpg", IMREAD_COLOR);
	cvtColor(image[1], image[1], COLOR_BGR2RGB);
	image[2] = imread("D:\\CG\\OpenCV\\violet.jpg", IMREAD_COLOR);
	cvtColor(image[2], image[2], COLOR_BGR2RGB);
	image[3] = imread("D:\\CG\\OpenCV\\metal.jpg", IMREAD_COLOR);
	cvtColor(image[3], image[3], COLOR_BGR2RGB);
	image[4] = imread("D:\\CG\\OpenCV\\grab.jpg", IMREAD_COLOR);
	cvtColor(image[4], image[4], COLOR_BGR2RGB);
	image[5] = imread("D:\\CG\\OpenCV\\lava2.tif", IMREAD_COLOR);
	cvtColor(image[5], image[5], COLOR_BGR2RGB);
	image[6] = imread("D:\\CG\\OpenCV\\lava.tif", IMREAD_COLOR);
	cvtColor(image[6], image[6], COLOR_BGR2RGB);

	// gl ����
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glutCreateWindow("Final Project");
	init_light();
	init_texture();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// Ű���� ���
		// Ű���带 ������ ���� �� ��� �ݺ��Ǵ� ������ ����
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
		// Ű���带 �ѹ� ������ ���� ������ �ִ� ������ ����
		// �ߺ� Ű�� ������� �ʱ� ����
	glutKeyboardFunc(pressKeyboardEvent);
		// Ű���带 ���� �� ������ ����
	glutKeyboardUpFunc(offKeyboardEvent);
	

	// ���콺 ������
	glutWarpPointer(_WINDOW_CENTER_WIDTH, _WINDOW_CENTER_HEIGHT);
	glutPassiveMotionFunc(moveMouseEvent);
	
	// ������ ó���� ���� Ÿ�̸�
	glutTimerFunc(1, MyTimer, 1);

	glutMainLoop();

	return 0;
}