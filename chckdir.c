#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>



void printFiles(const char *a){
  DIR *p = opendir(a);
  struct dirent *x;
  x = readdir(p);
  while(x != NULL){
    if ( (int)(*x).d_type == 8){
      printf("File: %s  ", x->d_name);
      printf("Type: %i \n", x->d_type);
    }
    x = readdir(p);   
  }
  closedir(p);
}

void listDirs(const char *a){
  DIR *p = opendir(a);
  struct dirent *x;
  x = readdir(p);
  while(x != NULL){
    if ( (int)(*x).d_type == 4){
	printf("Name of Directory: %s \n", (*x).d_name);
      }
    x = readdir(p);
  }
  closedir(p);
}

void readSize(long size){
  if (size>1000){
    printf("The size of the directory is: %li KB\n", size/1000);
  }
  else if(size>1000000){
    printf("The size of the directory is: %li MB\n", size/1000000);
  }
  else if(size>1000000000){
    printf("The size of the directory is: %li GB\n", size/1000000000);
  }
  else{
    printf("The size of the directory is: %li B\n", size);
  }
}



long sizeofDir(const char *a){
  long total = 0;
  
  DIR *p = opendir(a);
  
  struct dirent *x;
  
  x = readdir(p);
  
  struct stat fileinfo;
  
  while(x != NULL){
    
    if((int)x->d_type == 8){
      stat(x->d_name, &fileinfo);
      total += fileinfo.st_size;
      
    }
    
    x = readdir(p);
    
  }
  closedir(p);
  return total;
}


void main(){
  const char* path = ".";
  printf("+++++++++++++++TESTING CODE++++++++++++++++++\n\n");
  printf("Scanning current directory\n\n");
  printf("\nDirectories: \n");
  listDirs(path);
  printf("\nFiles: \n");
  printFiles(path);
  printf("\n\nSize of the directory in bytes: %li bytes\n", sizeofDir(path));
  readSize(sizeofDir(path));
  printf("\n\n");
 printf("++++++++++++++DONE TESTING CODE++++++++++++++++++\n\n");


}
