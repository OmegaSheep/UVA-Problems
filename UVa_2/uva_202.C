/* UVa problem: <202>
 *
 * Topic: (Arithmetic)
 *
 * Level: 2 points
 * 
 * Brief problem description: 
 *
 *   Find the decimal expansion and cycle for a given fraction.
 *
 * Solution Summary:
 *
 * This problem exploits knowledge of the fact that the remainder of Numerator/Denominator repeats itself when a cycle begins.
 * I keep calculating the remainders and using a new numerator of 10*remainder each time. 
 * Once I detect a repeat in remainders I know that I have a cycle and that it begins at the index of the first occurence of the repeated remainder.
 * From there I can simply calculate the digits before the cycle and digits in the cycle itself and format the results.
 *
 * Used Resources:
 *
 *   - Textbook
 *	 - Verbal hearsay from classmates (specifically that the problem involves looking for repeats in remainders to determine the cycle)
 *	 - https://en.wikipedia.org/wiki/Repeating_decimal (Particularly useful, especially that the cycle length is bounded by the denominator)
 *	 - (This specific segment helped a lot) https://en.wikipedia.org/wiki/Repeating_decimal#Converting_repeating_decimals_to_fractions
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
#include <string>

using namespace std;

int main() {
	int num;				//Numerator
	int den;				//Denominator
	int remain;				//Remainder
	vector<int> remainders;	//All remainders.

	vector<int> d;			//Digit array.

	while (cin >> num) {
		cin >> den;

		printf("%d/%d = %d.",num,den,num/den);	//eg. "3/7 = 0."
		num = num % den;
		int offender;							//Index of the first occurence of the repeated remainder.

		while(1) {
			remain = num % den;

			//If we find a repeated remainder we need to exit.
			if(std::find(remainders.begin(), remainders.end(), remain) != remainders.end()) {
				offender = std::distance( remainders.begin(), std::find(remainders.begin(), remainders.end(), remain));
				break;

			//Add the remainder to our array. Calculate the digit and add it to our digit array.
			//Calculate the next remainder. Numerator is 10 * the next remainder.
			} else {
				remainders.push_back(remain);
				d.push_back(num/den);
				remain = num % den;
				num = 10*remain;
			}
		}
		// Grab last digit.
		d.push_back(num/den);

		// If our very last remainder was 0, the number isn't cyclic at all, skip to else case.
		if (remainders[remainders.size()-1] != 0) {
			// Print out the stuff pre-bracket.
			for (int i=1;i<=offender;++i) {
				cout << d[i];// << " ";
			}
			cout << "(";

			//If we ever go over 50 digits, get the heck outta here.
			for (int i=offender+1;i<d.size();++i) {
				if (i>50) {
					cout << "...";
					break;
				}
				cout << d[i];// << " ";

			}
			cout << ")\n";

			//Repeating digits = total digits # of digits minus the digits before the repeat.
			cout << "   " << d.size()-offender-1 <<  " = number of digits in repeating cycle\n\n";
		}
		else {

			//We know there are no cycles so just print all the digits.
			for (int i=1;i<d.size()-1;++i) {
				cout << d[i];// << " ";
			}		
			cout << "(0)\n";	
			cout << "   1 = number of digits in repeating cycle\n\n";
		}
		remainders.clear();
		d.clear();
	}
	return 0;

}

