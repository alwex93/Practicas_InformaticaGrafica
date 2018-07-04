#include <iostream>
#include "stdafx.h"
using namespace std;

class Tablero {
	enum Estado { vacio, bola, comida };
	static const int d = 12;
	Estado tablero[d][d]; //Tablero del juego
	bool hayComida;
public:
	Tablero() {
		for (int fila = 0; fila < d; fila++) {
			for (int columna = 0; columna < d; columna++) {
				tablero[fila][columna] = vacio;
			}
		}
		hayComida = false;
	}

	int getLength() {
		return d;
	}

	void vaciarCelda(int fila, int columna) {
		if (tablero[fila][columna] == comida) {
			hayComida = false;
		}
		tablero[fila][columna] = vacio;
	}

	bool estaVacio(int fila, int columna) {
		return tablero[fila][columna] == vacio;
	}

	void colocarBola(int fila, int columna) {
		tablero[fila][columna] = bola;
	}

	bool hayBola(int fila, int columna) {
		return tablero[fila][columna] == bola;
	}

	bool hayComidaEnPos(int fila, int columna) {
		return tablero[fila][columna] == comida;
	}

	bool contieneComida() {
		return hayComida;
	}

	void colocarComida(int fila, int columna) {
		tablero[fila][columna] = comida;
		hayComida = true;
	}

	bool colision(int fila, int columna) {
		return fila < 0 || fila > d - 1 || columna < 0 || columna > d - 1 || hayBola(fila, columna);
	}
};