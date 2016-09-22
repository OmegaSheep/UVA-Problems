/* UVa problem: <1266>
 *
 * Topic: (Number Theory)
 *
 * Level: 2 points
 * 
 * Brief problem description: 
 *
 *	Create a magic square of size N where N is odd. Square must sum up to the same value in all rows, columns and diagonals.
 *
 * Solution Summary:
 *
 *   Use the construction strategy described in the textbook on page 361.
 *	 Put a 1 in the center, and travel diagonally upward each step. Travel straight down if diagonal up is taken. 
 *
 * Used Resources:
 *
 *   - Textbook.
 *	 - http://stackoverflow.com/questions/1489830/efficient-way-to-determine-number-of-digits-in-an-integer (digitSize function)
 *	 
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>
using namespace std;

// Returns digit length of integer.
unsigned digitSize (unsigned i)
{
    return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}

int rowAdj(int r, int N) {
	r -= 1;
	if (r < 0) {
		r = N - 1;
	}
	return r;
}

int colAdj(int c, int N) {
	c += 1;
	if (c >= N) {
		c = 0;
	}
	return c;
}

bool first = true;
int maxDig;

int main() {
	int N;
	while(cin >> N) {
		int sq[N][N];
		int num = 1;
		memset(sq,-1,sizeof(sq));
		maxDig = digitSize(N*N);
		int row = 0;
		int col = N/2;

		//Base case 
		sq[row][col] = num;
		num++;

		while (num <= N*N) {
			if (sq[rowAdj(row,N)][colAdj(col,N)] < 1) {
				row = rowAdj(row,N);
				col = colAdj(col,N);
			} else {
				row = colAdj(row,N);
			}
			sq[row][col] = num;
			num++;
		}

		//Print newline if not the first square.
		if (first) {
			first = false;
		} else {
			cout << "\n";
		}

		//What is the sum for this square?
		int sum = 0;
		for (int i = 0; i < N; ++i) {
			sum += sq[0][i];
		}

		//Print the detail line, then print the square.
		printf("n=%d, sum=%d\n",N,sum);
		for (int i = 0; i < N; ++i) {
			cout << " ";
			for (int j = 0; j < N; ++j) {
				int spaces = maxDig - digitSize(sq[i][j]);
				while (spaces > 0) {
					cout << " ";
					spaces--;
				}
				cout << sq[i][j];
				if (j != N - 1) 
					cout << " ";
			}
			cout << "\n";
		}
	}
	return 0;
}