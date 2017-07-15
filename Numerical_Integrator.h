#pragma once

#ifndef NUMERICAL_INTEGRATOR_H

#define NUMERICAL_INTEGRATOR_H


void Euler(void(*primeFunction)(double*, double*, double*), int amt, double* tSpan, double* init, double h, double* parameters);
void RK4(void(*primeFunction)(double*, double*, double*), int amt, double* tSpan, double* init, double h, double* parameters);
void ode45(void(*primeFunction)(double*, double*, double*), int amt, double* tSpan, double* init, double tol, double* parameters);
void ode56(void(*primeFunction)(double*, double*, double*), int amt, double* tSpan, double* init, double tol, double* parameters);



#endif