/* Name: Jason Mohammad Sarwar
 * CS 631
 * Midterm
 * ls(1)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {

  int noOfFlags = 0;
  int noOfFiles = 0;

  //These integers will be 0 if the flag is off or 1 if the flag is on
  int A = 0;
  int a = 0;
  int C = 0;
  int c = 0;
  int d = 0;
  int F = 0;
  int f = 0;
  int h = 0;
  int i = 0;
  int k = 0;
  int l = 0;
  int n = 0;
  int q = 0;
  int R = 0;
  int r = 0;
  int S = 0;
  int s = 0;
  int t = 0;
  int u = 0;
  int w = 0;
  int x = 0;
  int one = 0;

  int lpr = 0; //For loops

  if(argc == 1) {
    //Execute ls without any flags or files


  }
  else {

    if(argv[2][0] == '-') {
      lpr = 1;
      while(argv[2][lpr] != '\0') {
	if(argv[2][lpr] == 'A') {
	  A = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 'a') {
	  a = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 'c') {
	  c = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 'C') {
	  C = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 'd') {
	  d = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 'F') {
	  F = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 'f') {
	  f = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 'h') {
	  h = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 'i') {
	  i = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 'k') {
	  k = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 'l') {
	  l = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 'n') {
	  n = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 'q') {
	  q = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 'R') {
	  R = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 'r') {
	  r = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 'S') {
	  S = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 's') {
	  s = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 't') {
	  t = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 'u') {
	  u = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 'w') {
	  w = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == 'x') {
	  x = 1;
	  noOfFlags++;
	}
	else if(argv[2][lpr] == '1') {
	  one = 1;
	  noOfFlags++;
	}



      }

    }

  }


  return 0;
}
