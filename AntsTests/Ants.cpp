#include <cmath>
#include <iostream>

#include "Ants.h"

#define M_PI 3.14


void Ants::runSimulation()
{
	// ants walk on a table
	double number_of_ants[ARR_MAX][ARR_MAX];
	double new_number_of_ants[ARR_MAX][ARR_MAX];
	double velocity_of_ants[ARR_MAX][ARR_MAX];
	const int total_ants = 100; // initial number of ants
								 // initialize
	for (int i = 0; i<ARR_MAX; i++) {
		for (int j = 0; j<ARR_MAX; j++) {
			velocity_of_ants[i][j] = M_PI*(sin((2 * M_PI*(i + j)) / 350) + 1);
			//std::cout << "vel" << i << "," << j << " " << velocity_of_ants[i][j] << " ";
		}
	}
	int n = 0;
	double z = 0;
	for (int i = 0; i<ARR_MAX; i++) {
		for (int j = 0; j<ARR_MAX; j++) {
			number_of_ants[i][j] = 0.0;
		}
	}
	while (n < total_ants) {
		for (int i = 0; i<ARR_MAX; i++) {
			for (int j = 0; j<ARR_MAX; j++) {
				z += sin(0.3*(i + j));
				if (z>1 && n != total_ants) {
					number_of_ants[i][j] += 1;
					n += 1;
				}
			}
		}
	}

	// run simulation
	double totants;
	for (int t = 0; t < 10; t++) {
		
		totants = 0.0;
		for (int i = 0; i<ARR_MAX; i++) {
			for (int j = 0; j<ARR_MAX; j++) {
				totants += number_of_ants[i][j];
			}
		}
		std::cout << "Iteration " << t << ", num of ants = " << totants << std::endl;
		for (int i = 0; i<ARR_MAX; i++) {
			for (int j = 0; j<ARR_MAX; j++) {
				new_number_of_ants[i][j] = 0.0;
			}
		}
		for (int i = 0; i<ARR_MAX; i++) {
			for (int j = 0; j<ARR_MAX; j++) {
				int di = (int)(1.9*sin(velocity_of_ants[i][j]));
				int dj = (int)(1.9*cos(velocity_of_ants[i][j]));
				int i2 = i + di;
				int j2 = j + dj;
				// some ants do not walk
				new_number_of_ants[i][j] += 0.8*number_of_ants[i][j];
				// the rest of the ants walk, but some fall of the table
				if (i2>=0 && i2 < ARR_MAX && j2>=0 && j2 < ARR_MAX) {
					new_number_of_ants[i2][j2] += 0.2*number_of_ants[i][j];
				}
			}
		}

		totants = 0.0;
		for (int i = 0; i<ARR_MAX; i++) {
			for (int j = 0; j<ARR_MAX; j++) {
				number_of_ants[i][j] = new_number_of_ants[i][j];
				totants += number_of_ants[i][j];
			}
		}
	}

	std::cout << "The end, num of ants = " << totants << std::endl;
}