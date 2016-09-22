/* UVa problem: <11584>
 *
 * Topic: (Dynamic Programming)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *	Determine the number of sub-palindrome partitions in a given word.
 *
 * Solution Summary:
 *
 *   Summary: Use dynamic programming to solve for smaller string values.
 *
 *	 When determining if something is a palindrome, I use dynamic programming to ensure that I never have to recomputer
 *	 palindrome status for any substring of the original. This allows me to check if a substring is a palindrome in O(1).
 *
 *	 As for the program itself, my dynamic array (dp) stores the number of palindrome partitions up to a given length i.
 *	 This results in dp[length-1] containing the solution the entire string.
 *
 *	 To computer intermediate values, I check all "j" up to "i" and see if string(j,i) is a palindrome. If the value of dp[j] + 1 is better
 *	 then dp[i] then I replace dp[i] with its new value. Doing this throughout the whole string will provide me with the solution.
 *
 * Used Resources:
 *
 *   - Textbook (useful palindrome resources)
 *	 - https://en.wikipedia.org/wiki/Longest_common_substring_problem (Later did not use this in my code)
 *	 - Zachary. We talked about this in his office hours at some length.
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <sstream>
#define MAX_VAL 1000

using namespace std;

int sp[MAX_VAL][MAX_VAL];

int dp[MAX_VAL];

string line;

bool isPalindrome(int i, int j) {

	if (j-i == 1 and line[i] == line[j]) {
		return sp[i][j] = 1;
	} 

	if (j-i == 1 and line[i] != line[j]) {
		return sp[i][j] = 0;
	}

	if (i == j) return sp[i][j] = 1;
	
	if (sp[i][j] != -1)
		return sp[i][j];

	else {
		if (line[i] != line[j]) {
			return sp[i][j] = 0;
		}
		else { 
			return isPalindrome(i+1,j-1);
		}
	}
}


int main() {

	int cases;
	int counter = 0;
	memset(dp, 0 ,sizeof(dp));

	cin >> cases;
	getline(cin, line);

	while (counter < cases)	{
		counter++;
		getline(cin, line);

		memset(sp, -1, sizeof(sp));
		
		for (int i = 0; i < line.length(); ++i) {
			dp[i] = i;									//Just needs to be bigger than the max # of possible splits for that sub string.
		}

		// Function
		for (int i = 1; i < line.length(); ++i) {

			if (isPalindrome(0,i)) {
				dp[i] = 0;								//If it's a palindrome it requires 0 splits.
			}

			for (int j = 0; j < i; ++j) {

				if (isPalindrome(j+1, i)) {
					dp[i] = min(dp[i], dp[j] + 1);	 	//If dp[j] + 1 is better than the existing value of dp[i], we replace it.
				} 
			}
		}	
			cout << dp[line.length()-1]+1 << "\n";

	}
	return 0;
}
