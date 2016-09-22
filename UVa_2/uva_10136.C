/* UVa problem: <10136>
 *
 * Topic: (Geometry)
 *
 * Level: 2 points
 * 
 * Brief problem description: 
 *
 *    Given a pan of chocolate chips, determine where to stab the cookie cutter to contain the most chocolate chips.
 *
 * Solution Summary:
 *
 *		Essentially, I go through every pair of points and if I am able to create a circle of radius 2.5 using 2 of the chips,
 *		I then check how many other chips lie within the circle (You have to check both of the circles you can create from
 *		each pair of points.)
 *
 *		If the amount of chips in a given circle is greater than my best, the center of that circle becomes the new best place
 *		to stab the cookie cutter.
 *
 *	
 * Used Resources:
 *
 *   - Textbook (Seriously I used like a million geometry functions from it, notably circle2ptsrad() and insideCircle() )
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <bitset>
#include <tuple>
#include <cmath>
#include <utility>
#include <string>
#include <sstream>
#define EPS 1e-8

using namespace std;

struct point { double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {} 
	bool operator < (point other) const {
		if (fabs(x -  other.x) > EPS) {
			return x < other.x;
		}
		return y < other.y;
	}
};

double dist(point p1, point p2) {
	//return hypot(p1.x - p2.x, p1.y - p2.y);
	return sqrt( (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) );
}

int insideCircle(point p, point c, double r) {
	double dx = p.x - c.x, dy = p.y - c.y;
	double Euc = dx * dx + dy * dy, rSq = r * r;
	return Euc < rSq? 0 : Euc == rSq ? 1 : 2; 
}

bool circle2PtsRad(point p1, point p2, double r, point &c) {
	double d2 = (p1.x - p2.x) * (p1.x - p2.x) +
				(p1.y - p2.y) * (p1.y - p2.y);
	double det = r * r/ d2 - 0.25;
	if (det < 0.0) return false;
	double h = sqrt(det);
	c.x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
	c.y = (p1.y + p2.y) * 0.5 + (p2.x - p1.x) * h;
	return true;
}

// For debugging.
void printVec(vector<point> p) {
	for (int i=0; i <p.size();++i) {
		cout << p[i].x << " " << p[i].y << "\n";
	}
}

int main() {
	string line;
	getline(cin,line);
	istringstream iss(line);

	vector<point> points;

	int N;
	iss >> N;
	getline(cin,line);

	double x;
	double y;

	for (int q = 0; q < N; ++q) {
		if (q != (N and 0)) cout <<"\n";
		getline(cin,line);
		while (line != "") {
			istringstream iss(line);
			iss >> x;
			iss >> y;
			points.push_back(point(x,y));
			getline(cin,line);
		}
		if (points.size() == 1) {
			cout << "1\n";
			points.clear();
			continue;
		}
		point center = point();
		int maxTotal = 1;
		int total = 0;
		for (int i = 0;i < points.size(); ++i) {
			for (int j = 0;j < points.size(); ++j) {
					total = 0;
					if (circle2PtsRad(points[i],points[j],2.5,center)) {
						//How many Chips are in range?
						for (int k = 0;k < points.size(); ++k) {
							if (dist(center,points[k]) - 2.5 <= EPS) {
								total++;
							}
						}
						if (total > maxTotal) {
							maxTotal = total;
						}
					}	
			}
		}
		cout << maxTotal << "\n";
		points.clear();
	}
	return 0;
}