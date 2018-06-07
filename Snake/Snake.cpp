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
const int s = 12;
Estado m[s][s]; //Tablero del juego
int headX, headY;
int iter = 0;
int MAX_ITER = 500;
bool decrease = false;
serpiente nodelist;
tuple<int, int> a;
int x_obj, y_obj;
int puntuacion;
double eyeX = 0.0, eyeY = 0.0, eyeZ = 5.0;

void base() {
	glPushMatrix();
	glBegin(GL_QUADS);
	glTranslatef(s / 2 + 0.5, 0.0f, s / 2 + 0.5);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-s/2-0.1, 0.0f, -s/2);
	glVertex3f(-s/2, 0.0f, s/2);
	glVertex3f(s/2, 0.0f, s/2);
	glVertex3f(s/2, 0.0f, -s/2);
	glEnd();
	glPopMatrix();
}

void esferaPequeña(int x, int y, int z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glutSolidSphere(0.6, 10, 10);
	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireSphere(0.6, 10, 10);
	glPopMatrix();
}

void escenario(GLfloat x, GLfloat z) {
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(x, 0.0f, z);
	glVertex3f(x, 0.0f, z + 0.95);
	glVertex3f(x + 0.95, 0.0f, z + 0.95);
	glVertex3f(x + 0.95, 0.0f, z);
	glEnd();
	glPopMatrix();
}

void matrix(int n) {
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(s/2+0.5, (s/2+0.5)-12, 2.0f);

	int y = -s;
	for (int i = 0; i < n; i++, y += 0.01) {
		int x = -s;
		for (int j = 0; j < n; j++, x += 0.01) {
			switch (m[i][j]) {
			case vacio:
				glColor3f(0.0f, 0.0f, 0.0f);
				escenario(x - 0.5, y - 0.5);
				break;
			case bola:
				glColor3f(0.0f, 0.0f, 1.0f);
				esferaPequeña(x-1+0.25, 1.0f, y-1+0.25);
				break;
			case objeto:
				glColor3f(0.0f, 1.0f, 0.0f);
				esferaPequeña(x - 1 + 0.25, 0.0f, y - 1 + 0.25);
				break;
			}
		}
	}
	if (iter == 0) iter = 1;
	glPopMatrix();
}

void actMatrix() {
	Nodo* n = nodelist.get_first();
	while (n != NULL) {
		m[n->x][n->y] = bola;
		n = n->next;
	}
	m[x_obj][y_obj] = objeto;
}

// Función que visualiza la escena OpenGL
void Display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	matrix(s);
	base();
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
				headX--;
				break;
			case rght:
				headY++;
				break;
			case down:
				headX++;
				break;
			case lft:
				headY--;
		}
		//Detección de colisión: Game Over
		if (headX < 0 || headX > s-1 || headY < 0 || headY > s-1 || m[headX][headY] == bola) {
			cout << "Game Over\n";
			exit(0);
		}
		//Detección de colisión: Objeto
		if (headX == x_obj && headY == y_obj) {
			//Actualizamos puntuacion
			puntuacion++;
			//Incrementamos de tamaño la serpiente
			nodelist.addBola();

			//Generamos siguiente objeto
			x_obj = rand() % 12;
			y_obj = rand() % 12;
			m[x_obj][y_obj] = vacio;
			while (m[x_obj][y_obj] == bola) x_obj = rand() % 12; y_obj = rand() % 12;
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
		gluPerspective(120.0, (GLfloat)h / (GLfloat)w, 1.0, 100.0);
	}
	else {
		//ratio = ((GLsizei)h / (GLsizei)w);
		gluPerspective(120.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void setEye(double x, double y, double z) {
	eyeX = x;
	eyeY = y;
	eyeZ = z;
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
	case GLUT_KEY_F2: //Contrapicado
		setEye(0.0, -5.0, 5.0);
		break;
	case GLUT_KEY_F3:

		break;
	}
	glutIdleFunc(Idle);
}

void init() {
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			m[i][j] = vacio;
		}
	}
	//x e y estan invertidos, ojo
	headX = 5;
	headY = 5;
	nodelist = serpiente(headX, headY);
	nodelist.addBola();

	//Generamos el primer objeto
	x_obj = rand() % 12;
	y_obj = rand() % 12;
	while(x_obj == 5 && y_obj == 5) x_obj = rand() % 12; y_obj = rand() % 12;
	cout << "x_obj: " << x_obj << "\n";
	cout << "y_obj: " << y_obj << "\n";
	actMatrix();
	
	//Movimiento inicial de la serpiente
	dir = rght;

	//Puntuación
	puntuacion = 0;
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