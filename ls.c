/* Name: Jason Mohammad Sarwar
 * CS 631
 * Midterm
 * ls(1)
 */

#include <sys/ioctl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <stropts.h>

/* These integers will be 0 if the flag is off or 1 if the flag is on */

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



int printOut(char* path) {

  int noOfFiles = 0;

  DIR *dir;
  struct dirent *entry;

  struct winsize size;
  int widthRemaining = 0;

  char **fileNames;

  struct stat statbuf;

  if((fileNames = (char**)malloc(sizeof(char*) * 256)) == NULL) {
    fprintf(stderr, "Malloc failed: %s\n", strerror(errno));
    return 16;
  }

  if((dir = opendir(path)) == NULL) {
    fprintf(stderr, "Unable to open current directory: %s\n", strerror(errno));
    return 3;
  }
  else {
    /*
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1) {
    printf(stderr, "ioctl has failed: %s\n", strerror(errno));
    return 3;
     }
    */
    while((entry = readdir (dir)) != NULL) {
      //strcpy(fileNames[noOfFiles], entry -> d_name);
      printf("%s\n", entry -> d_name); 
      noOfFiles++;
    }

    if(closedir(dir) < 0) {
      fprintf(stderr, "Unable to close directory: %s\n", strerror(errno));
      return 4;
    }
  }

  return 0;
}





int main(int argc, char **argv) {

  int noOfFiles = 0;


  int option = 0; //Integer for Switch Case
  int lpr = 0; //Multi-purpose integer

  DIR *dir;
  struct dirent *entry;

  struct winsize size;
  int widthRemaining = 0;

  char **fileNames;

  struct stat statbuf;

  while ((option = getopt(argc, argv, "AacCdFfhiklnqRrSstuwx1")) != -1) {
    switch(option) {
      case 'A':
        A = 1;
        break;
      case 'a':
        a = 1;
        break;
      case 'c':
        c = 1;
        break;
      case 'C':
        C = 1;
        l = 0;
        one = 0;
	n = 0;
	x = 0;
        break;
      case 'd':
        d = 1;
        break;
      case 'F':
        F = 1;
        break;
      case 'f':
        f = 1;
        break;
      case 'h':
        h = 1;
	k = 0;
        break;
      case 'i':
        i = 1;
        break;
      case 'k':
        k = 1;
	h = 0;
        break;
      case 'l':
        l = 1;
        C = 0;
	one = 0;
	n = 0;
	x = 0;
        break;
      case 'n':
        n = 1;
        l = 0;
	C = 0;
	one = 0;
	x = 0;
        break;
      case 'q':
        q = 1;
        w = 0;
        break;
      case 'R':
        R = 1;
        break;
      case 'r':
        r = 1;
        break;
      case 'S':
        S = 1;
        break;
      case 's':
        s = 1;
        break;
      case 't':
        t = 1;
        break;
      case 'u':
        u = 1;
        break;
      case 'w':
        w = 1;
        q = 0;
        break;
      case 'x':
        x = 1;
        l = 0;
	C = 0;
	one = 0;
	n = 0;
        break;
      case '1':
        one = 1;
        l = 0;
	C = 0;
	n = 0;
	x = 0;
        break;
      case '?':
	 //fprintf(stderr, "ls: invalid option -- '%c'\n", optopt);
	 return 4;
      default:
	 printf("ls: internal error\n");
	 return 5;
      }
  }
  
  lpr = 1;
  if((fileNames = (char**)malloc(sizeof(char*) * 256)) == NULL) {
    fprintf(stderr, "Malloc failed: %s\n", strerror(errno));
    return 6;
  }

  while(lpr < argc) {
    if(argv[lpr][0] != '-') {
      if((fileNames[noOfFiles] = (char*)malloc(sizeof(char) * strlen(argv[lpr]))) == NULL) {
	  fprintf(stderr, "Malloc failed: %s\n", strerror(errno));
	  free(fileNames);
	  return 7;
	}
      strcpy(fileNames[noOfFiles], argv[lpr]);
      noOfFiles++;
    }

    lpr++;
  }

  if(noOfFiles > 0) {
    /* First for loop is to find any invalid filenames or directory names */
    for(lpr = 0; lpr < noOfFiles; lpr++) {
      if(stat(fileNames[lpr], &statbuf) != 0) {
	 fprintf(stderr, "ls: cannot access %s: No such file or directory\n", fileNames[lpr]);
	 free(fileNames[lpr]);
	 fileNames[lpr] = NULL;
      }
    }

    for(lpr = 0; lpr < noOfFiles; lpr++) {
      if(fileNames[lpr] == NULL)
        continue;

      if(stat(fileNames[lpr], &statbuf) != 0) {
	 fprintf(stderr, "error in statbuf: %s\n", strerror(errno));
        return 9;
      }

      if(S_ISDIR(statbuf.st_mode) == 0) {
	//Print out files only
	/* Need to edit a lot here in the future */
        printf("%s\n", fileNames[lpr]); 


	/* Need to edit a lot here in the future */
      }      

    }

    for(lpr = 0; lpr < noOfFiles; lpr++) {
      if(fileNames[lpr] == NULL)
        continue;

      if(stat(fileNames[lpr], &statbuf) != 0) {
	 fprintf(stderr, "error in statbuf: %s\n", strerror(errno));
        return 10;
      }

      if(S_ISDIR(statbuf.st_mode) != 0) {
	//Print out directories and their content
        printf("\n%s:\n", fileNames[lpr]);
	printOut(fileNames[lpr]);

      }      

    }




  }
  else {
    if((dir = opendir(".")) == NULL) {
      fprintf(stderr, "Unable to open current directory: %s\n", strerror(errno));
      return 2;
    }
    else {
      /*
      if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1) {
	fprintf(stderr, "ioctl has failed: %s\n", strerror(errno));
	return 3;
      }
      */
      while((entry = readdir (dir)) != NULL) {
	strcpy(fileNames[noOfFiles], entry -> d_name);
	noOfFiles++;
      }

      if(closedir(dir) < 0) {
	fprintf(stderr, "Unable to close directory: %s\n", strerror(errno));
	return 4;
      }
    }

  }


  if(argc == 1) {
    /* Execute ls without any flags or files */
    if((dir = opendir(".")) == NULL) {
      fprintf(stderr, "Unable to open current directory: %s\n", strerror(errno));
      return 2;
    }
    else {
      if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1) {
	fprintf(stderr, "ioctl has failed: %s\n", strerror(errno));
	return 3;
      }

      while((entry = readdir (dir)) != NULL) {
	if(strcmp(entry -> d_name, ".") == 0 || strcmp(entry -> d_name, "..") == 0) {
	  continue;
	}
	lpr = strlen(entry -> d_name) + 3;
	if(lpr > widthRemaining) {
	  printf("\n");
	  widthRemaining = size.ws_col;
	}
	printf("%s   ", entry -> d_name);

      }

      if(closedir(dir) < 0) {
	fprintf(stderr, "Unable to close directory: %s\n", strerror(errno));
	return 4;
      }
      printf("\n");
    }

  }

  for(lpr = 0; lpr < noOfFiles; lpr++)
    free(fileNames[lpr]);
  free(fileNames);
  return 0;
}

