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

void base() {
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
}

void cubo() {
	glPushMatrix();
	glBegin(GL_QUADS);
	glTranslatef(0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidCube(1);
	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireCube(1);
	glTranslatef(0.0f, 0.0f, -1.0f);
	glEnd();
	glPopMatrix();
}

void esferaPequeña() {
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(0.5, 10, 10);
	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireSphere(0.5, 10, 10);
	glPopMatrix();
}

void esferaGrande() {
	glPushMatrix();
	glColor3f(0.0f, 0.5f, 1.0f);
	glutSolidTorus(0.5, 1, 10, 10);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutWireTorus(0.5, 1, 10, 10);
	glPopMatrix();
}

// Función que visualiza la escena OpenGL
void Display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	base();
	//Cubo central
	cubo();
	glTranslatef(-2.0f, 0.0f, 0.0f);
	//Esfera Izquierda
	esferaGrande();
	esferaPequeña();
	glTranslatef(4.0f, 0.0f, 0.0f);
	//Esfera derecha
	esferaGrande();
	esferaPequeña();

	glPopMatrix();
	glutSwapBuffers();
}

//Mostramos la figura y la rotamos
void DisplayRotate(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	base();
	glPushMatrix();
	//Cubo central
	glRotatef(fAngulo, 1.0f, 0.0f, 0.0f);
	cubo();
	glPopMatrix();

	//Esferas pequeñas
	glPushMatrix();
	glRotatef(fAngulo, 0.0f, 1.0f, 1.0f);
	//Esfera pequeña Izquierda
	glTranslatef(-2.0f, 0.0f, 0.0f);
	esferaPequeña();
	glTranslatef(4.0f, 0.0f, 0.0f);
	//Esfera pequeña Derecha
	esferaPequeña();
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(fAngulo, 0.0f, -1.0f, -1.0f);
	//Esfera grande izquierda
	glTranslatef(-2.0f, 0.0f, 0.0f);
	esferaGrande();
	//Esfera grande derecha
	glTranslatef(4.0f, 0.0f, 0.0f);
	esferaGrande();
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}

Direction getDir() {
	switch (dir) {
	case right:
		move_x += 0.01f;
		if (move_x > 1.5f) return down;
		break;
	case down:
		move_y -= 0.01f;
		if (move_y < -1.5f) return left;
		break;
	case left:
		move_x -= 0.01f;
		if (move_x < -1.5f) return up;
		break;
	case up:
		move_y += 0.01f;
		if (move_y > 1.5f) return right;
		break;
	}
	return dir;
}

void DisplayTranslate(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	dir = getDir();
	glPushMatrix();

	base();
	glTranslatef(move_x, move_y, 0.0f);
	//Cubo central
	cubo();
	glTranslatef(1.0f, 0.0f, 0.0f);
	//Esfera izquierda
	esferaPequeña();
	glTranslatef(-2.0f, 0.0f, 0.0f);
	//Esfera derecha
	esferaPequeña();
	glTranslatef(4.0f, 0.0f, 0.0f);

	glPopMatrix();
	glutSwapBuffers();
}

void DisplayRotateTranslate(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	dir = getDir();
	glPushMatrix();

	base();
	glTranslatef(move_x, move_y, 0.0f);
	glRotatef(fAngulo, 1.0f, 0.0f, 0.0f);
	cubo();
	glTranslatef(-1.0f, 0.0f, 0.0f);
	//Esfera izquierda
	esferaPequeña();
	glTranslatef(2.0f, 0.0f, 0.0f);
	//Esfera derecha
	esferaPequeña();
	glTranslatef(-1.0f, 0.0f, 1.0f);

	glPopMatrix();
	glutSwapBuffers();
}

// Función que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{
	// Incrementamos el ángulo
	fAngulo += 0.5f;
	// Si es mayor que dos pi la decrementamos
	if (fAngulo > 360)
		fAngulo -= 360;
	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
}

//Reshaping image
void changeSize(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// si h>w tenemos que redimensionar coordenadas -y/y, usando el ratio h/w,
	//en caso contrario las coordenadas -x/x con el ratio w/h.
	if (h > w) {
		glFrustum(-1.0, 1.0, -h/(float)w, h / (float)w, 1.0, 20.0);
	}
	else {
		glFrustum(-w / (float)h, w / (float)h, -1.0, 1.0, 1.0, 20.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void Keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'e':// ESCAPE key
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
	// Reshape image
	glutReshapeFunc(changeSize);
	// Comienza la ejecuciÓn del core de GLUT
	glutMainLoop();
	return 0;
}