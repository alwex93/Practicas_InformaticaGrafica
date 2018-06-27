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
#include <fstream>
#include "BmpLoader.h"
using namespace std;

const int W_WIDTH = 800; // Tamaño incial de la ventana
const int W_HEIGHT = 610;
GLfloat move_x;
GLfloat move_y;
Direction dir;
const int s = 12;
Estado m[s][s]; //Tablero del juego
int headX, headY;
int iter = 0;
int MAX_ITER = 500;
bool decrease = false;
bool fp = false;
serpiente nodelist;
tuple<int, int> a;
int x_obj, y_obj;
int puntuacion;
double eyeX = 0.0, eyeY = 0.0, eyeZ = 10.0;
double centerX = 0.0, centerY = 0.0, centerZ = 0.0;
double upX = 0.0, upY = 1.0, upZ = 0.0;
GLfloat initPos = s / 2 - 0.5;

char* readFileBytes(const char *name)
{
	ifstream fl(name);
	fl.seekg(0, ios::end);
	size_t len = fl.tellg();
	char *ret = new char[len];
	fl.seekg(0, ios::beg);
	fl.read(ret, len);
	fl.close();
	return ret;
}

void esferaPequeña(int x, int y, int z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glutSolidSphere(0.5, 10, 10);
	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireSphere(0.5, 10, 10);
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
	glColor3f(0.2f, 1.0f, 0.3f);

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
				esferaPequeña(x - 1 + 0.25, 0.0f, y - 1 + 0.25);
				glColor3f(0.0f, 0.0f, 0.0f);
				escenario(x - 0.5, y - 0.5);
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

	//LoadTexture("texturaPared.bmp");
	//GlTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, readFileBytes("C:\\Users\\Usuario\\Desktop\\Uib\\2017-2018\\InformaticaGrafica\\PracticasIG\\leerfichero\\texturaPared.bmp"));

	glPushMatrix();
	
	glEnable(GL_TEXTURE_2D);
	//Pared inferior
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-s - 0.5, 1.0f, -0.5f);
	glTexCoord2f(0, 1);
	glVertex3f(-s - 0.5, 0.0f, -0.5f);
	glTexCoord2f(1, 1);
	glVertex3f((s / 2) - 6.5, 0.0f, -0.5f);
	glTexCoord2f(1, 0);
	glVertex3f((s / 2) - 6.5, 1.0f, -0.5f);
	glEnd();

	//Pared left
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(-s - 0.5, 1.0f, -0.5f);
	glTexCoord2f(1, 0);
	glVertex3f(-s - 0.5, 0.0f, -0.5f);
	glTexCoord2f(0, 0);
	glVertex3f(-s - 0.5, 0.0f, -(s / 2) - 6.5);
	glTexCoord2f(0, 1);
	glVertex3f(-s - 0.5, 1.0f, -(s / 2) - 6.5);
	glEnd();

	//Pared superior
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(-s - 0.5, 1.0f, -(s / 2) - 6.5);
	glTexCoord2f(1, 0);
	glVertex3f(-s - 0.5, 0.0f, -(s / 2) - 6.5);
	glTexCoord2f(0, 0);
	glVertex3f(s / 2 - 6.5, 0.0f, -s - 0.5);
	glTexCoord2f(0, 1);
	glVertex3f(s / 2 - 6.5, 1.0f, -s - 0.5);
	glEnd();

	//Pared right
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(s / 2 - 6.5, 1.0f, -s - 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(s / 2 - 6.5, 0.0f, -s - 0.5);
	glTexCoord2f(0, 0);
	glVertex3f((s / 2) - 6.5, 0.0f, -0.5f);
	glTexCoord2f(0, 1);
	glVertex3f((s / 2) - 6.5, 1.0f, -0.5f);

	glDisable(GL_TEXTURE_2D);

	glEnd();

	//glDisable(GL_TEXTURE_2D);
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
	
	if (fp) {
		switch (dir) {
		case up:
			setEye(0.0, 0, 0.5);
			setCenter(100, 0.0, 0.0);
			setUp(0.0, 1.0, 0.0);
			glRotatef(90, 0.0, 0.0, 1.0);
			glRotatef(-90, 1.0, 0.0, 0.0);
			glTranslated(0, -initPos, -initPos);
			glTranslated(0, headX + 0.55, headY - 1);
			break;
		case down:
			setEye(0.0, 0, 0.5);
			setCenter(100, 0.0, 0.0);
			setUp(0.0, 1.0, 0.0);
			glRotatef(90, 0.0, 0.0, 1.0);
			glRotatef(90, 1.0, 0.0, 0.0);
			glTranslated(0, -initPos, -initPos);
			glTranslated(0, headX - 0.55, headY - 1);
			break;
		case lft:
			setEye(0.0, 0, 0.5);
			setCenter(100, 0.0, 0.0);
			setUp(0.0, 1.0, 0.0);
			glRotatef(90, 0.0, 0.0, 1.0);
			glRotatef(180, 1.0, 0.0, 0.0);
			glTranslated(0, initPos, -initPos);
			glTranslated(0, headX + 1 - s, headY - 1 + 0.55);
			break;
		case rght:
			setEye(0.0, 0, 0.5);
			setCenter(100, 0.0, 0.0);
			setUp(0.0, 1.0, 0.0);
			glRotatef(90.0, 0.0, 0.0, 1.0);
			glTranslated(0, initPos, -initPos);
			glTranslated(0, headX + 1 - s,headY - 1 - 0.55);
		}

		//setEye(0, double(-initPos), 0.25);

	}
	else {
		setEye(0.0, 0.0, 10.0);
		setCenter(0.0, 0.0, 0.0);
		setUp(0.0, 1.0, 0.0);
	}
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

	glPushMatrix();

	glTranslatef(initPos, initPos - s, 0.0f);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	matrix(s);
	paredes();

	glPopMatrix();
	glutSwapBuffers();
}

void actMatrix() {
	Nodo* n = nodelist.get_first();
	while (n != NULL) {
		m[n->x][n->y] = bola;
		n = n->next;
	}
}

void generarObjetivo() {
	do {
		x_obj = rand() % 12;
		y_obj = rand() % 12;
	} while (m[x_obj][y_obj] == bola);
	m[x_obj][y_obj] = objeto;
}

void controlObjetivo(int &x_obj, int &y_obj) {
	if (headX == x_obj && headY == y_obj) {
		//Actualizamos puntuacion
		puntuacion++;
		//Cada 5 puntos, sube la velocidad
		if (puntuacion % 5 == 0) {
			decrease = true;
		}
		//Incrementamos de tamaño la serpiente
		nodelist.addBola();
		m[x_obj][y_obj] = vacio;
	}
	if (m[x_obj][y_obj] == vacio) {
		generarObjetivo();
	}
}

// Función que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{
	if (iter != 0) {
		iter++;
		if (iter == MAX_ITER + 1) {
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
			cout << "GAME OVER\n";
			cout << "Puntuacion: ";
			cout << puntuacion;
			cout << "\n";
			exit(0);
		}
		//Detección de colisión: Objeto
		controlObjetivo(x_obj, y_obj);

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
		//gluPerspective(120.0, (GLfloat)h / (GLfloat)w, 1.0, 100.0);
		glFrustum(-1.0, 1.0, -h / (float)w, h / (float)w, 1.0, 30.0);
		//glOrtho(-1.0, 1.0, -h / (float)w, h / (float)w, -20.0, 100.0);
	}
	else {
		//ratio = ((GLsizei)h / (GLsizei)w);
		//gluPerspective(120.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
		glFrustum(-w / (float)h, w / (float)h, -1.0, 1.0, 1.0, 30.0);
		//glOrtho(-w / (float)h, w / (float)h, -1.0, 1.0, -20.0, 100.0);
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
	case GLUT_KEY_F2:
		if (fp) {
			fp = false;
		} else {
			fp = true;
		}
		break;
	}
	glutIdleFunc(Idle);
}

void Keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case '+': //Zoom in
		eyeZ -= 0.1;
		break;
	case '-': //Zoom out
		eyeZ += 0.1;
		break;
	case 'a':
		eyeX -= 0.1;
		break;
	case 'z':
		eyeX += 0.1;
		break;
	case 's':
		eyeY -= 0.1;
		break;
	case 'x':
		eyeY += 0.1;
		break;
	}
}

void init() {
	x_obj = 0;
	y_obj = 0;
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

	//generarObjetivo();

	actMatrix();

	//Movimiento inicial de la serpiente
	dir = rght;

	//Puntuación
	puntuacion = 0;

	//Cargar textura
	//LoadTexture("brick.bmp");
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
	glutKeyboardFunc(Keyboard);
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