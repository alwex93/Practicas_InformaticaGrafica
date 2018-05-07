// Etapa2.cpp
// Fichero principal 
////////////////////////////////////////////////////
#include "stdafx.h"
#include "glut.h"
#include <GL/gl.h>
#include <GL/glu.h>
const int W_WIDTH = 500; // Tamaño incial de la ventana
const int W_HEIGHT = 500;
GLfloat fAngulo; // Variable que indica el ángulo de rotación de los ejes.
GLfloat fAnguloInt;
bool right = true;
bool rightInt = true;
GLfloat p_inf = 2.5f;

// Función que visualiza la escena OpenGL
void Display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	//Pendulo exterior
	glPushMatrix();
	glTranslatef(0.0f, 2.5f, 0.0f);
	glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.5f, 0.1f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glEnd();
	
	glBegin(GL_LINES);
	glLineWidth(2.5);
	glColor3f(0.2f, 0.5f, 0.1f);
	glVertex3f(0.0f, 0.0, 0.0f);
	glVertex3f(0.0f, -3.0f, 0.0f);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.5f, 0.1f);
	glVertex3f(-0.5f, -2.5f, 0.0f);
	glVertex3f(0.5f, -2.5f, 0.0f);
	glVertex3f(0.5f, -3.5f, 0.0f);
	glVertex3f(-0.5f, -3.5f, 0.0f);
	glEnd();

	//Pendulo interior
	glTranslatef(0.0f, -3.0f, 0.0f);
	glRotatef(fAnguloInt, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 3.0f, 0.0f);
	glBegin(GL_LINES);
	glLineWidth(2.5);
	glColor3f(0.2f, 0.5f, 0.1f);
	glVertex3f(0.0f, -3.0f, 0.0f);
	glVertex3f(0.0f, -5.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.5f, 0.1f);
	glVertex3f(-0.5f, -4.5f, 0.0f);
	glVertex3f(0.5f, -4.5f, 0.0f);
	glVertex3f(0.5f, -5.5f, 0.0f);
	glVertex3f(-0.5f, -5.5f, 0.0f);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}

// Función que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{

	// Rotacion pendulo exterior
	if (right) {
		// Incrementamos el ángulo
		fAngulo += 0.03f;
		if (fAngulo > 90) {
			right = false;
		    fAngulo = 90;
		}
	} else {
		fAngulo -= 0.03f;
		if (fAngulo < -90) {
			right = true;
			fAngulo = -90;
		}
	}

	//Rotacion pendulo interior
	if (rightInt) {
		// Incrementamos el ángulo
		fAnguloInt += 0.03f;
		if (fAnguloInt > 90) {
			rightInt = false;
			fAnguloInt = 90;
		}
	}
	else {
		fAnguloInt -= 0.03f;
		if (fAnguloInt < -90) {
			rightInt = true;
			fAnguloInt = -90;
		}
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
	glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);

	// Reshape image
	glutReshapeFunc(changeSize);

	// Comienza la ejecuciÓn del core de GLUT
	glutMainLoop();
	return 0;
}