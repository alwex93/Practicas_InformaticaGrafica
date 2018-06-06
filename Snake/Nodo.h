#include <stdlib.h>

struct Nodo {
	int x, y; //x, y actuales
	Nodo* next;
};

bool operator==(const Nodo& lhs, const Nodo& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}