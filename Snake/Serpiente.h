#include "Nodo.h"
#include <iostream>
#include <cmath>
#include <tuple>
using namespace std;

class serpiente
{
	int bolas;
	Nodo* cabeza;
	Nodo* cola;
public:
	serpiente() {
		bolas = 0;
		cabeza = NULL;
		cola = cabeza;
	}
	serpiente(int i, int j)
	{
		bolas = 1;
		cabeza = new Nodo{ i, j };
		cola = cabeza;
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

	tuple<int,int> move(int x, int y) {
		if (abs(x - cabeza->x) + abs(y - cabeza->y) != 1) {
			return make_tuple(0,0);
		}
		int xaux = x;
		int yaux = y;
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
		return make_tuple(xnext, ynext);
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