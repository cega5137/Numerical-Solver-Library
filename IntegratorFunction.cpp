

#include "integratorFunction.h"
#include <iostream>

// Constructors
IntegratorFunction::IntegratorFunction() {}

// Destructurs
IntegratorFunction::~IntegratorFunction() {}

// Public Methods
void IntegratorFunction::registercallback(void(*holder)(double*, double*, double*)) {
	int_method = holder;
}

void IntegratorFunction::primeFunction(double* time, double* y, double* parameters) {
	(*int_method)(time, y, parameters);
}