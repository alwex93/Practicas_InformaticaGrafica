// Fichero principal 
////////////////////////////////////////////////////
#include "stdafx.h"
#include "glut.h"
#include "Estado.h"
#include "Direction.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

const int W_WIDTH = 800; // Tamaño incial de la ventana
const int W_HEIGHT = 610;
GLfloat fAngulo; // Variable que indica el ángulo de rotación de los ejes. 
GLfloat move_x;
GLfloat move_y;
Direction dir;
const int s = 10;
Estado m[s][s]; //Tablero del juego
int headX, headY, prevX, prevY;


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

void esferaPequeña(int x, int y, int z) {
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(0.4, 10, 10);
	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireSphere(0.4, 10, 10);
	glPopMatrix();
}

void matrix(int n) {
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(5.0, 5.0, -2.0f);

	glBegin(GL_QUADS);
	int y = -s;
	for (int i = 0; i < n; i++) {
		int x = -s;
		for (int j = 0; j < n; j++) {
			switch (m[i][j]) {
			case vacio:
				glColor3f(1.0f, 0.0f, 0.0f);
				break;
			case bola:
				glColor3f(0.0f, 0.0f, 1.0f);
				break;
			case objeto:
				glColor3f(0.0f, 1.0f, 0.0f);
				break;
			}
			glVertex2f(x-0.5, y-0.5);
			glVertex2f(x-0.5, y + 0.95-0.5);
			glVertex2f(x-0.5 + 0.95, y-0.5 + 0.95);
			glVertex2f(x-0.5 + 0.95, y-0.5);

			x += 0.01;
		}
		y += 0.01;
	}
	glEnd();
}
// Función que visualiza la escena OpenGL
void Display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	//base();
	//Cubo central
	//cubo();
	matrix(s);
	glPopMatrix();
	glutSwapBuffers();

	switch (dir) {
	case up:
		if (headX != 9) {
			m[prevX][prevY] = vacio;
			headX++;
			m[headX][headY] = bola;
			prevX = headX;
		}
		break;
	case rght:
		if (headY != 9) {
			m[prevX][prevY] = vacio;
			headY++;
			m[headX][headY] = bola;
			prevY = headY;
		}
		break;
	case down:
		if (headX != 0) {
			m[prevX][prevY] = vacio;
			headX--;
			m[headX][headY] = bola;
			prevX = headX;
		}
		break;
	case lft:
		if (headY != 0) {
			m[prevX][prevY] = vacio;
			headY--;
			m[headX][headY] = bola;
			prevY = headY;
		}
	}
}

void init() {
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			m[i][j] = vacio;
		}
	}
	//m[5][5] = bola;
	//x e y estan invertidos, ojo
	m[9][1] = bola;
	headX = 9; prevX = 9;
	headY = 0; prevY = 0;
	dir = rght;
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
	//double ratio = ((GLsizei)w / (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// si h>w tenemos que redimensionar coordenadas -y/y, usando el ratio h/w,
	//en caso contrario las coordenadas -x/x con el ratio w/h.
	if (h > w) {
		glFrustum(-1.0, 1.0, -h / (float)w, h / (float)w, 1.0, 20.0);
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
	case GLUT_KEY_LEFT:
		if (dir != rght) {
			dir = lft;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (dir != lft) {
			dir = rght;
		}
		break;
	case GLUT_KEY_UP:
		if (dir != down) {
			dir = up;
		}
		break;
	case GLUT_KEY_DOWN:
		if (dir != up) {
			dir = down;
		}
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
	glutCreateWindow("Snake");

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

	init(); //creamos el tablero, que es una matriz

	// Comienza la ejecuciÓn del core de GLUT
	glutMainLoop();
	return 0;
}