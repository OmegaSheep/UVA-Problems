/* UVa problem: <389>
 *
 * Topic: (None)
 *
 * Level: 2 points
 * 
 * Brief problem description: 
 *
 *   Given a number and its base, convert it to a new base and make sure it fits on a calculator screen.
 *
 * Solution Summary:
 *
 *   Java has a built in resource for converting integer bases. (parseInt) I simply use that to compute the answer.
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

import java.util.Scanner;
import java.math.*;
import java.io.*;
import java.util.*;
import java.lang.*;

public class Main {
	
	public static void main(String[] args) {
		Scanner sc = new Scanner (System.in);
		while (sc.hasNext()) {
			String num = sc.next();
			int base1 = sc.nextInt();
			int base2 = sc.nextInt();
			int ans = Integer.parseInt(num,base1);
			String ans2 = Integer.toString(ans,base2);
			ans2.toUpperCase();
			if (ans2.length() > 7) {
				System.out.print("  ERROR\n");
			} else {
				if (ans2.length() != 7) {
					int l = 7 - ans2.length();
					do { System.out.print(" ");} while(l-- > 1);
				}
				System.out.print(ans2.toUpperCase()+"\n");
			}
		}
	}
}