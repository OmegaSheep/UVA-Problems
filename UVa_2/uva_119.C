/* UVa problem: <119>
 *
 * Topic: (None)
 *
 * Level: 2 points
 * 
 * Brief problem description: 
 *
 *    Determine how much more (or less) each person in the group gives than they receive.
 *
 * Solution Summary:
 *
 *   Mostly a string parsing problem. I store an array of people, and array of the "gains" they have.
 *	 I subtract or add from the "gains" array at the index of each person based on what information I receive about them.
 *
 * Used Resources:
 *
 *   - Textbook
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

using namespace std;
int main() {
	int N;						//# of people
	string line;
	bool first = true;
	while (cin >> N) {
		if (first)
			first = false;
		else
			cout << "\n";
		string name;
		vector<string> people;	//Array of people
		vector<int>	   gains(N);	//Array of gains

		//Name getting.
		getline(cin,line);
		getline(cin,line);
		istringstream iss(line);
		int i = 0;
		while (i < N) {
			iss >> name;
			people.push_back(name);
			i++;
		}
		//Value getting.
		i = 0;
		while (i < N) {
			int amount;
			int split;
			int splitAmount;
			string giver;
			string receiver;

			getline(cin,line);
			istringstream iss(line);
			// Find giver.
			iss >> giver;
			int gpos = find(people.begin(), people.end(), giver) - people.begin();

			// Figure amount.
			iss >> amount;
			iss >> split;
			if (split != 0) {
				splitAmount = amount / split;
			} else {
				splitAmount = 0;
			}
			int j = 0;
			while (j < split ) {
				iss >> receiver;
				int rpos = find(people.begin(), people.end(), receiver) - people.begin();
				gains[rpos] += splitAmount;
				gains[gpos] -= splitAmount;
				j++;
			}
			i++;
		}
		for (int i = 0; i < gains.size(); ++i) {
			cout << people[i] << " " << gains[i] << "\n";
		}
	}
	return 0;
}