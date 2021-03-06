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

GLfloat no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_ambient_color[] = { 0.8f, 0.8f, 0.2f, 1.0f };
GLfloat mat_diffuse[] = { 0.1f, 0.5f, 0.8f, 1.0f };
GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat no_shininess[] = { 0.0f };
GLfloat low_shininess[] = { 5.0f };
GLfloat high_shininess[] = { 100.0f };
GLfloat mat_emission[] = { 0.3f, 0.2f, 0.2f, 0.0f };

const int W_WIDTH = 500; // Tamaño incial de la ventana
const int W_HEIGHT = 500;
GLfloat fAngulo; // Variable que indica el ángulo de rotación de los ejes. 

GLfloat lp[] = { 0.0f, 0.0f, 2.5f, 1.0f }; //light position
//tipos de luz
enum Mat { mamb, mdiff, mspec, memi };
Mat m = mamb;

//shademodel; 1= smooth, 0=flat
int shade = 1;
//Coordinates
double x_r = 0.0, y_r = 0.0, z_r = -1.0;
double eyeX = 0.0, eyeY = 0.0, eyeZ = 5.0;
GLdouble upX = 0.0, upY = 1.0, upZ = 0.0;

void setMaterial() {
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	switch (m) {
	case mamb:
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		break;
	case mdiff:
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		break;
	case mspec:
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		break;
	case memi:
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
		break;
	}
}

void base() {
	glPushMatrix();
	setMaterial();
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
	glTranslatef(0.0f, -2.5f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(0.31f, 0.0f, 0.31f);
	glNormal3f(0.0f, 1.0f, 0.0f);
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
	setMaterial();
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
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
	setMaterial();
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.5, 100, 100);
	glColor3f(1.0f, 0.0f, 1.0f);
	glPopMatrix();
}

void esferaGrande() {
	glPushMatrix();
	setMaterial();
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
	glColor3f(0.0f, 0.5f, 1.0f);
	glutSolidTorus(0.5, 1, 100, 100);
	glColor3f(0.0f, 0.0f, 1.0f);
	glPopMatrix();
}


//Mostramos la figura y la rotamos
void DisplayRotate(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, x_r, y_r, 5.0 + z_r, upX, upY, upZ);
	
    glLightfv(GL_LIGHT0, GL_POSITION, lp);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, mat_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);

	glPushMatrix();
	base();

	glPushMatrix();
	glTranslatef(lp[0], lp[1], lp[2]); //movemos la esfera que representa el origen de la luz
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.02, 10, 10);

	glPopMatrix();
	
	//Cubo
	glPushMatrix();
	glRotatef(fAngulo, 0.0f, 1.0f, 0.0f);
	cubo();
	glPopMatrix();
	
	//Esferas
	glPushMatrix();
	glRotatef(fAngulo, 0.0f, 1.0f, 0.0f);
	glTranslatef(-2.0f, 0.0f, 0.0f);
	//Esfera 1
	esferaPequeña();
	glTranslatef(4.0f, 0.0f, 0.0f);
	//Esfera 2
	esferaPequeña();
	glPopMatrix();
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
}

void SpecialKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1: //Ambient Maerial
		m = mamb;
		break;
	case GLUT_KEY_F2: //Diffuse Material
		m = mdiff;
		break;
	case GLUT_KEY_F3: //Specular Material
		m = mspec;
		break;
	case GLUT_KEY_F4: //Emission Material
		m = memi;
		break;
	}
	cout << m;
}

void Keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'a':
		lp[0] += 0.05;
		break;
	case 's': 
		lp[1] += 0.05;
		break;
	case 'd':
		lp[2] += 0.05;
		break;
	case 'z':
		lp[0] -= 0.05;
		break;
	case 'x':
		lp[1] -= 0.05;
		break;
	case 'c':
		lp[2] -= 0.05;
		break;
	case '+': //Encender luces
		glEnable(GL_LIGHTING);
		break;
	case '-': //Apagar luces
		glDisable(GL_LIGHTING);
		break;
	case ' ': //Cambiar sombreado
		if (shade == 1) {
			glShadeModel(GL_FLAT);
			shade = 0;
		}
		else {
			glShadeModel(GL_SMOOTH);
			shade = 1;
		}
		break;
	}
	cout << lp[0];
	cout << "\n";
	cout << lp[1];
	cout << "\n";
	cout << lp[2];
	cout << "\n";

}

void init(void)
{
	glShadeModel(GL_SMOOTH);
	//Inicializacion de la luz por defecto
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
	//Control keyboard for camera
	glutSpecialFunc(SpecialKeyboard);
	glutKeyboardFunc(Keyboard);
	//Idle
	glutDisplayFunc(DisplayRotate);
	glutIdleFunc(Idle);

	//glEnable(GL_DEPTH_TEST);

	init();
	// El color de fondo será el negro (RGBA, RGB + Alpha channel)
	glClearColor(0.31f, 0.31f, 0.31f, 1.0f);

	// Reshape image
	glutReshapeFunc(changeSize);

	// Comienza la ejecuciÓn del core de GLUT
	glutMainLoop();
	return 0;
}