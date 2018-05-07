// Etapa4.cpp
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


const int W_WIDTH = 500; // Tamaño incial de la ventana
const int W_HEIGHT = 500;
GLfloat fAngulo; // Variable que indica el ángulo de rotación de los ejes. 
const double PI = 3.1415926535897932384626433832795;
GLdouble phi = -90.0;
GLdouble theta = 0.0;
GLdouble phi_r = 0.0;
GLdouble theta_r = 0.0;

//Coordinates
double x_r = 0.0, y_r = 0.0, z_r = -1.0;
double eyeZ = 5.0;
GLdouble upX = 0.0, upY = 1.0, upZ = 0.0;


//Mostramos la figura y la rotamos
void DisplayRotate(void)
{
	// Borramos la escena
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//???????????????????????????????????
	glLoadIdentity();
	gluLookAt(0.0, 0.0, eyeZ, x_r, y_r, 5.0 + z_r, upX, upY, upZ);

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
	case GLUT_KEY_LEFT:
		phi += 1;
		break;
	case GLUT_KEY_RIGHT:
		phi -= 1;
		break;
	case GLUT_KEY_UP:
		theta -= 1;
		break;
	case GLUT_KEY_DOWN:
		theta += 1;
	}
	//Transformar coordenadas esfericas a cartesianas
	theta_r = (theta * PI) / 180;
	phi_r = (phi * PI) / 180;
	x_r = cos(theta_r)*cos(phi_r);
	y_r = sin(theta_r);
	z_r = sin(phi_r)*cos(theta_r);
	cout << "x :";
	cout << x_r;
	cout << " y :";
	cout << y_r;
	cout << " z :";
	cout << z_r;
	cout << " phi :";
	cout << phi;
	cout << " theta :";
	cout << theta;
	cout << "\n";
}

void Keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case '+': //Normal
		eyeZ += 1.0;
		break;
	case '-': //Rotate
		eyeZ -= 1.0;
		break;
	}
	cout << "x :";
	cout << x_r;
	cout << " y :";
	cout << y_r;
	cout << " z :";
	cout << z_r;
	cout << " phi :";
	cout << phi;
	cout << " theta :";
	cout << theta;
	cout << "\n";
	//glutIdleFunc(Idle);
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

	glEnable(GL_DEPTH_TEST);

	// El color de fondo será el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Reshape image
	glutReshapeFunc(changeSize);

	// Comienza la ejecuciÓn del core de GLUT
	glutMainLoop();
	return 0;
}