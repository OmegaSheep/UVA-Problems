/* UVa problem: <11152>
 *
 * Topic: (Geometry)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *   Find the three areas for each flower.
 *
 * Solution Summary:
 *
 *   For the first area, get the area using the radius from circRad. 
 *	 For the second area use Herons formula. Subtract the result from the first area.
 *	 Calculate the area of the third circle inside the triangle using its radius. 
 *	 Subtract the third area from the second area.
 *
 * Used Resources:
 *
 *   - Textbook (Specifically Heron's Formula)
 *	 - http://www.mathopenref.com/triangleincircle.html (Calculating Circle in Triangle)
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <cmath>
#define PI           3.14159265358979323846
using namespace std;

double herons(double a, double b, double c) {
	double s = (a+b+c)/2;
	return sqrt(s*(s-a)*(s-b)*(s-c));
}

double circRad(double a, double b, double c) {
	return (a*b*c)/(4*herons(a,b,c));
}

int main() {
	double a;
	double b;
	double c;

	double sun;
	double vio;
	double ros;

	string line;
	while(getline(cin, line)) {
		istringstream iss(line);
		iss >> a;
		iss >> b;
		iss >> c;

		sun = circRad(a,b,c) * circRad(a,b,c) * PI; // Need to subtract the other areas.
		vio = herons(a,b,c);
		sun -= vio;
		double ros_rad = 2*vio/(a+b+c);
		ros = ros_rad * ros_rad * PI;
		vio -= ros;
		printf("%.4f %.4f %.4f\n",sun,vio,ros);
	}
	return 0;
}