/* UVa problem: <11837>
 *
 * Topic: (String)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *   Determine if a music snippet has been plagiarized based on semitone differences.
 *
 * Solution Summary:
 * 
 *   Clever use of KMP Algorithm. For the input, I do something I called "Gapify" in which I create an array of int values,
 *	 which are representative of the DIFFERENCE in semi-tone of two given notes. eg. C -> E becomes 2.
 *
 *	 Following this I use another array with the reversed values which could be plagiarized in a different tone
 *	 (this step might not be necessary now since my "x = (x+12 %) 12" code fixed a lot of my problems, I theorized this could work since
 *	 it essentially converts the reversed case into the regular case, automatically testing both).
 *
 *	 Whatever the case may be, if KMP finds the substring of tone differences inside of the actual melody's tone 
 *	 differences the result is positive and if not, the result is negative. P and P2 store the two versions of the snippet
 *	 and T stores the melody itself.
 *
 * Used Resources:
 *
 *   - Textbook (KMP Algorithm and logic code)
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */

#define MAX_N 100010
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

char T[MAX_N], P[MAX_N], P2[MAX_N];
int b[MAX_N], n, m;

void kmpPreprocess() {
	n = strlen(T);
	m = strlen(P);
	int i = 0, j = -1; b[0] = -1;
	while (i < m) {
		while (j >= 0 && P[i] != P[j]) j = b[j];
			i++; j++;
			b[i] = j;
	}
}

int kmpSearch() {
	int i = 0, j = 0;
	while (i < n) {
		while (j >= 0 && T[i] != P[j]) j = b[j];
		i++; j++;
		if (j == m) {
			return 1;
			//j = b[j];
		}
	}
	return 0;
}

//Quintessential Test Case
// 1 11 9
// vs
// 12 2
int noteVal(string note) {
	if (note == "B#" || note == "C")
		return 1;
	if (note == "C#" || note == "Db")
		return 2;
	if (note == "D")
		return 3;
	if (note == "Eb" || note == "D#")
		return 4;
	if (note == "E" || note == "Fb")
		return 5;
	if (note == "F" || note == "E#")
		return 6;
	if (note == "Gb" || note == "F#")
		return 7;
	if (note == "G")
		return 8;
	if (note == "Ab" || note == "G#")
		return 9;
	if (note == "A")
		return 10;
	if (note == "Bb" || note == "A#")
		return 11;
	if (note == "B" || note == "Cb")
		return 12;
}

char strVal(int x) {
	//HOLY FUCK THIS FIXES EVERYTHING YES
	x = (x + 12) % 12;

	/*
	if (x == -11)
		return 'a';
	if (x == -10)
		return 'b';
	if (x == -9)
		return 'c';
	if (x == -8)
		return 'd';
	if (x == -7)
		return 'e';
	if (x == -6)
		return 'f';
	if (x == -5)
		return 'g';
	if (x == -4)
		return 'h';
	if (x == -3)
		return 'i';
	if (x == -2)
		return 'j';
	if (x == -1)
		return 'k';
	*/
	if (x == 0)
		return 'l';
	if (x == 1)
		return 'm';
	if (x == 2)
		return 'n';
	if (x == 3)
		return 'o';
	if (x == 4)
		return 'p';
	if (x == 5)
		return 'q';
	if (x == 6)
		return 'r';
	if (x == 7)
		return 's';
	if (x == 8)
		return 't';
	if (x == 9)
		return 'u';
	if (x == 10)
		return 'v';
	if (x == 11)
		return 'w';
}

//This function reverses the strToVal functions results.
char flop(char x) {
	//HOLY FUCK THIS FIXES EVERYTHING YES
	x = (x + 12) % 12;

	if (x == 'a')
		return 'w';
	if (x == 'b')
		return 'v';
	if (x == 'c')
		return 'u';
	if (x == 'd')
		return 't';
	if (x == 'e')
		return 's';
	if (x == 'f')
		return 'r';
	if (x == 'g')
		return 'q';
	if (x == 'h')
		return 'p';
	if (x == 'i')
		return 'o';
	if (x == 'j')
		return 'n';
	if (x == 'k')
		return 'm';
	if (x == 'm')
		return 'k';
	if (x == 'n')
		return 'j';
	if (x == 'o')
		return 'i';
	if (x == 'p')
		return 'h';
	if (x == 'q')
		return 'g';
	if (x == 'r')
		return 'f';
	if (x == 's')
		return 'e';
	if (x == 't')
		return 'd';
	if (x == 'u')
		return 'c';
	if (x == 'v')
		return 'b';
	if (x == 'w')
		return 'a';
}

int main() { 

	/**Giant vector list of note sections**/

	int m;
	int t;
	string sNote; //String copy of current note. For vector storage.

	int val1;
	int val2;
	char c;

	while (cin >> m >> t) {

		memset(P, 0, MAX_N);
		memset(T, 0, MAX_N);
		memset(b, 0, MAX_N);

		if (m == 0 && t == 0) {
			break;	
		}

		/** Store and gapify Melody **/
		cin >> sNote;
		val1 = noteVal(sNote);
		for (int i=0;i<m-1;++i) {
			cin >> sNote;
			val2 = noteVal(sNote);
			c = strVal(val1 - val2);
			T[i] = c;
			val1 = val2;
		}

		/** Store and gapify Snippet **/
		cin >> sNote;
		val1 = noteVal(sNote);
		for (int j=0;j<t-1;++j) {
			cin >> sNote;
			val2 = noteVal(sNote);
			c = strVal(val1 - val2);
			P[j] = c;
			P2[j] = flop(c);
			val1 = val2;
		}

		kmpPreprocess();
		//cout << "T: " << T << "\n";
		//cout << strlen(P) << "\n";
		//cout << "P: " << P << "\n";
		int ans = 0;

		if (m <= 1)
			ans = 1;
		if (kmpSearch())
			ans = 1;
		for (int i = 0; i < strlen(P);++i) {
			P[i] = P2[i];
		}
		//cout << strlen(P) << "\n";
		//cout << "P2: " << P << "\n";
		if (kmpSearch())
			ans = 1;
		if (ans == 1) {
			cout << "S\n";
		} else {
			cout << "N\n";
		}
	}		
	return 0;
}	
