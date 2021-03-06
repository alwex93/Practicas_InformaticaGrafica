// Etapa2.cpp
// Fichero principal 
////////////////////////////////////////////////////
#include "stdafx.h"
#include "glut.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <math.h>
const int W_WIDTH = 500; // Tamaño incial de la ventana
const int W_HEIGHT = 500;
const double PI = 3.1415926535897932384626433832795;
const float radius = 0.5;
GLfloat fAngulo; // Variable que indica el ángulo de rotación de los ejes. 
GLfloat move_x, move_y;
GLfloat cood_x = 0.0f, cood_y = 0.0f;
enum Direction { up, down, left, right };
Direction dir;

void figura() {
	// Creamos a continuación dibujamos los poligonos
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-move_x - 1.0f, -move_y - 1.0f, 0.0f);
	glVertex3f(-move_x, -move_y, 0.0f);
	glVertex3f(-move_x - 1.0f, -move_y + 1.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-move_x + 1.0f, -move_y + 1.0f, 0.0f);
	glVertex3f(-move_x, -move_y, 0.0f);
	glVertex3f(-move_x + 1.0f, -move_y - 1.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-move_x - 1.0f, -move_y + 1.0f, 0.0f);
	glVertex3f(-move_x, -move_y, 0.0f);
	glVertex3f(-move_x + 1.0f, -move_y + 1.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-move_x - 1.0f, -move_y - 1.0f, 0.0f);
	glVertex3f(-move_x, -move_y, 0.0f);
	glVertex3f(-move_x + 1.0f, -move_y - 1.0f, 0.0f);
	glEnd();

	//Draw Circle
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	//Change the 6 to 12 to increase the steps (number of drawn points) for a smoother circle
	//Note that anything above 24 will have little affect on the circles appearance
	//Play with the numbers till you find the result you are looking for
	//Value 1.5 - Draws Triangle
	//Value 2 - Draws Square
	//Value 3 - Draws Hexagon
	//Value 4 - Draws Octagon
	//Value 5 - Draws Decagon
	//Notice the correlation between the value and the number of sides
	//The number of sides is always twice the value given this range
	for (double i = 0; i < 2 * PI; i += PI / 5) //<-- Change this Value
		glVertex3f(cos(i) * radius - move_x, sin(i) * radius - move_y, 0.0);
	glEnd();
}

// Función que visualiza la escena OpenGL
void Display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	figura();

	glPopMatrix();


	glutSwapBuffers();
}

//Mostramos la figura y la rotamos
void DisplayRotate(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	// Rotamos las proximas primitivas
	glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
	figura();
	glPopMatrix();


	glutSwapBuffers();
}

//Mostramos la figura y la trasladamos
void DisplayTranslate(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	// Trasladamos las proximas primitivas
	glTranslatef(move_x, move_y, 0.0f);

	GLfloat saveX = move_x, saveY = move_y;
	move_x = 0.0; move_y = 0.0;
	figura();
	move_x = saveX; move_y = saveY;

	switch (dir) {
	case right:
		move_x += 0.001f;
		if (move_x > 1.5f) dir = down;
		break;
	case down:
		move_y -= 0.001f;
		if (move_y < -1.5f) dir = left;
		break;
	case left:
		move_x -= 0.001f;
		if (move_x < -1.5f) dir = up;
		break;
	case up:
		move_y += 0.001f;
		if (move_y > 1.5f) dir = right;
		break;
	}
	glTranslatef(-move_x, -move_y, 0.0f);

	glPopMatrix();

	glutSwapBuffers();
}

//Mostramos la figura, la rotamos y la trasladamos
void DisplayRotateTranslate(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	// Trasladamos y rotamos las proximas primitivas
	//glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
	glTranslatef(-move_x, -move_y, 0.0f);
	glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
	glTranslatef(move_x, move_y, 0.0f);

	switch (dir) {
	case right:
		move_x += 0.001f;
		cood_x -= 0.001f;
		if (move_x > 1.5f) dir = down;
		break;
	case down:
		move_y -= 0.001f;
		cood_y += 0.001f;
		if (move_y < -1.5f) dir = left;
		break;
	case left:
		move_x -= 0.001f;
		cood_x += 0.001f;
		if (move_x < -1.5f) dir = up;
		break;
	case up:
		move_y += 0.001f;
		cood_y -= 0.001f;
		if (move_y > 1.5f) dir = right;
		break;
	}

	figura();
	glTranslatef(-move_x, -move_y, 0.0f);
	glPopMatrix();

	glutSwapBuffers();
}

// Función que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{
	// Incrementamos el ángulo
	fAngulo += 0.3f;
	// Si es mayor que dos pi la decrementamos
	if (fAngulo > 360)
		fAngulo -= 360;
	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
}

//Reshaping image
void changeSize(int w, int h) {
	//TODO
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void Keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'e':             // ESCAPE key
		exit(0);
		break;
	case 'n': //Normal
		glutDisplayFunc(Display);
		break;
	case 'r': //Rotate
		glutDisplayFunc(DisplayRotate);
		break;
	case 't': //Translate
		dir = left;
		glutDisplayFunc(DisplayTranslate);
		break;
	case 'b': //Rotate and Translate
		dir = left;
		glutDisplayFunc(DisplayRotateTranslate);
		break;
	}
	move_x = 0.0f;
	move_y = 0.0f;
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
	glutCreateWindow("Mi segunda Ventana con teclado");

	//Choose display type
	glutKeyboardFunc(Keyboard);
	//Idle
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