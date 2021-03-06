// Fichero principal 
////////////////////////////////////////////////////
#include "stdafx.h"
#include "glut.h"
#include "Serpiente.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <tuple>
#include <fstream>
#include "BmpLoader.h"
#include "Tablero.h"
using namespace std;
// Tamaño inicial de la ventana
const int W_WIDTH = 800; 
const int W_HEIGHT = 610;
//velocidad de movimiento y estado
int iter = 0;
int velocidad = 20;
bool decrease = false;
// Objetos del Juego
GLfloat initPos;
Tablero tablero;
Serpiente serpiente;
// Posicionamiento de la camara y sus estados
enum Camera { cen, first, picado };
Camera cam;
double eyeX = 0.0, eyeY = 0.0, eyeZ = 10.0;
double centerX = 0.0, centerY = 0.0, centerZ = 0.0;
double upX = 0.0, upY = 1.0, upZ = 0.0;
Direction dir;
//Puntuacion
int puntuacion;

// Posicion de la luz
GLfloat lp[] = { 0.0, 10.0, 10.0, 1.0 }; //light position
// Materiales
GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_emission[] = { 0.3f, 0.2f, 0.2f, 0.0f };
GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };


void esferaPequeña(int x, int y, int z) {
	glPushMatrix();
	//glMaterialfv(GL_FRONT, GL_EMISSION, mat_specular);
	glTranslatef(x, y+0.5, z);
	glutSolidSphere(0.5, 10, 10);
	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireSphere(0.5, 10, 10);
	glPopMatrix();
}

void escenario(GLfloat x, GLfloat z) {
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
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

	glColor3f(0.2f, 1.0f, 0.3f);

	int y = -tablero.getLength();
	for (int i = 0; i < n; i++, y += 0.01) {
		int x = -tablero.getLength();
		for (int j = 0; j < n; j++, x += 0.01) {
			glColor3f(1.0f, 0.0f, 0.0f);
			escenario(x - 0.5, y - 0.5);
			if (tablero.hayBola(i, j)) {
				glColor3f(0.0f, 0.0f, 1.0f);
				esferaPequeña(x - 1 + 0.25, 0.0f, y - 1 + 0.25);
			}
			else if (tablero.hayComidaEnPos(i, j)) {
				glColor3f(0.0f, 1.0f, 0.0f);
				esferaPequeña(x - 1 + 0.25, 0.0f, y - 1 + 0.25);
			}
		}
	}
	if (iter == 0) iter = 1;
	glPopMatrix();
}

void LoadTexture(const char* filename) {
	
	BmpLoader bl(filename);
	GLuint ID;
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData);

}

void paredes() {
	int length = tablero.getLength();
	glPushMatrix();

	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	//Pared inferior
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-length - 0.5, 1.0f, -0.5f);
	glTexCoord2f(0, 1);
	glVertex3f(-length - 0.5, 0.0f, -0.5f);
	glTexCoord2f(1, 1);
	glVertex3f((length / 2) - 6.5, 0.0f, -0.5f);
	glTexCoord2f(1, 0);
	glVertex3f((length / 2) - 6.5, 1.0f, -0.5f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//Pared left
	glEnable(GL_TEXTURE_2D);
	//glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(-length - 0.5, 1.0f, -0.5f);
	glTexCoord2f(1, 0);
	glVertex3f(-length - 0.5, 0.0f, -0.5f);
	glTexCoord2f(0, 0);
	glVertex3f(-length - 0.5, 0.0f, -(length / 2) - 6.5);
	glTexCoord2f(0, 1);
	glVertex3f(-length - 0.5, 1.0f, -(length / 2) - 6.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//Pared superior
	glEnable(GL_TEXTURE_2D);
	//glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(-length - 0.5, 1.0f, -(length / 2) - 6.5);
	glTexCoord2f(1, 0);
	glVertex3f(-length - 0.5, 0.0f, -(length / 2) - 6.5);
	glTexCoord2f(0, 0);
	glVertex3f(length / 2 - 6.5, 0.0f, -length - 0.5);
	glTexCoord2f(0, 1);
	glVertex3f(length / 2 - 6.5, 1.0f, -length - 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//Pared right
	glEnable(GL_TEXTURE_2D);
	//glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(length / 2 - 6.5, 1.0f, -length - 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(length / 2 - 6.5, 0.0f, -length - 0.5);
	glTexCoord2f(0, 0);
	glVertex3f((length / 2) - 6.5, 0.0f, -0.5f);
	glTexCoord2f(0, 1);
	glVertex3f((length / 2) - 6.5, 1.0f, -0.5f);
	glDisable(GL_TEXTURE_2D);

	glEnd();

	glPopMatrix();
}


void setEye(double x, double y, double z) {
	eyeX = x;
	eyeY = y;
	eyeZ = z;
}

void setCenter(double x, double y, double z) {
	centerX = x;
	centerY = y;
	centerZ = z;
}

void setUp(double x, double y, double z) {
	upX = x;
	upY = y;
	upZ = z;
}


// Función que visualiza la escena OpenGL
void Display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	// Set camara
	switch (cam) {
	case first:
		setEye(0.0, 0.0, 0.5);
		setCenter(100, 0.0, 0.0);
		setUp(0.0, 1.0, 0.0);
		glRotatef(90, 0.0, 0.0, 1.0);
		switch (dir) {
		case up:
			glRotatef(-90, 1.0, 0.0, 0.0);
			glTranslated(0, -initPos, -initPos);
			glTranslated(0, serpiente.getCabezaFila() + 0.54, serpiente.getCabezaColumna() - 1);
			break;
		case down:
			glRotatef(90, 1.0, 0.0, 0.0);
			glTranslated(0, -initPos, -initPos);
			glTranslated(0, serpiente.getCabezaFila() - 0.54, serpiente.getCabezaColumna() - 1);
			break;
		case lft:
			glRotatef(180, 1.0, 0.0, 0.0);
			glTranslated(0, initPos, -initPos);
			glTranslated(0, serpiente.getCabezaFila() + 1 - tablero.getLength(), 
				serpiente.getCabezaColumna() - 0.46);
			break;
		case rght:
			glTranslated(0, initPos, -initPos);
			glTranslated(0, serpiente.getCabezaFila() + 1 - tablero.getLength(), 
				serpiente.getCabezaColumna() - 1.54);
		}
		break;
	case picado:
		glTranslatef(1.0, 4.0, -5.0);
		glRotatef(-45, 1.0, 0.0, 0.0);
	case cen:
		setEye(0.0, 0.0, 10.0);
		setCenter(0.0, 0.0, 0.0);
		setUp(0.0, 1.0, 0.0);
		break;
	}
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

	glPushMatrix();

	glLightfv(GL_LIGHT0, GL_POSITION, lp);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

	glTranslatef(initPos, initPos - tablero.getLength(), 0.0f);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	matrix(tablero.getLength());
	paredes();

	glPopMatrix();
	glutSwapBuffers();
}

void actMatrix() {
	Nodo* cola = serpiente.get_last();
	tablero.vaciarCelda(cola->x, cola->y);
	serpiente.moverCola();

	Nodo* cabeza = serpiente.get_first();
	while (cabeza != NULL) {
		tablero.colocarBola(cabeza->x, cabeza->y);
		cabeza = cabeza->next;
	}
}

void generarObjetivo() {
	int x_obj, y_obj;
	do {
		x_obj = rand() % 12;
		y_obj = rand() % 12;
	} while (tablero.hayBola(x_obj, y_obj));
	tablero.colocarComida(x_obj, y_obj);
}

void controlObjetivo() {
	if (tablero.hayComidaEnPos(serpiente.getCabezaFila(), serpiente.getCabezaColumna())) {
		//Actualizamos puntuacion
		puntuacion++;
		//Cada 5 puntos, sube la velocidad
		if (puntuacion % 5 == 0) {
			decrease = true;
		}
		//Incrementamos de tamaño la serpiente
		serpiente.addBola();
		tablero.vaciarCelda(serpiente.getCabezaFila(), serpiente.getCabezaColumna());
	}
	if (!tablero.contieneComida()) {
		generarObjetivo();
	}
}
// Función que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{
	if (iter != 0) {
		iter++;
		if (iter == velocidad + 1) {
			iter = 0;
			if (decrease) velocidad /= 2; decrease = false;
		}
	}
	 if (iter == velocidad) {
		 serpiente.moverCabeza(dir);
		//Detección de colisión: Game Over
		if (tablero.colision(serpiente.getCabezaFila(), serpiente.getCabezaColumna())) {
			cout << "GAME OVER\n";
			cout << "Puntuacion: ";
			cout << puntuacion;
			cout << "\n";
			exit(0);
		}
		//Detección de colisión: Objeto
		controlObjetivo();

		actMatrix();
	 }
	 // Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
}

//Reshaping image
void changeSize(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// si h>w tenemos que redimensionar coordenadas -y/y, usando el ratio h/w,
	//en caso contrario las coordenadas -x/x con el ratio w/h.
	if (h > w) {
		glFrustum(-1.0, 1.0, -h / (float)w, h / (float)w, 1.0, 30.0);
	}
	else {
		glFrustum(-w / (float)h, w / (float)h, -1.0, 1.0, 1.0, 30.0);
	}
	glMatrixMode(GL_MODELVIEW);

}

Direction cambio(bool c) {
	int newDir = c ? dir + 1 : dir - 1;
	if (newDir > lft) {
		return up;
	}
	else if (newDir < up) {
		return lft;
	}
	else {
		return static_cast<Direction>((newDir));
	}
}

void SpecialKeyboard(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_LEFT:
		dir = cambio(false);
		break;
	case GLUT_KEY_RIGHT:
		dir = cambio(true);
		break;
	case GLUT_KEY_F1:
		cam = first;
		break;
	case GLUT_KEY_F2:
		cam = picado;
		break;
	case GLUT_KEY_F3:
		cam = cen;
		break;
	}
}

void init() {
	srand(1993);
	tablero = Tablero();
	initPos = tablero.getLength() / 2 - 0.5;
	//x e y estan invertidos, ojo
	serpiente = Serpiente(5, 5);
	serpiente.addBola();

	actMatrix();

	//Movimiento inicial de la serpiente
	dir = rght;
	//Camara incial
	cam = cen;
	//Puntuación
	puntuacion = 0;

	//Cargar textura
	LoadTexture("./arrow.bmp");

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
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
	glClearColor(0.31f, 0.31f, 0.31f, 1.0f);

	// Reshape image
	glutReshapeFunc(changeSize);

	init(); //creamos el tablero, que es una matriz

	// Comienza la ejecuciÓn del core de GLUT
	glutMainLoop();
	return 0;
}