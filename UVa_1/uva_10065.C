/* UVa problem: <10065>
 *
 * Topic: (Geometry)
 *
 * Level: 1 points
 * 
 * Brief problem description: Given a set of points counter clockwise and edges, determine the percent of space wasted by putting
 * a convex hull container around it.
 *
 * Solution Summary:
 *
 *	Classic convex hull problem. I compute the convex hull points using a textbook function.
 *	I then calculate the area of both the CH points and the input points using a textbook polygon area function.
 *	I compare the results and create a percentage of wasted space and output it!
 *
 * Used Resources:
 *
 *   - Textbook (Seriously there are so many math functions in there. Also the CH function is from there.)
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
#include <bitset>
#include <tuple>
#include <cmath>

using namespace std;

const double EPS = 1e-9;

/*TEXTBOOK FUNCTIONS*/
struct point { double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {} 

	bool operator < (point other) const {
		if (fabs(x-other.x) > EPS) {
			return x < other.x;
		}
		return y < other.y; 
	} 

	bool operator == (point other) const {
		return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
	}
	point operator - (point other) const {
		return point(x-other.x,y-other.y);
	}
};

double hypot(double dx, double dy) {
	return sqrt(dx * dx + dy * dy);
}

double dist(point p1, point p2) {
	return hypot(p1.x - p2.x, p1.y - p2.y);
}

struct vec { double x, y;
	vec(double _x, double _y) : x(_x), y(_y) {} 
};

vec toVec(point a, point b) {
	return vec(b.x - a.x, b.y - a.y);
}

double cross(vec a, vec b) {
	return a.x * b.y - a.y * b.x;
}

bool ccw(point p, point q, point r) {
	return cross(toVec(p,q), toVec(p,r)) > 0;
}



bool collinear(point p, point q, point r) {
	return fabs(cross(toVec(p,q), toVec(p,r))) < EPS;
}

point pivot(0,0);
bool angleCmp (point a, point b) {
	if (collinear(pivot, a, b)) {
		return dist(pivot, a) < dist(pivot, b);
	}
	double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
	double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
	return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
}

vector<point> CH(vector<point> P) {
	int i, j, n = (int)P.size();
	if (n <= 3) {
		if ( !(P[0] == P[n-1]) ) {
			P.push_back(P[0]);
		}
		return P;
	}
	int P0 = 0;
	for (int i = 1; i < n; ++i) {
		if (P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x)) {
			P0 = i;
		}
	}
	point temp = P[0]; P[0] = P[P0]; P[P0] = temp; //swap

	pivot = P[0];
	sort(++P.begin(), P.end(), angleCmp);

	//Continue

	vector<point> S;
	S.push_back(P[n-1]); S.push_back(P[0]); S.push_back(P[1]);
	i = 2;
	while (i < n) {
		j = (int)S.size()-1;
		if (ccw(S[j-1], S[j], P[i])) S.push_back(P[i++]);
		else S.pop_back();
	}
	return S;
}

double area(const vector<point> &P) {
	double result = 0.0, x1, y1, x2, y2;
	for (int i = 0; i < (int)P.size(); ++i) {
		x1 = P[i].x; x2 = P[(i+1)%P.size()].x;
		y1 = P[i].y; y2 = P[(i+1)%P.size()].y;
		result += (x1 * y2 - x2 * y1);
	}
	return fabs(result) / 2.0;
}

vector<point> PINTs;
vector<point> hull;
bool zort (point a, point b) {
	int pos1 = find(PINTs.begin(), PINTs.end(), a) - PINTs.begin();
	int pos2 = find(PINTs.begin(), PINTs.end(), b) - PINTs.begin();
	return pos1 < pos2;
}

point P0;

enum Direction {CCW, CW, CL};

Direction cross_prod_dir(const point &p1, const point &p2, const point &p0)
{
    double res = cross(toVec(p1,p0), toVec(p2,p0));

    if (fabs(res) < EPS)
        return CL;
    else if (res > 0.0)
        return CW;
    else
        return CCW;
}


double norm(point p) {
	return p.x * p.x + p.y * p.y;
}

bool polar_cmp(point p1, point p2)
{
    Direction res = cross_prod_dir(p1, p2, P0);

    if (res == CW)
        return true;
    else if (res == CCW)
        return false;
    else {
        double d = norm(p1 - P0) - norm(p2 - P0);

        if (fabs(d) < EPS)
            return false;
        else if (d < 0.0)
            return true;
        else
            return false;
    }
}

int main() {
	int counter = 1;
	int N;
	int x;
	int y;
	point PINT;
	while (1) {
		if (counter > 1) {
			cout << "\n";
		}
		cin >> N;
		if ( N == 0 ) {
			break;
		}

		for (int i=0;i<N;++i) {	
			cin >> x;
			cin >> y;
			PINT = point(x,y);
			PINTs.push_back(PINT);
		}
		hull = CH(PINTs);

		sort(hull.begin(), hull.end(), zort);

		double a1 = area(PINTs);
		double a2 = area(hull);
		printf("Tile #%d\n",counter);
		printf("Wasted Space = %.2f %%\n", 100 - (a1/a2)*100);

		/*Prints the test case data 
		printf("Size: %d\n",N);
		for (int i=0;i<PINTs.size();++i) {
			cout << PINTs[i].x << " " << PINTs[i].y << "\n";
		}
		printf("Hull: \n");
		for (int i=0;i<hull.size();++i) {
			cout << hull[i].x << " " << hull[i].y << "\n";
		}
		printf("Area of Tile: %.1f\n", area(PINTs));
		printf("Area of Hull: %.1f\n", area(hull));
		*/

		hull.clear();
		PINTs.clear();
		pivot.x = 0;
		pivot.y = 0;
		counter++;
	}
	return 0;
}

