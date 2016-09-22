""" UVa problem: <401>
 *
 * Topic: (None)
 *
 * Level: 2 points
 * 
 * Brief problem description: 
 *
 *  Determine if a word is a palindrome, or a mirrored string or some combination of both.
 *
 * Solution Summary:
 *
 *   The palindrome part is simply a check with string.reverse(). The mirrored portion however involves
 *   me simply replacing all letters in a string (letter-by-letter) with their mirrored components. If 
 *   the string still matches, then it is also a mirrored-string. I return the results via boolean check.
 *
 * Used Resources:
 *
 *   - None.
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
"""

import sys
import string

#This is my mirror function.
def function(x):
    badLetters = ["B","C","D","F","G","K","N","P","Q","R","4","6","7","9"]
    if (x in badLetters):
        return " "
    
    if (x == "3"):
        return "E"
    if (x == "E"):
        return "3"
    if (x == "J"):
        return "L"
    if (x == "L"):
        return "J"
    if (x == "S"):
        return "2"
    if (x == "2"):
        return "S"
    if (x == "Z"):
        return "5"
    if (x == "5"):
        return "Z"
    return x
    
    

for line in sys.stdin:
    for var in line.split():
        palin = False
        mirror = False
        word = var
        reverse = word[::-1]
        
        if (word == reverse):
            palin = True
        
        empty = ""
        for letter in reverse:
            newLetter = function(letter)
            empty+=newLetter
        if (word == empty):
            mirror = True
        
        if (palin and mirror):
            print(word,"-- is a mirrored palindrome.")
            print("")
        elif (palin):
            print(word,"-- is a regular palindrome.")
            print("")
        elif (mirror):
            print(word,"-- is a mirrored string.")
            print("")
        else:
            print(word,"-- is not a palindrome.")
            print("")

