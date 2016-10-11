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

#define S_IFWHT 0160000 /* whiteout */
#define S_ISWHT(m) (((m) & S_IFMT) == S_IFWHT)

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
  
  char *fullPath;
  
  struct stat statbuf;
  
  int lpr = 0; //Multi-purpose integer
  int lpr2 = 0; //Multi-purpose integer
  int max = 0;
  int aMax = 0;

  long itotal = 0;
  
  if(d == 1 && strcmp(path, ".") == 0) {
    
    if(stat(path, &statbuf) != 0) {
      fprintf(stderr, "error in statbuf: %s\n", strerror(errno));
      return 13;
    }
    if(i == 1) {
      printf("%i ", (int)statbuf.st_ino); 
    }
    if(s == 1) {
      printf("%i ", (int)statbuf.st_blocks); 
    }
    printf(".");
    
    if(F == 1)
      printf("/");
    
    printf("\n");
    return 0;
    
  }
  
  if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1) {
    fprintf(stderr, "ioctl has failed: %s\n", strerror(errno));
    return 3;
  }
  widthRemaining = size.ws_col;
  
  if((fileNames = (char**)malloc(sizeof(char*) * 256)) == NULL) {
    fprintf(stderr, "Malloc failed: %s\n", strerror(errno));
    return 16;
  }
  
  if((dir = opendir(path)) == NULL) {
    fprintf(stderr, "Unable to open current directory: %s\n", strerror(errno));
    return 3;
  }
  
  //Loop through all the files and directories in current directory and print them
  while((entry = readdir (dir)) != NULL) {

    if(A == 0 && a == 0 && ((entry -> d_name)[0] == '.')) {
      continue;
    }
    else if(A == 0 && a == 1 && ((entry -> d_name)[0] == '.')) {
    
      if((fullPath = (char*)malloc(sizeof(char) * (strlen(path) + strlen(fileNames[lpr])))) == NULL) {
	fprintf(stderr, "Malloc failed: %s\n", strerror(errno));
	return 17;
      }
      
      if(stat(fullPath, &statbuf) != 0) {
	fprintf(stderr, "error in statbuf: %s\n", strerror(errno));
	return 18;
      }

      if(!S_ISDIR(statbuf.st_mode))
	continue;

    }
    else if(A == 1 && ((entry -> d_name)[0] == '.')) {
      if(strcmp(entry -> d_name, ".") == 0 || strcmp(entry -> d_name, "..") == 0 ) {
	continue;
      }
    }

    if(((strcmp(entry -> d_name, ".") == 0 || strcmp(entry -> d_name, "..") == 0 )) && a == 0)
      continue;

    if((fileNames[noOfFiles] = (char*)malloc(sizeof(char) * strlen(entry -> d_name))) == NULL) {
      fprintf(stderr, "Malloc failed: %s\n", strerror(errno));
      return 17;
    }
    
    strcpy(fileNames[noOfFiles], entry -> d_name);
    
    if(max < strlen(fileNames[noOfFiles])) {
      max = strlen(fileNames[noOfFiles]);
    }
    
    if(s == 1) {
      if((fullPath = (char*)malloc(sizeof(char) * (strlen(path) + strlen(fileNames[lpr])))) == NULL) {
	fprintf(stderr, "Malloc failed: %s\n", strerror(errno));
	return 14;
      }
      strcpy(fullPath, path);
      strcat(fullPath, "/");
      strcat(fullPath, fileNames[noOfFiles]);
      
      
      if(stat(fullPath, &statbuf) != 0) {
	fprintf(stderr, "error in statbuf: %s\n", strerror(errno));
	return 10;
      }
      if(h == 1)
	itotal += ((long)statbuf.st_size);
      else if(k == 1)
	itotal += (((long)statbuf.st_size) / 1024);
      else
	itotal += (long)(statbuf.st_blocks);
      
      //free(fullPath);
    }
    
    noOfFiles++;
  }
  
  if(s == 1) {
    printf("total %ld", itotal);
    if(h == 1)
      printf("B");
    else if(k == 1)
      printf("KB");
    printf("\n");
  }

  max += 2;

  aMax = max;  
  if(i == 1)
    aMax += 6;
  if(s == 1) {
    if(h == 1)
      aMax += 7;
    else if(k == 1)
      aMax += 5;
    else
      aMax += 3;
  }
  if(F == 1)
    aMax += 1;

  
  for(lpr = 0; lpr < noOfFiles; lpr++) {
    
    if(stat(fileNames[lpr], &statbuf) != 0) {
      fprintf(stderr, "error in statbuf: %s\n", strerror(errno));
      return 14;
    }
    
    
    if(aMax > widthRemaining) {
      printf("\n");
      widthRemaining = size.ws_col;
    }
    
    if(i == 1) {
      printf("%i ", (int)statbuf.st_ino); 
    }
    if(s == 1) {
      if(h == 1)
	printf("%ld B ", ((long)statbuf.st_size)); 
      else if(k == 1)
	printf("%ld KB ", ((long)statbuf.st_size) / 1024); 
      else
	printf("%ld ", (long)statbuf.st_blocks); 
    }
    printf("%s", fileNames[lpr]);
    if(F == 1) {
      if(S_ISDIR(statbuf.st_mode))
	printf("/");
      else if(S_ISLNK(statbuf.st_mode))
	printf("@");
      else if(S_ISSOCK(statbuf.st_mode))
	printf("=");
      else if(S_ISFIFO(statbuf.st_mode))
	printf("|");
      else if(!S_ISDIR(statbuf.st_mode) && ((statbuf.st_mode & S_IXUSR) || (statbuf.st_mode & S_IXGRP) || (statbuf.st_mode & S_IXOTH) ) )
	printf("*");
      else if(S_ISWHT(statbuf.st_mode))
	printf("%c", '%');
    }

    for(lpr2 = 0; lpr2 < max - strlen(fileNames[lpr]); lpr2++)
      printf(" ");
    widthRemaining -= aMax;
    
    
  }
  
  if(closedir(dir) < 0) {
    fprintf(stderr, "Unable to close directory: %s\n", strerror(errno));
    return 4;
  }
  
  //Loop through list of files and directories
  for(lpr = 0; lpr < noOfFiles; lpr++) {
    if(R == 1 && strcmp(fileNames[lpr], "..") != 0 && strcmp(fileNames[lpr], ".") != 0) { //Recursive flag
      if((fullPath = (char*)malloc(sizeof(char) * (strlen(path) + strlen(fileNames[lpr])))) == NULL) {
	fprintf(stderr, "Malloc failed: %s\n", strerror(errno));
	return 14;
      }
      strcpy(fullPath, path);
      strcat(fullPath, "/");
      strcat(fullPath, fileNames[lpr]);
      free(fileNames[lpr]);
      if(stat(fullPath, &statbuf) != 0) {
	fprintf(stderr, "error in statbuf: %s\n", strerror(errno));
	return 10;
      }
      
      if(S_ISDIR(statbuf.st_mode) != 0) {
	//Print out directories and their contents
	
	printf("\n%s:\n", fullPath);
	
	printOut(fullPath);
      } 
      
      if(fullPath != NULL) {
	free(fullPath);
	fullPath = NULL;
      }
    }
    else {
      if(fileNames[lpr] != NULL) {
	free(fileNames[lpr]);
	fileNames[lpr] = NULL;
      }
    }
    
  }
  if(fileNames != NULL) {
    free(fileNames);
    fileNames = NULL;
  }
  
  return 0;
}




/* Main function */
int main(int argc, char **argv) {
  
  int noOfFiles = 0;
    
  int option = 0; //Integer for Switch Case
  int lpr = 0; //Multi-purpose integer
  int lpr2 = 0; //Multi-purpose integer

  struct winsize size;
  int widthRemaining = 0;
  
  char **fileNames;
  
  struct stat statbuf;
  
  int max = 0;
  int aMax = 0;

  long itotal = 0;
  
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
	return 7;
      }
      strcpy(fileNames[noOfFiles], argv[lpr]);
      noOfFiles++;
    }
    
    lpr++;
  }
  
  if(noOfFiles > 0) {
    max = 0;
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1) {
      fprintf(stderr, "ioctl has failed: %s\n", strerror(errno));
      return 3;
    }
    widthRemaining = size.ws_col;
    
    /* First for loop is to find any invalid filenames or directory names */
    for(lpr = 0; lpr < noOfFiles; lpr++) {
      if(stat(fileNames[lpr], &statbuf) != 0) {
	fprintf(stderr, "ls: cannot access %s: No such file or directory\n", fileNames[lpr]);
	free(fileNames[lpr]);
	 fileNames[lpr] = NULL;
      }
      else { 
        if(max < strlen(fileNames[lpr])) 
	  max = strlen(fileNames[lpr]);
        if(h == 1)
          itotal += ((long)statbuf.st_size);
        else if(k == 1)
          itotal += (((long)statbuf.st_size) / 1024);
        else
          itotal += (long)(statbuf.st_blocks);
      }
    }
    max += 2;    
    aMax = max;
    if(i == 1)
      aMax += 6;
    if(s == 1) {
      if(h == 1)
        aMax += 7;
      else if(k == 1)
        aMax += 5;
      else
        aMax += 3;
    }
    if(F == 1)
      aMax += 1;
    

 
   
    /* This for loop prints out files only */
    for(lpr = 0; lpr < noOfFiles; lpr++) {
      if(fileNames[lpr] == NULL)
        continue;
      
      if(stat(fileNames[lpr], &statbuf) != 0) {
	fprintf(stderr, "error in statbuf: %s\n", strerror(errno));
	return 9;
      }
      
      if(S_ISDIR(statbuf.st_mode) == 0) {
	//Print out files only
       
	if(aMax > widthRemaining) {
	   printf("\n");
	   widthRemaining = size.ws_col;
	 }
	 if(i == 1) {
	   printf("%i ", (int)statbuf.st_ino); 
	 }
	 if(s == 1) {
           if(h == 1)
	      printf("%ld B ", ((long)statbuf.st_size)); 
           else if(k == 1)
	      printf("%ld KB ", ((long)statbuf.st_size) / 1024); 
           else
	      printf("%ld ", (long)statbuf.st_blocks); 
	  }
	 printf("%s", fileNames[lpr]);
    
	 if(F == 1) {
	   if(S_ISLNK(statbuf.st_mode))
	     printf("@");
	   else if(S_ISSOCK(statbuf.st_mode))
	     printf("=");
	   else if(S_ISFIFO(statbuf.st_mode))
	     printf("|");
	   else if( ((statbuf.st_mode & S_IXUSR) || (statbuf.st_mode & S_IXGRP) || (statbuf.st_mode & S_IXOTH) ) )
	     printf("*");
	   else if(S_ISWHT(statbuf.st_mode))
	     printf("%c", '%');
	 }
	 for(lpr2 = 0; lpr2 < max - strlen(fileNames[lpr]); lpr2++)
	   printf(" ");
	 widthRemaining -= aMax;
	 
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
	if(d == 0) {
	  printf("\n%s:\n", fileNames[lpr]);
	  printOut(fileNames[lpr]);
	}
	else {
	  if(max > widthRemaining) {
	    printf("\n");
	    widthRemaining = size.ws_col;
	  }
	  
	  if(i == 1) {
	    printf("%i ", (int)statbuf.st_ino); 
	  }
	  if(s == 1) {
           if(h == 1)
	      printf("%ld B ", ((long)statbuf.st_size)); 
           else if(k == 1)
	      printf("%ld KB ", ((long)statbuf.st_size) / 1024); 
           else
	      printf("%ld ", (long)statbuf.st_blocks); 
	  }
	  printf("%s", fileNames[lpr]);
	  if(F == 1) {
	    printf("/");
	  }
	  printf("   ");
	  widthRemaining -= max;
	
	}
      }      
      free(fileNames[lpr]);
    }

    printf("\n");


  }
  else {
    printOut(".");
  }
  printf("\n");
  free(fileNames);
  return 0;
}

