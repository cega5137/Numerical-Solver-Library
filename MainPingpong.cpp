// Test Main Seth / Cesar

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Integrator.h"


// Function declaration
double CdAproximation(double v, double nu, double d);
void SphericFreeFall(double* t, double* y, double* C);


int main() {
	std::cout << "Application Starting" << std::endl;

	// Create Integrator Instance
	Integrator ball;

	// Set Integration Methods
	double	z0 = 0;
	double	v0 = 0;
	double	tend = 10;
	int		args = 2;
	double	y[2];
	double	d = 0.036; //[m]
	double	rhoFluid = 1.22;  //[kg / m ^ 3]
	double	nu = 1e-6;  //[m ^ 2 / s]
	double	rhoBall = 1000;  //[kg / m ^ 3]
	double  g = 9.80665;
	double	rhoBar;
	double tspan[2];
	double Const[4];
	
						/* Constants */
	rhoBar = rhoFluid / rhoBall;
	
						/* Initial conditions */
	y[0] = z0;
	y[1] = v0;
	tspan[0] = 0;
	tspan[1] = tend;
	Const[0] = rhoBar;
	Const[1] = nu;
	Const[2] = d;
	Const[3] = g;


	std::cout << "t0 = " << tspan[0] << std::endl;
	std::cout << "tend = " << tspan[1] << std::endl;


						 /* Choose integrator */
	ball.registercallback(Euler);
	
						/* Pass variables to integrator */
	ball.integrate(SphericFreeFall, args, tspan, y, 0.01, Const);

	// End
	std::cout << "Application Terminating" << std::endl;

	std::getchar();
}

// Function
void SphericFreeFall(double* t, double* y, double* C ) {

	// Memory allocation
	double z, v;
	double rhoBar, nu, d, g, cd;
	double a, b, c;
	double dzdt, dvdt;

	// save variables into allocation
	z = y[0];
	v = y[1];

	// Save constants	
	rhoBar = 0.00122;//C[0];
	nu = 1e-6;//C[1];
	d = 0.036;//C[2];
	g = 9.80665;//C[3];
	
	// calculate cd
	cd = CdAproximation(v, nu, d);

	// Calculate coefficients
	a = 1 + 0.5 * rhoBar;
	b = (1 - rhoBar)*g;
	c = 3 * rhoBar / (4 * d);

	// Compute derivatives
	dzdt = v;
	dvdt = (1 / a)*(b - c*abs(v)*v*cd);


	// return
	y[0] = dzdt;
	y[1] = dvdt;
}

// Cd estimation;
double CdAproximation(double v,double nu, double d) {

	// Memory allocation
	double cd;
	double Re;
	
	// Calculate Re number
	Re = v*d / nu;

	// Find Cd
	if (Re == 0)
		cd = 0;
	else if (Re <= 1)
		cd = 24 / Re;
	
	else if (Re > 1 && Re <= 400)
		cd = 24 / pow(Re, 0.646);

	else if (Re > 400 && Re <= 3*pow(10, 5))
		cd = .5;
	
	else if (Re > 3*pow(10, 5) && Re <= 2*pow(10, 6))
		
		cd = .000366*pow(Re, 0.4275);

	else if (Re > 2*pow(10, 6))
		cd = .18;

	return cd;
}
