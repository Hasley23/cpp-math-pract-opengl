#define _USE_MATH_DEFINES
#include <cstdlib>
#include <glut.h>
#include <cmath>
#include<iostream>
using namespace std;

float N = 0.0;

double I_0 = 0.0;
double I = 0.0;
double Beta = 0.0;
double Omega_0 = 0.0;
double q_0 = 0.0;
double E_max = 0.0;
double L = 0.0;
double Omega = 0.0;
double t = 0.0;
double dt = 0.00001;
double t_i = 0.0;
double q = 0.0;
double R = 0.0;
double C = 0.0;
double nu = 0.0;
double E = 0.0;

void change_size(GLsizei w, GLsizei h) {
	GLdouble aspect_ratio;
	//if (h == 0)
		//h = 1; 
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	aspect_ratio = (GLdouble)w / (GLdouble)h;
	gluPerspective(25.0, (double)w / (double)h, 1.0, 100);
	glTranslatef(0, 0, -35);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void initialise() {
	glClearColor(.5, .5, .5, 0.5);
}

void drawText(const char *text, int length, int x, int y)	//Отображение текста на экране, произвольная позиция
{
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
}

void render_scene() { 
	glClear(GL_COLOR_BUFFER_BIT);

	//Ось X
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-39.0, 0.0);
	glVertex2f(39.0, 0.0);
	glEnd();

	//Ось Y
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, -22);
	glVertex2f(0.0, 22);
	glEnd();

	//Ось Z
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0, -22);
	glVertex3f(0.0, 0, 22.0);
	glEnd();

	//Случай 1
	//Начальные данные
	I = 0;
	q = 2 * pow(10, -6);
	R = 200;
	L = 0.5;
	C = 0.5 *pow(10, -6);
	t = 0;
	dt = 0.00001;
	E = 200;
	Beta = R / (2 * L);
	//Omega_0 = sqrt(1 / (L*C));
	//Omega = sqrt(Omega_0*Omega_0 - Beta * Beta);
	Omega_0 = pow(10, 5);
	Omega = pow(10, 10);
	double E_max = E;

	I -= (2 * Beta*I + Omega_0 * Omega_0*q - E * cos(Omega*t) / L)*dt/2.0;
	q = q + I * dt;
	glPointSize(1);
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 1);
	while (t <= N) {
		//glVertex2d(t * 10.0, q * 1000.0);
		glVertex2d(t * 200, I * 100);
		//glVertex2d(t * 200.0, E * 0.5);
		I -= (2 * Beta*I + Omega_0 * Omega_0*q - E_max * cos(Omega*t) / L)*dt;
		q = q + I * dt;
		E = E_max * cos(Omega * t);
		t += dt;
	}
	glEnd();

	

	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(t * 50.0, I * 50.0, 0);
	glutSolidSphere(0.005, 20, 20);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	//glClear(GL_COLOR_BUFFER_BIT);
}

void DRAW()
{
	while (true)
	{
		N += 0.005;
		if (N < 700.0)
			render_scene();
	}
}

void keyboard_func(unsigned char key, int x, int y)
{
	
	switch (key)
	{
	case 'x':
		N += 0.00025;
		if (N < 700.0) render_scene();
		//DRAW();

		break;

	//XZ (верх-вниз)
	case '8':
		glRotatef(0.5, 1, 0, 1);
		render_scene();
		break;
	case '2':
		glRotatef(-0.5, 1, 0, 1);
		render_scene();
		break;

	//Y (лево-право)
	case '4':
		glRotatef(0.5, 0, 1, 0);
		render_scene();
		break;
	case '6':
		glRotatef(-0.5, 0, 1, 0);
		render_scene();
		break;

	//YZ
	case '7':
		glRotatef(0.5, 0, 0, 1);
		glRotatef(0.5, 0, 1, 0);
		render_scene();
		break;
	
	//XZ
	case '9':
		glRotatef(0.5, 1, 0, 0);
		glRotatef(-0.5, 0, 0, 1);
		render_scene();
		break;

	//XZ
	case '1':
		glRotatef(-0.5, 1, 0, 0);
		glRotatef(0.5, 0, 0, 1);
		render_scene();
		break;

		//XY
	case '3':
		glRotatef(-0.5, 1, 0, 0);
		glRotatef(-0.5, 0, 1, 0);
		render_scene();
		break;
	case 27:	// Escape key
		exit(0);
	}
}

static void reshape_view(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}


void XYZ_rotation(int button, int state, int x, int y)
{
	button = GLUT_LEFT_BUTTON;
	N += 10;
	if (state == GLUT_DOWN) render_scene();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("ФОСТ5");
	//glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_ONE, GL_SRC_COLOR);
	float light_position[] = { -3, 0,-3, 0.0f };
	glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	//glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glutKeyboardFunc(keyboard_func);
	glutMouseFunc(XYZ_rotation);
	glutDisplayFunc(render_scene);
	glutReshapeFunc(change_size);
	initialise();
	glutMainLoop();
	return 0;
}