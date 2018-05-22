// Etapa3.cpp
// Fichero principal 
////////////////////////////////////////////////////
#include "stdafx.h"
#include "glut.h"
#include "List.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

const int W_WIDTH = 500; // Tamaño incial de la ventana
const int W_HEIGHT = 500;
GLfloat fAngulo; // Variable que indica el ángulo de rotación de los ejes. 
GLfloat move_x;
GLfloat move_y;
enum Direction { up, down, lft, rght };
Direction dir;
GLfloat cabezaX = 0.0f, colaX = (cabezaX + 0.5f) * 4;
GLfloat cabezaY = -0.5f, colaY = cabezaY;
Nodo2 n1, n2; //n1 es el primer nodo, n2 el segundo
float init_x = 0.0;
float init_y = 0.0;
list nodelist;

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

void esferaPequeña(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(0.5, 10, 10);
	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireSphere(0.5, 10, 10);
	glPopMatrix();
}

// Función que visualiza la escena OpenGL
void Display(void) {
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	GLfloat d = 0.0f;
	base();
	/*
	cabezaX += move_x;
	cabezaY += move_y;
	glTranslatef(cabezaX, cabezaY, 0.0f);
	for (int i = 0; i < 4; i++) {
		esferaPequeña(cabezaX + d, cabezaY, 0.0f);
		d += 0.5f;
	}*/
	
	Nodo2 *temp = new Nodo2;
	temp = nodelist.get_first();
	GLfloat a = temp->x + move_x;
	GLfloat b = temp->y + move_y;
	glTranslatef(a, b, 0.0f);
	while (temp != NULL) {
		cout << temp->x;
		cout << "\n";
		cout << temp->y;
		cout << "\n";
		a = temp->x += move_x;
		b = temp->y += move_y;
		esferaPequeña(a, b, 0.0f);
		temp = temp->next;
	}

	glPopMatrix();
	glutSwapBuffers();
}

void init() {
	nodelist.createnode(init_x, init_y);
	nodelist.createnode(init_x - 0.5, init_y);
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

void Keyboard(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_LEFT:
		dir = lft;
		move_x = -0.001;
		move_y = 0;
		break;
	case GLUT_KEY_RIGHT:
		dir = rght;
		move_x = 0.001;
		move_y = 0;
		break;
	case GLUT_KEY_UP:
		dir = up;
		move_x = 0;
		move_y = 0.001;
		break;
	case GLUT_KEY_DOWN:
		dir = down;
		move_x = 0;
		move_y = -0.001;
		break;
	case GLUT_KEY_F1:
		Nodo2 * temp = new Nodo2;
		temp = nodelist.get_last();
		nodelist.createnode(temp->x - 0.5, temp->y);
	break;
	}
	glutIdleFunc(Idle);
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

// Función principal
int main(int argc, char **argv)
{
	move_x = 0.001;
	// Inicializamos la librería GLUT
	glutInit(&argc, argv);

	// Indicamos como ha de ser la nueva ventana
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	// Creamos la nueva ventana
	glutCreateWindow("Snake");

	//Choose display type
	glutSpecialFunc(Keyboard);
	//Idle
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);

	glEnable(GL_DEPTH_TEST);

	// El color de fondo será el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


	// Reshape image
	glutReshapeFunc(changeSize);

	init(); //Crea los primeros nodos de la serpiente

	// Comienza la ejecuciÓn del core de GLUT
	glutMainLoop();
	return 0;
}