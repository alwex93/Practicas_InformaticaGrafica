// Etapa3.cpp
// Fichero principal 
////////////////////////////////////////////////////
#include "stdafx.h"
#include "glut.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <math.h>
const int W_WIDTH = 500; // Tamaño incial de la ventana
const int W_HEIGHT = 500;
GLfloat fAngulo; // Variable que indica el ángulo de rotación de los ejes. 
GLfloat move_x;
GLfloat move_y;
enum Direction { up, down, left, right };
Direction dir;

// Función que visualiza la escena OpenGL
void Display(void)
{
	// Borramos la escena
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glTranslatef(0.0f, -2.5f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-2.5f, 0.0f, -3.5f);
	glVertex3f(2.5f, 0.0f, -3.5f);
	glVertex3f(2.5f, 0.0f, 1.5f);
	glVertex3f(-2.5f, 0.0f, 1.5f);
	glEnd();
	glTranslatef(0.0f, 2.5f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	//Cubos
	glTranslatef(0.0f, 0.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidCube(1);

	glColor3f(1.0f, 1.0f, 0.0f);
	glutWireCube(1);

	glTranslatef(-2.0f, 0.0f, 0.0f);
	//Esfera 1
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(0.5, 10, 10);

	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireSphere(0.5, 10, 10);
	glColor3f(0.0f, 0.5f, 1.0f);
	glutSolidTorus(0.5, 1, 10, 10);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutWireTorus(0.5, 1, 10, 10);
	glTranslatef(4.0f, 0.0f, 0.0f);
	//Esfera 2
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(0.5, 10, 10);

	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireSphere(0.5, 10, 10);
	glColor3f(0.0f, 0.5f, 1.0f);
	glutSolidTorus(0.5, 1, 10, 10);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutWireTorus(0.5, 1, 10, 10);

	glPopMatrix();

	glutSwapBuffers();
}

//Mostramos la figura y la rotamos
void DisplayRotate(void)
{
	// Borramos la escena
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glTranslatef(0.0f, -2.5f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-2.5f, 0.0f, -3.5f);
	glVertex3f(2.5f, 0.0f, -3.5f);
	glVertex3f(2.5f, 0.0f, 1.5f);
	glVertex3f(-2.5f, 0.0f, 1.5f);
	glEnd();
	glTranslatef(0.0f, 2.5f, 0.0f);
	glPopMatrix();

	/*glPushMatrix();
	glTranslatef(0.0f, 0.0f, -1.0f);
	// Rotamos las proximas primitivas
	//glRotatef(fAngulo, 1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidCube(1);

	glColor3f(1.0f, 1.0f, 0.0f);
	glutWireCube(1);
	glPopMatrix();*/

	//Esferas
	glPushMatrix();
	//glTranslatef(1.0f, 0.0f, 0.0f);
	glRotatef(fAngulo, 0.0f, 1.0f, 1.0f);
	glTranslatef(-2.0f, 0.0f, 0.0f);

	//Esfera 1
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(0.5, 10, 10);

	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireSphere(0.5, 10, 10);

	glTranslatef(4.0f, 0.0f, 0.0f);
	//Esfera 2
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(0.5, 10, 10);

	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireSphere(0.5, 10, 10);
	
	glPopMatrix();

	glPushMatrix();
	glRotatef(fAngulo, 0.0f, -1.0f, -1.0f);
	glTranslatef(-2.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.5f, 1.0f);
	glutSolidTorus(0.5, 1, 10, 10);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutWireTorus(0.5, 1, 10, 10);

	glTranslatef(4.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.5f, 1.0f);
	glutSolidTorus(0.5, 1, 10, 10);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutWireTorus(0.5, 1, 10, 10);

	glPopMatrix();

	glutSwapBuffers();
}

void DisplayTranslate(void)
{
	// Borramos la escena
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	// Trasladamos las proximas primitivas

	glTranslatef(0.0f, -2.5f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-2.5f, 0.0f, -3.5f);
	glVertex3f(2.5f, 0.0f, -3.5f);
	glVertex3f(2.5f, 0.0f, 1.5f);
	glVertex3f(-2.5f, 0.0f, 1.5f);
	glEnd();
	glTranslatef(0.0f, 2.5f, 0.0f);

	//glPopMatrix();

	//glPushMatrix();

	switch (dir) {
	case right:
		move_x += 0.001f;
		if (move_x > 1.5f) dir = down;
		break;
	case down:
		move_y -= 0.001f;
		if (move_y < -1.5f) dir = left;
		break;
	case left:
		move_x -= 0.001f;
		if (move_x < -1.5f) dir = up;
		break;
	case up:
		move_y += 0.001f;
		if (move_y > 1.5f) dir = right;
		break;
	}

	glTranslatef(move_x, move_y, 0.0f);
	glTranslatef(0.0f, 0.0f, -1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidCube(1);

	glColor3f(1.0f, 1.0f, 0.0f);
	glutWireCube(1);

	glTranslatef(-1.0f, 0.0f, 0.0f);
	//Esfera 1
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(0.5, 10, 10);

	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireSphere(0.5, 10, 10);
	glTranslatef(2.0f, 0.0f, 0.0f);
	//Esfera 2
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(0.5, 10, 10);

	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireSphere(0.5, 10, 10);
	glTranslatef(-1.0f, 0.0f, 1.0f);

	glPopMatrix();

	glutSwapBuffers();
}

void DisplayRotateTranslate(void)
{
	// Borramos la escena
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	// Trasladamos las proximas primitivas

	glTranslatef(0.0f, -2.5f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-2.5f, 0.0f, -3.5f);
	glVertex3f(2.5f, 0.0f, -3.5f);
	glVertex3f(2.5f, 0.0f, 1.5f);
	glVertex3f(-2.5f, 0.0f, 1.5f);
	glEnd();
	glPopMatrix();

	glPushMatrix();

	switch (dir) {
	case right:
		move_x += 0.001f;
		if (move_x > 1.5f) dir = down;
		break;
	case down:
		move_y -= 0.001f;
		if (move_y < -1.5f) dir = left;
		break;
	case left:
		move_x -= 0.001f;
		if (move_x < -1.5f) dir = up;
		break;
	case up:
		move_y += 0.001f;
		if (move_y > 1.5f) dir = right;
		break;
	}

	glTranslatef(move_x, move_y, 0.0f);
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 20.0);
	glTranslatef(0.0f, 0.0f, -1.0f);
	// Rotamos las proximas primitivas
	glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidCube(1);

	glColor3f(1.0f, 1.0f, 0.0f);
	glutWireCube(1);

	glTranslatef(-1.0f, 0.0f, 0.0f);
	//Esfera 1
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(0.5, 10, 10);

	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireSphere(0.5, 10, 10);
	glTranslatef(2.0f, 0.0f, 0.0f);
	//Esfera 2
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(0.5, 10, 10);

	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireSphere(0.5, 10, 10);
	glTranslatef(-1.0f, 0.0f, 1.0f);

	glPopMatrix();

	glutSwapBuffers();
}

// Función que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{
	// Incrementamos el ángulo
	fAngulo += 0.03f;
	// Si es mayor que dos pi la decrementamos
	if (fAngulo > 360)
		fAngulo -= 360;
	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
}

//Reshaping image
void changeSize(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	//double ratio = ((GLsizei)w / (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// si h>w tenemos que redimensionar coordenadas -y/y, usando el ratio h/w,
	//en caso contrario las coordenadas -x/x con el ratio w/h.
	if (h > w) {
		glFrustum(-1.0, 1.0, -h/(float)w, h / (float)w, 1.0, 20.0);
	}
	else {
		//ratio = ((GLsizei)h / (GLsizei)w);
		glFrustum(-w / (float)h, w / (float)h, -1.0, 1.0, 1.0, 20.0);
	}
	//gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void Keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'e':             // ESCAPE key
		exit(0);
		break;
	case 'n': //Normal
		glutDisplayFunc(Display);
		break;
	case 'r': //Rotate
		glutDisplayFunc(DisplayRotate);
		break;
	case 't': //Translate
		move_x = -1.5f;
		move_y = 1.5f;
		glutDisplayFunc(DisplayTranslate);
		break;
	case 'b': //Translate and Rotate
		move_x = -1.5f;
		move_y = 1.5f;
		glutDisplayFunc(DisplayRotateTranslate);
		break;
	}
	glutIdleFunc(Idle);
}
// Función principal
int main(int argc, char **argv)
{
	// Inicializamos la librería GLUT
	glutInit(&argc, argv);

	// Indicamos como ha de ser la nueva ventana
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	// Creamos la nueva ventana
	glutCreateWindow("Mi tercera Ventana con teclado");

	//Choose display type
	glutKeyboardFunc(Keyboard);
	//Idle
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);

	glEnable(GL_DEPTH_TEST);

	// El color de fondo será el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);
	

	// Reshape image
	glutReshapeFunc(changeSize);

	// Comienza la ejecuciÓn del core de GLUT
	glutMainLoop();
	return 0;
}