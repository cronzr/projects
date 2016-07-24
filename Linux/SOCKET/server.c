/*
  An example of client-server program using unix socket
  This is a server part
*/

#include <sys/types.h>;
#include <sys/socket.h>;
#include <sys/un.h>;

void main () {
  int a[9];
  int i,buf,k,v;
  struct sockaddr_un serv_addr, clnt_addr;
    int sockfd;
    int saddrlen, caddrlen, max_caddrlen, n;
    
  if ((sockfd=socket(AF_UNIX, SOCK_DGRAM, 0))<0){
    printf("Error in socket()"); exit(1);
  }
  unlink("./echo.server");
  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sun_family = AF_UNIX;
  strcpy(serv_addr.sun_path, "./echo.server");
  saddrlen = sizeof(serv_addr.sun_family)+ strlen(serv_addr.sun_path);
  
  if (bind(sockfd, (struct sockaddr *)&serv_addr, saddrlen)<0){
    printf("Error in bind()"); exit(1);
  }
  for( ; ; ){
    caddrlen = max_caddrlen;
    for (i=0;i<=9;i++){
      n = recvfrom(sockfd, &buf, 4, 0, (struct sockaddr *)&clnt_addr, &caddrlen);
      if (n < 0){ printf("Error in receiving a message\n"); exit(1); } 
      a[i]=buf;
    }
    /* processing  */
    i=0;
    do{
      k=i+1;
      do{
        if (a[i]>a[k]) {
          v=a[i]; a[i]=a[k]; a[k]=v;
        }
	      k++;
      }
      while(k<=9);
      i++;
    }
    while (i<9);
    
    for (i=0;i<=9;i++){
      if (sendto(sockfd, &a[i], n, 0, (struct sockaddr *)&clnt_addr, caddrlen)!=n){
        printf(" Ошибка передачи"); exit(1); 
      }
    }
    close(sockfd); unlink("./echo.server");
    exit(0);
  }
}  
