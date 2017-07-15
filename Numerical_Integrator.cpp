#include "Numerical_Integrator.h"
#include<iostream>
#include<cmath>
#include<cstdlib>
#include <fstream>'

// Imaginary Integration Library/ doesn't have to be in main or in the integrator class


void Euler(void(*primeFunction)(double*, double*, double*), int amt, double* tSpan, double* init, double h, double* parameters) {


	// Memory allocation
	int i;
	double t;
	double* primes = (double*)std::malloc(amt*sizeof(double)); // Make a class out of primes, so people cannot access more than they need to 
//	char fileout[] = "";//"Euler.dat";

	// Start at initial time
	t = tSpan[0];

/*	if (fileout != "") {
		// Open File
		using namespace std;
		ofstream outf(fileout);


		if (!outf)
		{
			// Print an error and exit
			cerr << "Uh oh, Sample.dat could not be opened for writing!" << endl;
			exit(1);
		}
		outf << "t \t x \t v" << endl;
	};*/

	// Iterate
	while (t < tSpan[1])
	{
		// set primes conditions as its primes
		for (i = 0; i < amt ; i++) {
			primes[i] = init[i];
		}

		// Function to get the primes
		(*primeFunction)(&t, primes, parameters);
		/*std::cout << " \nAfter function" << std::endl;
		std::cout << "t = " << t << std::endl;
		std::cout << "z = " << init[0] << std::endl;
		std::cout << "v = " << init[1] << std::endl;
		std::cout << "z' = " << primes[0] << std::endl;
		std::cout << "v' = " << primes[1] << std::endl;*/

		// Update state
		t = t + h;

//		if (fileout == "") {
			std::cout << t << "  ";
			for (i = 0; i < amt; i++) {
				init[i] = init[i] + h*primes[i];
				std::cout << init[i] << "  ";
			}
			std::cout << std::endl;
//		}
/*		else {
			// Write output file
			outf << t << "  ";
			for (i = 0; i < amt; i++) {
				init[i] = init[i] + h*primes[i];
				outf << init[i] << "  ";
			}
			outf << endl;
		}*/
	};
}

void RK4(void(*primeFunction)(double*, double*, double*), int amt, double* tSpan, double* init, double h, double* parameters) {

	// Memory allocation
	int i;
	double t,tTemp;
	double* k1 = (double*)std::malloc(amt*sizeof(double));
	double* k2 = (double*)std::malloc(amt*sizeof(double));
	double* k3 = (double*)std::malloc(amt*sizeof(double));
	double* k4 = (double*)std::malloc(amt*sizeof(double));
	double* primes = (double*)std::malloc(amt*sizeof(double)); // Make a class out of primes, so people cannot access more than they need to 

	// Set starting time
	t = tSpan[0];

	//Iterate
	while (t < tSpan[1]) {

					/* First constant */
		// set primes conditions as its primes
		for (i = 0; i < amt; i++) {
			primes[i] = init[i];
		}
		
		(*primeFunction)(&t, primes, parameters);
		
		for (i = 0; i < amt; i++) {
			k1[i] = h*primes[i];
			tTemp = t + 0.5*h;
		}

				
					/* Second Constant */
		for (i = 0; i < amt; i++) {
			primes[i] = init[i] + 0.5*k1[1];
		}

		(*primeFunction)(&tTemp, primes, parameters);

		for (i = 0; i < amt; i++) {
			k2[i] = h*primes[i];
		}

					/* Third Constant */
		for (i = 0; i < amt; i++) {
			primes[i] = init[i] + 0.5*k2[i];
		}

		(*primeFunction)(&tTemp, primes, parameters);
		
		for (i = 0; i < amt; i++) {
			k3[i] = h*primes[i];
			tTemp = t + h;
		}
	
					/* Forths Constant */
		for (i = 0; i < amt; i++) {
			primes[i] = init[i] + k3[i];

		}

		(*primeFunction)(&tTemp, primes, parameters);
	
		for (i = 0; i < amt ; i++) {
			k4[i] = h*primes[i];
		}

					/* Update time step and state*/
		t = t + h;

		for (i = 0; i < amt; i++) {
			init[i] = init[i] + (1.0 / 6.0)*(k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]);

		}

					/* Output */
		std::cout << " \nAfter function" << std::endl;
		std::cout << "t = " << t << std::endl;
		std::cout << "z = " << init[0] << std::endl;
		std::cout << "v = " << init[1] << std::endl;
		
	}

}


void ode45(void(*primeFunction)(double*, double*, double*), int amt, double* tSpan, double* init, double tol, double* parameters) {
	// Memory allocation
	int i;
	double t, tTemp;
	double* k1 = (double*)std::malloc(amt*sizeof(double));
	double* k2 = (double*)std::malloc(amt*sizeof(double));
	double* k3 = (double*)std::malloc(amt*sizeof(double));
	double* k4 = (double*)std::malloc(amt*sizeof(double));
	double* k5 = (double*)std::malloc(amt*sizeof(double));
	double* k6 = (double*)std::malloc(amt*sizeof(double));
	double* Y4 = (double*)std::malloc(amt*sizeof(double));
	double* Y5 = (double*)std::malloc(amt*sizeof(double));
	double* Er = (double*)std::malloc(amt*sizeof(double));
	double* primes = (double*)std::malloc(amt*sizeof(double)); // Make a class out of primes, so people cannot access more than they need to 
	double h, Emax;
												   // Set starting time
	t = tSpan[0];
	h = .1;
	
						// Start iteration
	while (t < tSpan[1]) {

		Emax = 1000;
		while (Emax > tol) {
			Emax = 0;
						/* First constant */
			// set primes conditions as its primes
			for (i = 0; i < amt; i++) {
				primes[i] = init[i];
			}

			(*primeFunction)(&t, primes, parameters);

			for (i = 0; i < amt; i++) {
				k1[i] = h*primes[i];
				tTemp = t + 0.25*h;
			}

					/* Second constant */
			// set primes conditions as its primes
			for (i = 0; i < amt; i++) {
				primes[i] = init[i] + 0.25*k1[i];
			}

			(*primeFunction)(&t, primes, parameters);

			for (i = 0; i < amt; i++) {
				k2[i] = h*primes[i];
				tTemp = t + (3.0 / 8.0)*h;
			}

					/* Third constant */
			// set primes conditions as its primes
			for (i = 0; i < amt; i++) {
				primes[i] = init[i] + (3.0 / 32.0)*k1[i] + (9.0 / 32.0) *k2[i];
			}

			(*primeFunction)(&t, primes, parameters);

			for (i = 0; i < amt; i++) {
				k3[i] = h*primes[i];
				tTemp = t + (12.0 / 12.3)*h;
			}

					/* Fourth constant */
			// set primes conditions as its primes
			for (i = 0; i < amt; i++) {
				primes[i] = init[i] + (1932.0 / 2197.0)*k1[i] - (7200.0 / 2197.0) *k2[i] + (7296.0 / 2197.0)*k3[i];
			}

			(*primeFunction)(&t, primes, parameters);

			for (i = 0; i < amt; i++) {
				k4[i] = h*primes[i];
				tTemp = t + h;
			}

					/* Fifth constant */
			// set primes conditions as its primes
			for (i = 0; i < amt; i++) {
				primes[i] = init[i] + (439.0 / 216.0)*k1[i] - 8 * k2[i] + (3680.0 / 513.0) *k3[i] + (7296.0 / 2197.0)*k4[i];
			}

			(*primeFunction)(&t, primes, parameters);

			for (i = 0; i < amt; i++) {
				k5[i] = h*primes[i];
				tTemp = t + 0.5*h;
			}

					/* Sixth constant */
			// set primes conditions as its primes
			for (i = 0; i < amt; i++) {
				primes[i] = init[i] - (8.0 / 27.0)*k1[i] + 2 * k2[i] - (3544.0 / 2565.0)*k3[i] + (1859.0 / 4104.0)*k4[i] - (11.0 / 40.0)*k5[i];
			}

			(*primeFunction)(&t, primes, parameters);

			for (i = 0; i < amt; i++) {
				k6[i] = h*primes[i];
			}

			/* Calculate Fourth and Fifth Order */
			for (i = 0; i < amt; i++) {
				Y4[i] = init[i] + ((25.0 / 216.0)*k1[i] + (1408.0 / 2565.0)*k3[i] + (2197.0 / 4104.0)*k4[i] - (1.0 / 5.0)*k5[i]);
				Y5[i] = init[i] + ((16.0 / 135.0)*k1[i] + (6656.0 / 12825.0)*k3[i] + (28561.0 / 56430.0)*k4[i] - (9.0 / 50.0)*k5[i] + (2.0 / 55.0)*k6[i]);
				Er[i] = Y5[i] - Y4[i];
				if (Emax < abs(Er[i])) {
					Emax = abs(Er[i]);
				}
			}
			//std::cout << "Emax = " << Emax << std::endl;
			if (Emax > tol)
				h = h / 10;	
		}

		t = t + h;
		for (i = 0; i < amt; i++) {
			init[i] = Y5[i];
		}

		std::cout << " \nAfter function" << std::endl;
		std::cout << "h = " << h << std::endl;
		std::cout << "t = " << t << std::endl;
		std::cout << "z = " << init[0] << std::endl;
		std::cout << "v = " << init[1] << std::endl;
		
		h = .1;

	}
}


void ode56(void(*primeFunction)(double*, double*, double*), int amt, double* tSpan, double* init, double tol, double* parameters) {
	std::cout << "Calling ODE56 with amt = " << amt << std::endl;
}
