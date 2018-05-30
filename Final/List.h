#include "Nodo.h"
#include <stdlib.h>

class list
{
	int bolas;
	Nodo* giros;
public:
	list()
	{
		bolas = 0;
		giros = NULL;
	}

	void createnode(float i, float j, bool dir)
	{
		Nodo* temp = new Nodo{i, j, dir};
		bolas++;
		if (giros == NULL)
		{
			giros = temp;
		}
		else { //poner al principio
			temp->next = giros;
			giros = temp;
		}
	}

	int isHead(float i, float j) {
		//if (new Nodo{ i, j, NULL } == giros) {
		if (i == giros->x && j == giros->y) {
			return giros->derecha;
		}
		return -1;
	}

	Nodo* get_first()
	{
		Nodo *temp = new Nodo;
		temp = giros;
		return temp;
	}

	int get_bolas()
	{
		return bolas;
	}

	bool get_dir(int n)
	{
		Nodo *temp = giros;
		for (int i = 0; i < n; i++) {
			temp = temp->next;
		}
	return temp->derecha;
	}
};