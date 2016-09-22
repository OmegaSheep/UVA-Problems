
/* UVa problem: <12492>
 *
 * Topic: (Combinatorics)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *  - Determine how long it takes a rubiks cube cycle to reset to original state.
 *
 * Solution Summary:
 *  
 *  - I just modified the UVA archive code. I manually perform rotations and check if cube is solved after each run.
 *  - When the cube is finally I solved, I print how many runs it took to solve the cube.
 *  
 * Used Resources:
 *
 *   - UVA CODE ARCHIVE RUBIKS CUBE CODE - File is under /misc/ folder.
 * 
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */


#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

typedef struct{
  char g[9][12];
} Cube;

int cx[6] = {4,4,4,4,1,7};
int cy[6] = {1,4,7,10,4,4};

int rx[6][4][3] = {{{0,1,2}, {5,4,3}, {6,7,8}, {3,4,5}},
		   {{2,2,2}, {5,4,3}, {6,6,6}, {3,4,5}},
		   {{2,1,0}, {5,4,3}, {8,7,6}, {3,4,5}},
		   {{5,4,3}, {8,8,8}, {3,4,5}, {0,0,0}},
		   {{3,3,3}, {3,3,3}, {3,3,3}, {3,3,3}},
		   {{5,5,5}, {5,5,5}, {5,5,5}, {5,5,5}}};

int ry[6][4][3] = {{{3,3,3}, {11,11,11}, {3,3,3}, {3,3,3}},
		   {{3,4,5}, {2,2,2}, {5,4,3}, {6,6,6}},
		   {{5,5,5}, {5,5,5}, {5,5,5}, {9,9,9}},
		   {{8,8,8}, {3,4,5}, {0,0,0}, {5,4,3}},
		   {{0,1,2}, {3,4,5}, {6,7,8}, {9,10,11}},
		   {{11,10,9}, {8,7,6}, {5,4,3}, {2,1,0}}};

int isSolved(Cube c){
  int i, x, y;
  
  for(i = 0; i < 6; i++) {
    for(x = cx[i]-1; x <= cx[i]+1; x++) {
      for(y = cy[i]-1; y <= cy[i]+1; y++) {
        if(c.g[x][y] != c.g[cx[i]][cy[i]]) {
          return 0;
        }
      }
    }
  }
  return 1;
}

Cube Rotate(Cube c, int f){
  char t[3][3]; int i, j, x = cx[f], y = cy[f];

  for(i = 0; i < 3; i++) for(j = 0; j < 3; j++) 
    t[i][j] = c.g[x+i-1][y+j-1];

  for(i = 0; i < 3; i++) for(j = 0; j < 3; j++)
    c.g[x+i-1][y+j-1] = t[2-j][i];

  for(i = 0; i < 3; i++)
    t[0][i] = c.g[rx[f][0][i]][ry[f][0][i]];
  
  for(j = 0; j < 3; j++) for(i = 0; i < 3; i++)
      c.g[rx[f][j  ][i]][ry[f][j  ][i]] =
      c.g[rx[f][j+1][i]][ry[f][j+1][i]];
  
  for(i = 0; i < 3; i++)
    c.g[rx[f][j][i]][ry[f][j][i]] = t[0][i];
  
  return c;
}

//This just performs the rotation 3 times to simulate counter clockwise.
Cube Rotate3(Cube c, int f) {
  c = Rotate(c, f);
  c = Rotate(c, f);
  c = Rotate(c, f);
  return c;
}

void printCube(Cube c){
  int i, j;

  for(i = 0; i < 9; i++){
    for(j = 0; j < 12; j++)
      printf("%c", c.g[i][j] ? c.g[i][j] : ' ');
    printf("\n");
  }
}

int main(){
  int i, j, d; Cube c;

  memset(c.g, 0, sizeof(c.g));
  for(i = 0; i < 3; i++) {
    for(j = 3; j < 6; j++) {
        c.g[i][j] = '4';
    }
  }
  for(i = 3; i < 6; i++) {
    c.g[i][0] = '0';
    c.g[i][1] = '0';
    c.g[i][2] = '0';
  }
  for(i = 3; i < 6; i++) {
    c.g[i][3] = '1';
    c.g[i][4] = '1';
    c.g[i][5] = '1';
  }
  for(i = 3; i < 6; i++) {
    c.g[i][6] = '2';
    c.g[i][7] = '2';
    c.g[i][8] = '2';
  }
  for(i = 3; i < 6; i++) {
    c.g[i][9] = '3';
    c.g[i][10] = '3';
    c.g[i][11] = '3';
  }
  for(i = 6; i < 9; i++) {
    for(j = 3; j < 6; j++) {
        c.g[i][j] = '5';
    }
  }
  
 // while(scanf(" %d", &d) == 1){
 //   c = Rotate(c, d);
 //   printf("\n");
 //   printCube(c);
 // }
  //c = Rotate(c, 4);

  //FACES
  //0 = L
  //1 = F
  //2 = R
  //3 = B
  //4 = U
  //5 = D
  string sequence;

  while(cin >> sequence) {
    int count = 0;

    while(1) {
      for (int i = 0; i < sequence.length(); i++) {
        if (sequence[i] == 'L') {
            c = Rotate(c,0);
        }
        else if (sequence[i] == 'F') {
            c = Rotate(c,1);
        }
        else if (sequence[i] == 'R') {
            c = Rotate(c,2);
        }
        else if (sequence[i] == 'B') {
            c = Rotate(c,3);
        }
        else if (sequence[i] == 'U') {
            c = Rotate(c,4);
        }
        else if (sequence[i] == 'D') {
            c = Rotate(c,5);
        }
        else if (sequence[i] == 'l') {
            c = Rotate3(c,0);
        }
        else if (sequence[i] == 'f') {
            c = Rotate3(c,1);
        }
        else if (sequence[i] == 'r') {
            c = Rotate3(c,2);
        }
        else if (sequence[i] == 'b') {
            c = Rotate3(c,3);
        }
        else if (sequence[i] == 'u') {
            c = Rotate3(c,4);
        }
        else if (sequence[i] == 'd') {
            c = Rotate3(c,5);
        }
      }
      count += 1;
      if (isSolved(c)) {
        break;
      }
    }
    cout << count << "\n";
  }

  return 0;
}