// Fichero principal 
////////////////////////////////////////////////////
#include "stdafx.h"
#include "glut.h"
#include "Estado.h"
#include "Direction.h"
#include "Serpiente.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <tuple>
using namespace std;

const int W_WIDTH = 800; // Tamaño incial de la ventana
const int W_HEIGHT = 610;
GLfloat fAngulo; // Variable que indica el ángulo de rotación de los ejes. 
GLfloat move_x;
GLfloat move_y;
Direction dir;
const int s = 10;
Estado m[s][s]; //Tablero del juego
int headX, headY;
int iter = 0;
int MAX_ITER = 1000;
bool decrease = false;
serpiente nodelist;
tuple<int, int> a;


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
	glTranslatef(x, y, z);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(0.6, 10, 10);
	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireSphere(0.6, 10, 10);
	glPopMatrix();
}

void escenario(GLfloat x, GLfloat y) {
	glBegin(GL_QUADS);
	glVertex3f(x, y, 0.0f);
	glVertex3f(x, y + 0.95, 0.0f);
	glVertex3f(x + 0.95, y + 0.95, 0.0f);
	glVertex3f(x + 0.95, y, 0.0f);
	glEnd();
}

void matrix(int n) {
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(5.0, 5.0, -2.0f);

	int y = -s;
	for (int i = 0; i < n; i++, y += 0.01) {
		int x = -s;
		for (int j = 0; j < n; j++, x += 0.01) {
			switch (m[i][j]) {
			case vacio:
				glColor3f(1.0f, 0.0f, 0.0f);
				escenario(x - 0.5, y - 0.5);
				break;
			case bola:
				glColor3f(0.0f, 0.0f, 1.0f);
				esferaPequeña(x-1+0.25, y-1+0.25, 0.0f);
				break;
			case objeto:
				glColor3f(0.0f, 1.0f, 0.0f);
				break;
			}
		}
	}
	if (iter == 0) iter = 1;
}

void actMatrix() {
	Nodo* n = nodelist.get_first();
	while (n != NULL) {
		m[n->x][n->y] = bola;
		n = n->next;
	}
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
}

// Función que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{
	// Incrementamos el ángulo
	fAngulo += 0.5f;
	// Si es mayor que dos pi la decrementamos
	if (fAngulo > 360) fAngulo -= 360;

	if (iter != 0) {
		iter++;
		if (iter == MAX_ITER+1) {
			iter = 0;
			if (decrease) MAX_ITER /= 2; decrease = false;
		}
	}
	if (iter == MAX_ITER) {
		switch (dir) {
			case up:
				headX++;
				break;
			case rght:
				headY++;
				break;
			case down:
				headX--;
				break;
			case lft:
				headY--;
		}
		//
		if (headX < 0 || headX > 9 || headY < 0 || headY > 9 || m[headX][headY] == bola) {
			cout << "Game Over\n";
			exit(0);
		}
		Nodo* c = nodelist.get_last();
		m[c->x][c->y] = vacio;
		a = nodelist.move(headX, headY);
		actMatrix();
	}
	

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

void SpecialKeyboard(int key, int x, int y) {
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
	case GLUT_KEY_F1:
		decrease = true;
		break;
	case GLUT_KEY_F2:
		nodelist.addBola();
		nodelist.printlist();
	}

	glutIdleFunc(Idle);
}

void init() {
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			m[i][j] = vacio;
		}
	}
	//m[5][5] = bola;
	//x e y estan invertidos, ojo
	headX = 4;
	headY = 5;
	nodelist = serpiente(headX, headY);
	actMatrix();
	//m[9][1] = bola;
	dir = rght;
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

	//Choose movement
	glutSpecialFunc(SpecialKeyboard);

	glutDisplayFunc(Display);

	//Idle
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