#include <iostream>
#include <cmath>
#include <tuple>
#include "Nodo.h"
using namespace std;

enum Direction { up, rght, down, lft };

class Serpiente
{
	int bolas;
	Nodo* cabeza;
	Nodo* cola;
	int filaCabeza, columnaCabeza;
public:
	Serpiente() {
		bolas = 0;
		cabeza = NULL;
		cola = cabeza;
		filaCabeza = 0;
		columnaCabeza = 0;
	}

	Serpiente(int initFila, int initColumna) {
		bolas = 0;
		cabeza = new Nodo{ initFila, initColumna };
		cola = cabeza;
		filaCabeza = initFila;
		columnaCabeza = initColumna;
	}

	int getCabezaFila() {
		return filaCabeza;
	}

	int getCabezaColumna() {
		return columnaCabeza;
	}

	void moverCabeza(Direction dir) {
		switch (dir) {
		case up:
			filaCabeza--;
			break;
		case rght:
			columnaCabeza++;
			break;
		case down:
			filaCabeza++;
			break;
		case lft:
			columnaCabeza--;
		}
	}

	void moverCola() {
		int xaux = filaCabeza;
		int yaux = columnaCabeza;
		int xnext;
		int ynext;
		Nodo *temp = cabeza;
		do {
			//Guardar valores para siguiente bola
			xnext = temp->x;
			ynext = temp->y;
			//Actualizamos bola actual
			temp->x = xaux;
			temp->y = yaux;
			//Valores que pasan para la siguiente bola
			xaux = xnext;
			yaux = ynext;
			temp = temp->next;
		} while (temp != NULL);
	}

	void addBola()
	{
		Nodo* temp = new Nodo{ cola->x, cola->y };
		bolas++;
		cola->next = temp;
		cola = temp;
	}


	int isHead(float i, float j) {
		//if (new Nodo{ i, j, NULL } == giros) {
		if (cabeza != NULL && i == cabeza->x && j == cabeza->y) {
			return 1;
		}
		return -1;
	}

	Nodo* get_first()
	{
		Nodo *temp = new Nodo;
		temp = cabeza;
		return temp;
	}

	Nodo* get_last() {
		Nodo *temp = new Nodo;
		temp = cola;
		return temp;
	}

	int get_bolas()
	{
		return bolas;
	}

	void printlist() {
		Nodo *temp = new Nodo;
		temp = cabeza;
		cout << "n bolas: " << bolas << "\n";
		while (temp != NULL) {
			cout << "x: " << temp->x << "\n";
			cout << "y: " << temp->y << "\n";
			temp = temp->next;
		}
	}
};