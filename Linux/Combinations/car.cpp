/*
Calculate the number of combinations, permutations, placements on the given m and n. 
And if the number of combinations of < number of permutations, then count the number of zeros and units in the results.
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// computing factorial 
int fact (int k)
{ int i;  int l;
  l=1; i=1; for (i;i<=k;i++) l=l*i; return(l);
}

// number of digits in value
int length (int z)
{ int x,L;
  x=1; L=0;
  do { x=(x*10); L=(L+1); } while ((z/x)>0.1);
  return(L);
}

void main(int K, char *arg[]) { 
  int C,A,R,m,n,i,k,zero,one,allisok,again;
  allisok=0; 
  again=0;
  // if there is no parameters then ...
  if (K==1) { 
    printf("\nPlease enter value for m: "); 
    scanf("%d",&m);
    printf("\nPlease enter value for n: "); 
    scanf("%d",&n);
    allisok=1;
  }
  else
    if (K==2) {
      printf("Not all parameters were set");
      allisok=0;
    }
    else { 
      m=atoi(arg[1]); 
      n=atoi(arg[2]);
      allisok=1;
      again=1;
    }
    
    if (allisok==1) { 
      if (m>7) {
        printf("Error, (m) can not be greater than 7");
      }
      else { 
        if (n>7) 
          printf("Error, (n) can not be greater than 7");
      }
    }  
    else { 
      if (again==1) { 
        printf("\nEnter value for (m): %d",m); 
        printf("\nEnter value for (n): %d",n);
      }
    
      C=fact(m)/fact(n)*fact(m-n);
      A=fact(m)/fact(m-n);
      R=fact(n);
      printf("\nC=%d",C);
      printf("\nA=%d",A);
      printf("\nR=%d",R);
      if (C<A) { 
        char chC[5];
        char chA[5];
        char chR[5];
        itoa(C,chC,10);
        itoa(A,chA,10);
        itoa(R,chR,10);
        zero=0; one=0;
        i=0; 
        for (i; i<length(C); i++) { 
          if (chC[i]=='0') 
            zero=zero+1;
          else 
            if (chC[i]=='1') 
              one=one+1;
        }
        printf("\nNumber of zeros for C = %d", zero);
        printf("\nNumber of units for C = %d", one);
        zero=0; one=0;
        i=0; 
        for (i;i<length(A);i++) { 
          if (chA[i]=='0') 
            zero=zero+1;
          else 
            if (chA[i]=='1') 
              one=one+1;
        }
        printf("\nNumber of zeros for A = %d", zero);
        printf("\nNumber units for A = %d",one);
        zero=0; one=0;
        i=0; 
    
        for (i; i<length(R); i++) { 
          if (chR[i]=='0') 
            zero=zero+1;
          else 
            if (chR[i]=='1') one=one+1;
        }
        printf("\nNumber of zeros for R = %d", zero);
        printf("\nNumber of units for R = %d",one);
      }
    }
  }
  return(0);
}
