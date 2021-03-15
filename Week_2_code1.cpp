#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define _WINDOW_WIDTH	300
#define _WINDOW_HEIGHT	300
#define R	72 / 255.0
#define G	52 / 255.0
#define B	212 / 255.0
#define _MODE_COUNT	5

int mode = 0;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(R, G, B);

	switch (mode) {
        case 0:
            glBegin(GL_POLYGON);
            glVertex3f(-0.5, -0.5, 0.0);
            glVertex3f(0.5, -0.5, 0.0);
            glVertex3f(0.5, 0.5, 0.0);
            glVertex3f(-0.5, 0.5, 0.0);
            break;
        case 1:
            glutWireTeapot(0.6);	break;
        case 2:
            glutWireOctahedron();	break;
        case 3:
            glutWireIcosahedron();	break;
        case 4:
            glColor3f(1.0, 242 / 255.0, 0.0);
            glBegin(GL_POLYGON);
            glVertex3f(0.25, 0.30, 0.0);
            glVertex3f(1.0, 0.30, 0.0);
            glVertex3f(0.425, -0.15, 0.0);
            glVertex3f(0.75, -1.0, 0.0);
            glVertex3f(0.0, -0.425, 0.0);
            glVertex3f(-0.75, -1.0, 0.0);
            glVertex3f(-0.425, -0.15, 0.0);
            glVertex3f(-1.0, 0.30, 0.0);
            glVertex3f(-0.25, 0.30, 0.0);
            glVertex3f(0.0, 1.0, 0.0);
            break;
	}
	glEnd();
    glFlush();
}

void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)_WINDOW_WIDTH;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)_WINDOW_HEIGHT;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor, -1.0, 1.0);
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
	switch (KeyPressed) {

        case 'a':
            mode = (mode + 1) % _MODE_COUNT;
            break;

        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
            mode = int(KeyPressed - '1');
            break;

        case 'Q':
        case 'q':
        case 27:
            exit(0);	break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Example Drawing");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);

	glutMainLoop();
	return 0;
}
