#include <stdlib.h>

struct Nodo {
	float x, y; //x, y actuales
	bool derecha;
	Nodo* next;
};

bool operator==(const Nodo& lhs, const Nodo& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}