// Etapa5.cpp
// Fichero principal 
////////////////////////////////////////////////////
#include "stdafx.h"
#include "glut.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
using namespace std;

GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat no_shininess[] = { 0.0 };
GLfloat low_shininess[] = { 5.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };

const int W_WIDTH = 500; // Tamaño incial de la ventana
const int W_HEIGHT = 500;
GLfloat fAngulo; // Variable que indica el ángulo de rotación de los ejes. 
const double PI = 3.1415926535897932384626433832795;
GLdouble phi = -90.0;
GLdouble theta = 0.0;
GLdouble phi_r = 0.0;
GLdouble theta_r = 0.0;
bool rot = false;
GLfloat move_x;
GLfloat move_y;
enum Direction { up, down, left, right };
Direction dir;

GLfloat lp[] = { 0.0, 0.0, 1.5, 1.0 }; //cambiar 1.5 a 0 para ver mejor luz

//Coordinates
double x_r = 0.0, y_r = 0.0, z_r = -1.0;
double eyeX = 0.0, eyeY = 0.0, eyeZ = 5.0;
GLdouble upX = 0.0, upY = 1.0, upZ = 0.0;

void base() {
	glPushMatrix();
	glTranslatef(0.0f, -2.5f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-2.5f, 0.0f, -2.5f);
	glVertex3f(2.5f, 0.0f, -2.5f);
	glVertex3f(2.5f, 0.0f, 2.5f);
	glVertex3f(-2.5f, 0.0f, 2.5f);
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
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	//glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	//glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
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

//No sabemos porque right y left es ambiguo
Direction getDir() {
	switch (dir) {
	case right: //cambiar por 3
		move_x += 0.01f;
		break;
	case down:
		move_y -= 0.01f;
		break;
	case left: //cambiar por 2
		move_x -= 0.01f;
		break;
	case up:
		move_y += 0.01f;
		break;
	}
	return dir;
}

//Mostramos la figura y la rotamos
void DisplayRotate(void)
{
	// Borramos la escena
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	dir = getDir();
	//Insertamos luz, va aqui?
	//glEnable(GL_LIGHT0);
	//glLightf(GL_LIGHT0, GL_AMBIENT, (0, 0, 0, 1));
	//glEnable(GL_COLOR_MATERIAL);
	//glColorMaterial(GL_FRONT, GL_DIFFUSE);
	//Rotamos escena
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, x_r, y_r, 5.0 + z_r, upX, upY, upZ);
	
	glPushMatrix();
	base();

	glTranslatef(move_x, move_y, 0.0f);
	glPushMatrix();
	//glRotated(fAngulo, 1.0, 0.0, 0.0);
	glutSolidSphere(0.05, 10, 10);
	glLightfv(GL_LIGHT0, GL_POSITION, lp);

	glPopMatrix();
	//Cubo
	glPushMatrix();
	glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
	esferaGrande();
	glPopMatrix();
	/*
	//Esferas
	glPushMatrix();
	glRotatef(fAngulo, 0.0f, 1.0f, 1.0f);
	glTranslatef(-2.0f, 0.0f, 0.0f);
	//Esfera 1
	esferaPequeña();
	glTranslatef(4.0f, 0.0f, 0.0f);
	//Esfera 2
	esferaPequeña();
	glPopMatrix();

	//Toros
	glPushMatrix();
	glRotatef(fAngulo, 0.0f, -1.0f, -1.0f);
	glTranslatef(-2.0f, 0.0f, 0.0f);
	esferaGrande();

	glTranslatef(4.0f, 0.0f, 0.0f);
	esferaGrande();
	glPopMatrix();
	*/
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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void SpecialKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1: //Ambient
		break;
	case GLUT_KEY_F2: //Diffuse
		break;
	case GLUT_KEY_F3: //Specular
		break;
	case GLUT_KEY_F4: //Emission
		break;
	}
	//Transformar coordenadas esfericas a cartesianas
	theta_r = (theta * PI) / 180;
	phi_r = (phi * PI) / 180;
	x_r = cos(theta_r)*cos(phi_r);
	y_r = sin(theta_r);
	z_r = sin(phi_r)*cos(theta_r);
}

void Keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'a':
		lp[0] += 0.5;
		break;
	case 's': 
		lp[1] += 0.5;
		break;
	case 'd':
		lp[2] += 0.5;
		break;
	case 'z':
		lp[0] -= 0.5;
		break;
	case 'x':
		lp[1]  -= 0.5;
		break;
	case 'c':
		lp[2] -= 0.5;
		break;
	}
}

void init(void)
{
	
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	//glShadeModel(GL_SMOOTH);

	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_DEPTH_TEST);
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
	glutCreateWindow("Mi cuarta Ventana con teclado");

	//Choose display type
	//glutKeyboardFunc(Keyboard);
	//Control keyboard for camera
	glutSpecialFunc(SpecialKeyboard);
	glutKeyboardFunc(Keyboard);
	//Idle
	glutDisplayFunc(DisplayRotate);
	glutIdleFunc(Idle);

	//glEnable(GL_DEPTH_TEST);

	init();
	//Habilitamos renderización con luz
	/*
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL); //Objeto refleja luz
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE); //Inicializacion
	*/

	// El color de fondo será el negro (RGBA, RGB + Alpha channel)
	glClearColor(0.31f, 0.31f, 0.31f, 1.0f);

	// Reshape image
	glutReshapeFunc(changeSize);

	// Comienza la ejecuciÓn del core de GLUT
	glutMainLoop();
	return 0;
}