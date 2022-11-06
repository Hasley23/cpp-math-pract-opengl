#define _USE_MATH_DEFINES
#include <cstdlib>
#include <glut.h>
#include <cmath>
#include<iostream>
using namespace std;

float ctr = 1;

float B = 0.05;
float q = 1.6*pow(10, -19);
float m = 9.1*pow(10, -31);
float v = 1 * pow(10, 8);
int N = 3000;
float dt = 0.000000000001;
float R = 0.0;
float alpha;
float preAlpha = 0.0;

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

	
	float *x;
	x = new float[N];
	float *y;
	y = new float[N];
	float *z;
	z = new float[N];
	float *v_x;
	v_x = new float[N];
	float *v_y;
	v_y = new float[N];
	float *v_z;
	v_z = new float[N];
	alpha = (preAlpha / 180)*M_PI;

	x[0] = 0.0;
	y[0] = (m * v) / (q * B);
	z[0] = 0.0;
	v_x[0] = v * sin(alpha);
	v_y[0] = v * sin(alpha);
	v_z[0] = v * cos(alpha);

	v_x[1] = v_x[0] + q * B*v_y[1] * dt / (2 * m);
	v_y[1] = v_y[0] - q * B*v_x[1] * dt / (2 * m);
	v_z[1] = v_z[0];

	x[1] = x[0] + v_x[1] * dt;
	y[1] = y[0] + v_y[1] * dt;
	z[1] = z[0] + v_z[1] * dt;
	for (int i = 2; i < N; i++) {

		v_x[i] = v_x[i - 1] + q * B*v_y[i - 1] * dt / m;
		v_y[i] = v_y[i - 1] - q * B*v_x[i - 1] * dt / m;
		v_z[i] = v_z[0];
		x[i] = x[i - 1] + v_x[i] * dt;
		y[i] = y[i - 1] + v_y[i] * dt;
		z[i] = z[i - 1] + v_z[i] * dt;
	}

	glLineWidth(2.0);
	glColor3f(0.5, 8.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < ctr; i++) {
		glVertex3f(100*x[i], 100*y[i], 100*z[i]);
	}
	glEnd();

	
	glColor3f(0.5, 8.0, 1.0);
	glPushMatrix();
	for (int i = ctr - 1; i < ctr; i++) {
		//glTranslatef(1000*x[i], 1000*y[i], 1000*z[i]);
		glTranslatef(1000, 1000, 1000);
		glutSolidSphere(0.1, 10, 10);
	}
	glPopMatrix();
	glEnd();
	
	/*
	while (t <= N) {
		//glVertex3d(x * pow(10, 13), y * pow(10, 12), 0.0);
		//x = x + v_x * dt;
		//y = y + v_y * dt;
		//v_temp = v_x;
		//v_x = v_x + q * B * v_y * dt / m;
		//cout << x << endl;
		//cout << y << endl;

		//v_y = v_y - q * B * v_temp * dt / m;
		//v_temp = v_x;
		t += dt;
	}
	glEnd();
	*/
	
	glFlush();
	glutSwapBuffers();
	//glClear(GL_COLOR_BUFFER_BIT);
	
	//LOLOLOL
	delete[] v_x;
	delete[] v_y;
	delete[] v_z;
	delete[] z;
	delete[] x;
	delete[] y;
}

void DRAW()
{
	while (true)
	{
		N += 1;
		if (N < 700.0)
			render_scene();
	}
}

void keyboard_func(unsigned char key, int x, int y)
{
	
	switch (key)
	{
	case 'x':
		ctr++;
		if (ctr < 4000) render_scene();
		break;

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
	cout << "Alpha???" << endl;
	cin >> preAlpha;
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