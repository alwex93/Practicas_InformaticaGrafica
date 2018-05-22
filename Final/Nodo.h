#include <stdlib.h>

class Nodo {
	float x, y;
	Nodo* next;
public:
	void set_values(float, float);
	void set_next(Nodo*);
	float* get_values();
	Nodo* get_next();
};

void Nodo::set_values(float i, float j) {
	x = i;
	y = j;
}

void Nodo::set_next(Nodo* n) {
	next = n;
}

Nodo* Nodo::get_next() {
	return next;
}

float* Nodo::get_values() {
	float* r = (float*)malloc(sizeof(float) * 2);
	r[0] = x;
	r[1] = y;
	return r;
}