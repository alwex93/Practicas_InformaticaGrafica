// Etapa2.cpp
// Fichero principal 
////////////////////////////////////////////////////
#include "stdafx.h"
#include "glut.h"
#include <GL/gl.h>
#include <GL/glu.h>
const int W_WIDTH = 640; // Tama�o incial de la ventana
const int W_HEIGHT = 480;
GLfloat fAnguloInt, fAnguloExt; // Variable que indica el �ngulo de rotaci�n de los ejes.
const GLfloat constAdd = 0.3f;
bool dir;
GLfloat add;

// dibuja un rectangulo donde (x, y) es su punto central
void drawRectangle(float x, float y, float width, float height) {
	glBegin(GL_POLYGON);
	glVertex3f(x - width, y - height, -1.5);
	glVertex3f(x - width, y + height, -1.5);
	glVertex3f(x + width, y + height, -1.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x - width, y - height, -1.5);
	glVertex3f(x + width, y - height, -1.5);
	glVertex3f(x + width, y + height, -1.5);
	glEnd();
}

// Función que visualiza la escena OpenGL
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(fAnguloInt, 0.0f, 0.0f, 1.0f);

	glPushMatrix();

	glColor3f(0.0f, 0.0f, 0.0f);
	drawRectangle(0.0f, 0.0f, 0.009f, 0.1f);

	glColor3f(0.0f, 1.0f, 0.0f);
	drawRectangle(0.0f, -0.2f, 0.1f, 0.1f);

	glRotatef(fAnguloInt, 0.0f, 0.2f, 1.0f);

	glColor3f(0.0f, 0.0f, 0.0f);
	drawRectangle(0.0f, -0.4f, 0.009f, 0.1f);

	glColor3f(0.0f, 1.0f, 0.0f);
	drawRectangle(0.0f, -0.6f, 0.1f, 0.1f);

	glPopMatrix();

	glutSwapBuffers();
}

// Función que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{
	fAnguloInt += add;
	// Incrementamos el �ngulo
	// Si es mayor que dos pi la decrementamos
	if (fAnguloInt > 90 && dir) {
		add = -constAdd;
		dir = false;
	}
	else if (fAnguloInt < -90 && !dir) {
		add = constAdd;
		dir = true;
	}
	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
}

//Reshaping image
void changeSize(int w, int h) {
	//TODO
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// Función principal
int main(int argc, char **argv)
{
	dir = true;
	add = 0.3f;
	// Inicializamos la librería GLUT
	glutInit(&argc, argv);

	// Indicamos como ha de ser la nueva ventana
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	// Creamos la nueva ventana
	glutCreateWindow("Péndulo");

	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);

	// El color de fondo será el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-1.0, 1.0f, -1.0, 1.0f, 0.01f, 1.0f);

	// Reshape image
	glutReshapeFunc(changeSize);

	// Comienza la ejecuciÓn del core de GLUT
	glutMainLoop();
	return 0;
}