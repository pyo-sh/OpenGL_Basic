#include <GL/glut.h>

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(-1, -1, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1, 1, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glEnd();
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutCreateWindow("Text");
	glutDisplayFunc(mydisplay);
	glutMainLoop();
	return 0;
}