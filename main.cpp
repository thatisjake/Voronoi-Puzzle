#include <iostream>
#include <vector>
#include <math.h>
#include <windows.h>

using namespace std;

struct point {
	float x, y;
};



int main() {

	
	
	//How many squares should one edge inside the unit square be
	int resolution = 100;

	//How many points to have
	int n = 100;

	//Stores the points

	//Seeding the random values
	srand(time(0));

	//Keeps track of iterations
	int runTime = 1;
	double totalArea = 0;


	float expected = 0;
	for (int i = 1; i < n; i++) {
		expected += (float)1 / i;
	}
	cout << "Expected value: " << expected << endl;

	while (true) {
		
		vector<point> points;
		for (int i = 0; i < n; i++) {
			point p;

			p.x = (float) rand()/ (float)RAND_MAX;
			p.y = (float) rand()/ (float)RAND_MAX;
			points.push_back(p);
		}

		//Initialize vector
		vector<vector<int>>		values;
		vector<vector<float>>	distances;

		for (int i = 0; i < resolution; i++) {
			vector<int> tmp;
			vector<float> tmp2;

			for (int j = 0; j < resolution; j++) {
				tmp.push_back(0);
				tmp2.push_back(1000);
			}
			values.push_back(tmp);
			distances.push_back(tmp2);
		}
		


		//Calculate area
		int area = 0;

		//For every point
		for (int p = 0; p < n; p++) {
			//cout << "Calculating point #" << p << endl;

			int thisArea = 0;
			//And every "Row"
			for (int i = 0; i < resolution; i++) {

				//And every "Column"
				for (int j = 0; j < resolution; j++) {
					//Find distance
					float dist = sqrt(pow((points[p].x - ((float)j/ resolution)), 2) + pow((points[p].y - ((float)i/ resolution)), 2));

					if (distances[i][j] > dist) {
						values[i][j] = p;
						distances[i][j] = dist;
						thisArea++;
					}

				}
			}
			//cout << "Point Area = " << thisArea << endl;
			area += thisArea;
		}

		
		float realArea = (float)area / ((float)resolution * resolution);
		totalArea += realArea;
		float error = (((float)totalArea / runTime) - expected)/expected;

		cout << "Average Area: " << totalArea / runTime << " Iterations:" << runTime << " Error: " << abs(error * 100) << "%\n";
		
		runTime++;
	}

	return 0;
}