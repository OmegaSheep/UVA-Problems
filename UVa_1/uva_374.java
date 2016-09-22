/* UVa problem: <374>
 *
 * Topic: (Number Theory)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *   Calculate R = B^p mod M for very large values.
 *
 * Solution Summary:
 *
 *   Perform the operation with Java's Big Integers to avoid any conflicts with overflow or computation time.
 *
 * Used Resources:
 *
 *	 - Textbook
 *	 - Note: Chose Java over C++ for access to Big Ints.
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */

import java.util.Scanner;
import java.math.*;
import java.io.*;
import java.util.*;
import java.lang.*;

public class Main {

	public static void main(String[] args) { 
		Scanner sc = new Scanner(System.in);
		while(sc.hasNext()) {
			BigInteger b = sc.nextBigInteger();
			BigInteger p = sc.nextBigInteger();
			BigInteger m = sc.nextBigInteger();
			System.out.print (b.modPow(p,m)+"\n");
		}
	}
}
