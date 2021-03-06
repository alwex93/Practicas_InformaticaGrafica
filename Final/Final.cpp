// Etapa3.cpp
// Fichero principal 
////////////////////////////////////////////////////
#include "stdafx.h"
#include "glut.h"
#include "List.h"
#include "Direction.h"
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
Direction dir = rght;
GLfloat cabezaX = 0.0f, colaX = cabezaX;
GLfloat cabezaY = 0.0f, colaY = cabezaY;
Nodo n1, n2; //n1 es el primer nodo, n2 el segundo
float init_x = 0.0;
float init_y = 0.0;
list nodelist;
int r_model; //Random para la generación de objetos a comer
int iter = 0;
int MAX_ITER = 1000;

//Posiciones para los objetos bonus
GLfloat x_mod = 0.0f;
GLfloat y_mod = 0.0f;
GLfloat z_mod = 0.0f;

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

void drawOctahedro(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(fAngulo, 1.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
	glutSolidOctahedron();
	glTranslatef(-x, -y, -z);
	glPopMatrix();
}

void drawTorus(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(fAngulo, 1.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidTorus(0.2, 0.3, 100, 100);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void drawCube(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(fAngulo, 1.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidCube(0.5);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void drawCone(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(fAngulo, 1.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidCone(0.2, 0.3, 100, 100);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void drawTetrahedro(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(fAngulo, 1.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidTetrahedron();
	glColor3f(1.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void drawTetera(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(fAngulo, 1.0f, 0.0f, 1.0f);
	glColor3f(0.15f, 0.15f, 0.0f);
	glutSolidTeapot(0.5);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void drawRectangle(float x, float y, float width, float height) {
	glBegin(GL_POLYGON);
	glVertex3f(x - width, y - height, 0.0);
	glVertex3f(x - width, y + height, 0.0);
	glVertex3f(x + width, y + height, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x - width, y - height, 0.0);
	glVertex3f(x + width, y - height, 0.0);
	glVertex3f(x + width, y + height, 0.0);
	glEnd();
}

void drawMatrix() {
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	//for (int i = 0; i < 1; i++) {
		glBegin(GL_QUADS);
		glVertex3f(-2.0f, -2.0f, 3.0f);
		glVertex3f(2.0f, 2.0f, 3.0f);
		glVertex3f(-2.0f, 2.0f, 3.0f);
		glVertex3f(2.0f, -2.0f, 3.0f);
		glEnd();
	//}
	glPopMatrix();
}
//Objeto Bonus
void generateObject() {
	if (r_model == 0) return;
	
	switch (r_model) {
	case 1:
		drawOctahedro(x_mod, y_mod, z_mod);
		break;
	case 2:
		drawTorus(x_mod, y_mod, z_mod);
		break;
	case 3:
		drawCube(x_mod, y_mod, z_mod);
		break;
	case 4:
		drawCone(x_mod, y_mod, z_mod);
		break;
	case 5: 
		drawTetrahedro(x_mod, y_mod, z_mod);;
		break;
	case 6:
		drawTetera(x_mod, y_mod, z_mod);
	}
	if (iter == 0) iter = 1;
}

Direction cambio(bool c) {
	if (c){
		return static_cast<Direction>((dir + 1) % sentinel);
	}
	else {
		return static_cast<Direction>((dir - 1) % sentinel);
	}
}
// Función que visualiza la escena OpenGL
void Display(void) {
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glPushMatrix();
	generateObject();
	glPopMatrix();

	base();
	
	Nodo *serpiente = nodelist.get_first();
	GLfloat x;
	GLfloat y;
	drawMatrix();
	glTranslatef(cabezaX, cabezaY, 0.0f);
	/*for (int i = 0; i < nodelist.get_bolas(); i++) {
		int pos = nodelist.isHead(x, y);
		//cout << pos;
		if (pos != -1) {
			dir = cambio(nodelist.get_dir(pos));
		}
		 x = serpiente->x;
		 y = serpiente->y;
		switch (dir) {
		case (up):
			esferaPequeña(x, y - 0.5, 0.0f);
			y -= 0.5;
			break;
		case (down):
			esferaPequeña(x, y + 0.5, 0.0f);
			y += 0.5;
			break;
		case (lft):
			esferaPequeña(x + 0.5, y, 0.0f);
			x += 0.5;
			break;
		case (rght):
			esferaPequeña(x - 0.5, y, 0.0f);
			x -= 0.5;
		}
		serpiente = serpiente->next;
	}
	colaX = x;
	colaY = y;*/
	glPopMatrix();
	glutSwapBuffers();
}

void init() {
	//nodelist.createnode(init_x, init_y, true);
	nodelist = list();
	nodelist.createnode(0.0, 0.0, false);
	nodelist.createnode(-0.5, 0.0, false);	
	nodelist.createnode(-1.0, 0.0, false);
	nodelist.createnode(-1.5, 0.0, false);

	move_x = 0.001;
	move_y = 0;
}

// Función que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{
	cabezaX += move_x;
	cabezaY += move_y;
	// Incrementamos el ángulo
	fAngulo += 0.5f;
	if (iter != 0) {
		iter++;
		if (iter == MAX_ITER) {
			iter = 0;
			r_model = 0;
		}
	}
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
		if (dir != rght) {
			dir = lft;
			move_x = -0.001;
			move_y = 0;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (dir != lft) {
			dir = rght;
			move_x = 0.001;
			move_y = 0;
		}
		break;
	case GLUT_KEY_UP:
		if (dir != down) {
			dir = up;
			move_x = 0;
			move_y = 0.001;
		}
		break;
	case GLUT_KEY_DOWN:
		if (dir != up) {
			dir = down;
			move_x = 0;
			move_y = -0.001;
		}
		break;
	case GLUT_KEY_F1:
		nodelist.createnode(colaX, colaY, false);
		break;
	case GLUT_KEY_F2:
		x_mod = (4.0 * float(rand()) / float(RAND_MAX)) - 1.0;
		y_mod = (4.0 * float(rand()) / float(RAND_MAX)) - 1.0;
		z_mod = 0.0f;
		r_model = r_model == 0 ? (rand() % 7) + 1 : r_model;
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