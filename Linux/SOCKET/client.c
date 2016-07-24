/*
  An example of client-server program using unix socket
  This is a client part
*/

#include <sys/types.h>;
#include <sys/socket.h>;
#include <sys/un.h>;
#include <string.h>

int buf;
void main (){ 
  int i;
  int a[9];
  struct sockaddr_un serv_addr, clnt_addr;
    int sockfd;
    int saddrlen, caddrlen, msglen, n;

  for(i=0;i<=9;i++){
    printf("Enter value for a[%d]\n",i); scanf("%d",&a[i]);
  }

  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sun_family = AF_UNIX;
  strcpy(serv_addr.sun_path, "./echo.server");
  saddrlen = sizeof(serv_addr.sun_family)+ strlen(serv_addr.sun_path);    
  
  if ((sockfd=socket(AF_UNIX, SOCK_DGRAM, 0))<0){
    printf("Error in socket()"); exit(1);
  }

  bzero(&clnt_addr, sizeof(clnt_addr));
  clnt_addr.sun_family = AF_UNIX;
  strcpy(clnt_addr.sun_path, "./tmp/clnt.XXXX");
  mktemp(clnt_addr.sun_path);
  caddrlen = sizeof(clnt_addr.sun_family)+ strlen(clnt_addr.sun_path);    
  
  if (bind(sockfd, (struct sockaddr *)&clnt_addr, caddrlen)<0){
    printf("Error in bind()"); exit(1);
  }
  //  msglen = strlen(msg);
  for (i=0;i<=9;i++){
    if (sendto(sockfd, &a[i], 4, 0, (struct sockaddr *)&serv_addr, saddrlen)!=4){
      printf("Error in transferring a message\n"); exit(1);
    }
  }
  for (i=0;i<=9;i++){
    if ((n=recvfrom(sockfd, &buf, 4, 0, NULL, 0))<0){
      printf("Error in receiving a message\n"); exit(1);
    }
    a[i]=buf; printf("-> %d\n",a[i]);
  }
  close (sockfd);
  unlink(clnt_addr.sun_path);
  exit(0);
}  
