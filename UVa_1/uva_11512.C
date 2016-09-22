/* UVa problem: <11512>
 *
 * Topic: (String)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *   Find the longest repeated substring (lexicographically) in a given string and the number of times it occurs.
 *
 * Solution Summary:
 *
 *   1. Construct a suffix array and Longest Common Prefix array using textbook functions.
 *   2. Once the Longest Common Substring is found, use a counting function to count how often it occurs.
 *   3. Print out both values and reset the arrays.
 *	 4. I really want to emphasize: I basically copy pasted the TEXTBOOK code. A lot of the functions they use
 *		are spaghetti code but ultimately they work very well so I stuck with it.
 *
 * Used Resources:
 *
 *   - Textbook (seriously like 99% of this is from the textbook, except the counting function and some minor parsing)
 * 
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <cmath>
#define MAX_N 100010

using namespace std;

char T[MAX_N];
int n;
int RA[MAX_N], tempRA[MAX_N];
int SA[MAX_N], tempSA[MAX_N];
int c[MAX_N];
int Phi[MAX_N];
int LCP[MAX_N], PLCP[MAX_N];

//Resets all the arrays.
void resetAll() {
	memset(T, 0, sizeof T);
	memset(RA, 0, sizeof RA);
	memset(SA, 0, sizeof SA);
	memset(tempRA, 0, sizeof tempRA);
	memset(tempSA, 0, sizeof tempSA);
	memset(Phi, 0, sizeof Phi);
	memset(LCP,0,sizeof LCP);
	memset(PLCP,0,sizeof PLCP);
}

//Returns # of times a substring occurs in a string.
int countSubstr(string str, string sub) {
	int count = 0;
	int position = str.find(sub,0); 			//Get the first occurence.
	while (position != -1) {					//While we can still find the substr;
		count++;								//Increment count cause we found it.
		position = str.find(sub,position+1);	//Try to find it starting from beyond the previous occurence.
	}
	return count;
}

//TEXTBOOK SPAGHETTI CODE - Basically a radix sort.
void countingSort(int k) {
	int i, sum, maxi = max(300, n);
	memset(c, 0, sizeof c);
	for (i = 0; i < n; i++) 
		c[i + k < n ? RA[i + k] : 0]++;
	for (i = sum = 0; i < maxi; ++i) {
		int t = c[i]; c[i] = sum; sum += t; }
	for (i = 0; i < n; i++) 
		tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
	for (i = 0; i < n; i++) 
		SA[i] = tempSA[i];
	
}

//TEXTBOOK SPAGHETTI CODE - Constructs Suffix Array
void constructSA() {
	int i, k, r;
	for (i = 0; i < n; i++) RA[i] = T[i];
	for (i = 0; i < n; i++) SA[i] = i;
	for (k = 1; k < n; k <<= 1) {
		countingSort(k);
		countingSort(0);
		tempRA[SA[0]] = r = 0;
		for (i = 1; i < n; i++) 
			tempRA[SA[i]] = //
			(RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
		for (i = 0; i < n; i++) 
			RA[i] = tempRA[i];
		if (RA[SA[n-1]] == n-1) break;
	}
}

//TEXTBOOK SPAGHETTI CODE - Computes the longest common prefix array.
void computeLCP() {
	int i, L;
	Phi[SA[0]] = -1;
	for (i =1; i < n; i++)
		Phi[SA[i]] = SA[i-1];
	for (i = L = 0; i < n; i++) {
		if (Phi[i] == -1) { PLCP[i] = 0; continue; }
		while (T[i + L] == T[Phi[i] + L]) L++;
		PLCP[i] = L;
		L = max(L-1, 0);
	}
	for (i = 0; i < n; i++)
		LCP[i] = PLCP[SA[i]];
}

int main() {
	int N;
	cin >> N;

	int i = 0;
	while (i < N) {
		cin >> T;
		n = (int)strlen(T);
		T[n++] = '$';
		constructSA();
		computeLCP();

		int max = -1;
		int maxIndex = -1;

		for (int i = 0; i<n; ++i) {
			if (LCP[i] > max) {
				max = LCP[i];
				maxIndex = i;
			}
		}

		if (maxIndex != 0) {
			string ans(T + SA[maxIndex]);
			ans = ans.substr(0, LCP[maxIndex]);
			cout << ans;
			string input(T);
			int n = countSubstr(input,ans);
			cout << " " << n << "\n";
		}
		else {
			cout << "No repetitions found!\n";
		}
		i++;
		resetAll();
	}
}