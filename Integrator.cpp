

#include "Integrator.h"
#include <iostream>

// Constructors
Integrator::Integrator() {}

// Destructurs
Integrator::~Integrator() {}

// Public Methods
void Integrator::registercallback(void(*holder)(void(*primeFunction)(double*, double*, double*), int, double*, double*, double, double*)){//, void(*primeFunction)(double*, double*, double*)) {
	int_method = holder;
	//der_method = primeFunction;
}

void Integrator::integrate(void(*primeFunction)(double*, double*, double*), int amt, double* tSpan, double* args, double tol, double* parameters) {
	(*int_method)(primeFunction, amt, tSpan, args, tol, parameters);
}

/*
void Integrator::derivative(double* time, double* y, double* parameters) {
	(*der_method)(time, y, parameters);
}
*/