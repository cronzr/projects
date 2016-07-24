/*
An example of how we can split a file by parts. Next we can concat them using "cat" in Linux
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main () {
  char *s;                         // File name
  char *ss;                        // Generated file name
  char *buf[1];                    // Read/Write buffer
  struct stat *bf;                 // Struct to retreive a size of file
  int now;                         // Writed bytes
  int k;                           // File part num counter
  int err;                         // Error code when working with file
  int size;                        // File size
  int n;                           // Size of file part
  int numread, numwrite, cursize;  // Write/Read bytes
  int sour, dest;                  // File descriptors

  printf("Enter a file name to split: \n");
  scanf("%s",s);  
  sour=open(s,O_RDONLY);           // opening a file in readonly mode
  err=fstat(sour,bf);              // checking an error
  if (err==0) { 
    size=bf->st_size; 
    printf("Please set a part size: \n");
    scanf("%d",&n);
    if (n>1) {
      k=1; numwrite=0; cursize=0; numread=0; now=0;
      do {
        // creating a file
        sprintf(ss,"%d",k);  
        ss=strcat(ss,s); 
        dest=creat(ss,00700);
        do {
          numread=read(sour,buf,1);
          numwrite=write(dest,buf,1);
          cursize=cursize+numwrite; now=now+numwrite;
        }
        while ((n>now)&&(cursize<size));
      
        fsync(dest); 
        close(dest);  
        k=k+1;  
        now=0;
      }
      while ((cursize<size));
      close(sour); 
      return(1);
    } 
    else {
      printf("Size must be greater than zero!\n"); 
      exit(0);
    }
  } 
  else {
    printf("File does not exists!\n"); 
    exit(0);
  }
}
