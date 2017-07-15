#pragma once
// How to use it:
// classname.registercallback(Numerical_Integrator);
// classname.integrate(primeFunction, amt, t, arg, tol, parameters)

#ifndef INTEGRATOR_H

#define INTEGRATOR_H

#include "Numerical_Integrator.h"




class Integrator {
public:
	// Constructors

	// Base Constructor

	Integrator();

	// Destructors

	~Integrator();

	void registercallback(void(*holder)(void (*primeFunction)(double*, double*, double*),int, double*, double*, double, double*));
	void integrate(void(*primeFunction)(double*, double*, double*),int amt, double* t, double* args, double tol, double* parameters);

	//void derivative(double* time, double* y, double* parameters);

	//void (*int_method)(int amt, double* init_Conditions);
private:
	// amt: amount of initial conditions
	// time: is a pointer that holds two variables t0 and tend. In order to have a boundary conditions for time
	// init_Condition: it holds the initial conditions in a pointer
	void(*int_method)(void (*primeFunction)(double*, double*, double*),int amt, double* time, double* init_Conditions, double tol, double* parameters);
	//void(*der_method)(double* time, double* y, double* parameters);

};
#endif