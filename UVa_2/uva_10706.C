/* UVa problem: <10706>
 *
 * Topic: (Binary Search)
 *
 * Level: 2 points
 * 
 * Brief problem description: 
 *
 *  Find what digit is at a given index given a sequence of increasing sequences. 1, 1,2, 1,2,3, 1,2,3,4...
 *
 * Solution Summary:
 *
 *  1. Create a the largest possible sequence, the length of each individual sequence and the length of all sequences up to a point via preprocessing.
 *	2. Subtract the length of all sequences up to a point from the given index.
 *	3. Once this is done, use the remaining value to index into the pre-created largest sequence.
 *	4. Return the digit you find in step 3.
 *
 * Used Resources:
 *
 *   - Textbook
 *   - http://stackoverflow.com/questions/1489830/efficient-way-to-determine-number-of-digits-in-an-integer (digitSize function)
 *	 - http://www.algorithmist.com/index.php/UVa_10706 (Cited their explanation after I had mostly solved the problem)
 *	 
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */


#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <map>
#include <stdio.h>
#include <climits>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

long SS[312679];  // Contains sequence length at i.
long TT[312679];  // Contains total sequence length at i. Created from SS.
string sequence;	// Largest digit sequence.

// Returns digit length of integer.
unsigned digitSize (unsigned i)
{
    return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}

// Iterative search to determine what SS sequence the number lies in.
long regSearch(long A[], long value, long i) {
  if (A[i] >= 2147378477) {
    return 31267;
  }
  if (A[i] <= value && A[i+1] >= value) {
    return i;
  }
  else {
    return regSearch(A, value, i+1);
  }
}

// Used to create SS.
long seq_length(long k) {
  if (k==0) {
    return 0;
  }
  if (SS[k] != 0 && k != 0) {
    return SS[k];
  }
  else {
    return SS[k] = seq_length(k-1) + digitSize(k);
  }
}

// Used to create TT.
long AofK(long k) {
	long ans = 0;
	for (long i=1;i<=k;++i) {
		ans += seq_length(i);
	}
	return ans;
}

int main() {
	int N;
	cin >> N;

	SS[0] = 0;
	SS[1] = 1;
	
	// Create the largest sequence for indexing later.
	for (int i = 1; i < 31268; ++i) {
		sequence.append(to_string(i));
	}

	//Create TT which creates SS automatically.
	for (int i = 1; i< 31268; i++) {
  	TT[i] = AofK(i);
	}
	
	long index;
	while(cin >> index) {
    long result = regSearch(TT,index,0);
    index = index - TT[result];
	  cout << sequence[index-1] << "\n";
	}
	
	return 0;
}
