#include <iostream>
#include <stdio.h>

using namespace std;
int N,K;

/* this is to read long ints */
#define BSIZE 1<<15
char buffer[BSIZE];
long bpos = 0L, bsize = 0L;
long readLong()
{
	long d = 0L, x = 0L;
	char c;
	while (1)
  {
		if (bpos >= bsize)
    {
			bpos = 0;
			if (feof(stdin)) return x;
			bsize = fread(buffer, 1, BSIZE, stdin);
		}
		c = buffer[bpos++];
		if (c >= '0' && c <= '9') { x = x*10 + (c-'0'); d = 1; }
		else if (d == 1) return x;
	}
	return -1;
}


int main()
{
  N = readLong();
  K = readLong();
  int array[N], sum=0, sums[K-1];
  int min=N+1;
  for (int i = 0; i < N; i++) {
    array[i] = readLong();
    if (array[i] == K) { //K residents in a building
      cout<<"1"<<"\n";
      return 0;
    }
  }
	sums[0]=0;
  for (int i=1; i<=K-1; i++){
    sums[i]=N+1; //define array of minimum length for specified (i) sum
  }
  for (int y=0; y<N; y++){
    sum=0;
    for (int i=y; i<N-1; i++){ //gia to deksi array, dynamic programming
      sum+=array[i];
      if(sum>=K) break;
      if(sums[sum]>i-y){
        sums[sum]=i-y; //length apo ton deikti y
      }
    }
    sum=0;
    for (int x=y-1; x>0; x--){ //gia to aristero array
      sum+=array[x];
      if(sum>=K) break;
      if (sums[K-sum]+y-x+1 < min && sums[K-sum]!=sums[sum]) { //y-x+1 to length pou prepei na prosthesoume
				min=sums[K-sum]+y-x+1;
			}
    }
  }
  if (min==N+1) {
		cout<<"-1"<<"\n";
		return 0;
	}
  cout<<min<<"\n";
  return 0;
}
