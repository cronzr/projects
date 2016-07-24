/* 
  An example of how to use pipes and fork a process
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
  int p[2],a[9],i,k,v,pid;
  /* fill vector with valules */
  for (i=0; i<=9; i++){
    printf("Enter value for a[%d]\n",i);
    scanf("%d",&a[i]);
  }
  /* open pipe */
  if (pipe(p)==-1){
    perror("Error in pipe()");
    exit(1);
  }
  else {
    for (i=0;i<=9;i++) {   // write the vector to pipe
      write(p[1],&a[i],4);
    }
    pid=fork();       // creating child process
    switch(pid) {
      case -1:
        perror("Error in fork()");
        exit(0);
      case 0:         // child process performs processing 
        for (i=0;i<=9;i++){
          read(p[0],&a[i],4);
        }
        i=0;  
        do {
          k=i+1;
          do {
	          if (a[i]>a[k]) {
	            v=a[i]; a[i]=a[k]; a[k]=v; 
	          }
            k++;
          }
          while (k<=9);
	        i++;
        }
        while (i<=9);
      
        for (i=0;i<=9;i++){
          write(p[1],&a[i],4);
        }
        exit(0);

      default:        // Parent process is reading the result from pipe and prints the results
        wait(&pid);   
        for (i=0;i<=9;i++){
          read(p[0],&a[i],4);
          printf("--> %d\n",a[i]);
        }
        exit(0);  
    }
  }
}
