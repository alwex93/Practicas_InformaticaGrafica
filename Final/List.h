#include "Nodo2.h"
#include <stdlib.h>

class list
{
	Nodo2* head;
	Nodo2* tail;
public:
	list()
	{
		head = NULL;
		tail = NULL;
	}

	void createnode(float i, float j)
	{
		Nodo2* temp = new Nodo2;
		temp->x = i;
		temp->y = j;
		if (head == NULL)
		{
			head = temp;
			tail = temp;
			tail->next = NULL;
			temp = NULL;
		}
		else
		{
			tail->next = temp;
			tail = temp;
			tail->next = NULL;
		}
	}

	Nodo2* get_first()
	{
		Nodo2 *temp = new Nodo2;
		temp = head;
		return temp;
	}

	Nodo2* get_last()
	{
		Nodo2 *temp = new Nodo2;
		temp = tail;
		return temp;
	}

	void insert_end(float i, float j)
	{
		Nodo2 *temp = new Nodo2;
		temp->x = i;
		temp->y = j;
		tail->next = temp;
		tail = temp;
		tail->next = NULL;
	}
};

