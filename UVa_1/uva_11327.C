/* UVa problem: <11327>
 *
 * Topic: (Number Theory)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *	Determine the Nth rational number fraction between 0 and 1 and print it out.
 *
 * Solution Summary:
 *
 *   Iterating through the entire number range is too lengthy. This problem exploits knowledge that:
 *	 1. Every denominator shows up phi(denominator) times in order.
 *	 2. Every denominator has phi(denominator) possible numerators.
 *
 *	 First, I precompute the sum of all phis at a given index until the total sum is greater than the max N.
 *	 Then I get the denominator first via:
 *
 *	 Checking the sum of all the phis at the current index.
 *	 Once the sum is over the input number, we have our denominator.
 *
 * 	 Then for numerator, I know it has to be one of the numbers coprime to denominator.
 *	 At first I iterated through the the list of all coprime numbers (gcd(den,num) == 1) but after
 *	 trial and error I figured out the index of the coprime numerator (given a list of all coprime numbers) 
 *	 could be found at:
 *	 //int indexOfTop = input-1 - sumPhis[bot-1]; 
 *	 Which translates to the input N - the sum of phis before the denominator.
 *
 *	 Finally, once I have the two numbers, I simply print them out and move onto the next case!
 *
 *
 * Used Resources:
 *
 *   - Textbook Sieve Code / Is Prime Code.
 *	 - Textbook Phi code.
 *	 - Lots of tears. :'(
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
#define UNVISITED -1
#define VISITED 1
#define INF 1000000000
#define MAX 12158598919

using namespace std;

typedef long long ll;
typedef vector<int> vi;

ll _sieve_size;
bitset<10000010> bs;
vi primes;

int gcd(int a, int b) { return b ==0 ? a : gcd(b, a % b); }

void sieve(ll upperbound) {
	_sieve_size = upperbound + 1;
	bs.set();
	bs[0] = bs[1] = 0;
	for (ll i = 2; i <= _sieve_size; ++i) if (bs[i]) {

		for (ll j = i * i; j <= _sieve_size; j += i) bs[j] = 0;
		primes.push_back((int)i);
	}
}

bool isPrime(ll N) {
	if (N <= _sieve_size) return bs[N];
	for (int i = 0; i < (int)primes.size(); i++) {
		if (N % primes[i] == 0) return false;
	}
	return true;
}

ll EulerPhi(ll N) {
	ll PF_idx = 0, PF = primes[PF_idx], ans = N;
	while (PF * PF <= N) {
		if (N % PF == 0) ans -= ans / PF;
		while (N % PF == 0) N /= PF;
		PF = primes[++PF_idx];
	}
	if (N != 1) ans -= ans / N;
	return ans;                                                            
}

int main() {
	sieve(100000);
	vi phis(primes);
	vector<ll> sumPhis;

	sumPhis.push_back(1);
	sumPhis.push_back(1);
	ll total = 1;
	int index = 2;
	while (total < MAX) {
		total+=EulerPhi(index);
		sumPhis.push_back(total);
		index++;
	}

	ll input;
	while(cin >> input) {
		if (input == 0) {
			break;
		}
		else if (input == 1) {
			cout << "0/1\n";
			continue;
		}
		else if (input == 2) {
			cout << "1/1\n";
			continue;
		}

		//Top is numerator, bot is denominator.
		int top;
		int bot;

		//To get the numerator, simply check the sum of all the phis at the current index.
		//Once the sum is over the input number, we have our denominator.
		for (int i = 0; i < sumPhis.size(); ++i) {
			if (sumPhis[i] >= input-1 and sumPhis[i-1] < input-1) {
				bot = i;
			}
		}
		
		//Index of the numerator amongst the list of numbers coprime to denominator.
		int indexOfTop = input-1 - sumPhis[bot-1];

		int counter = 0;
		for (int i = 1; i < bot; ++i) {
			if (gcd(bot,i) == 1)
				counter+=1;
			if (counter == indexOfTop) {
				cout << i;
				break;
			}
		}
		cout << "/" << bot << "\n";
	}
	return 0;
}