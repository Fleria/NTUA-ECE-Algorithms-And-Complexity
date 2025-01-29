#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <bits/stdc++.h>

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

/*since solution has upper bound, perform binary search in spectrum of solutions*/
int main() {
  N = readLong();
  K = readLong();
  int array[N], maxmedian, minmedian, middle, best=-1, x=1, y=N+1, posneg[N];
  for (int i = 0; i < N; i++) {
    array[i] = readLong();
  }
	middle=(y+x)/2;
	while (x<=y){
		middle=(y+x)/2;
		for(int i=0; i<N; i++){ //array posneg[i]=1, -1
			if (array[i]>=middle) {posneg[i]=1;}
			else {posneg[i]=-1;}
			if (i>0) {
			posneg[i]+=posneg[i-1]; //prefix sum
		  }
		}
		maxmedian = posneg[K]; //max median for array of length K
		minmedian = 0; //min median
		for(int j=K; j<N; j++){ //for every array longer than K, calculate max, min median
			minmedian = min(minmedian, posneg[j-K]);
			maxmedian = max(maxmedian, posneg[j]-minmedian);
		}
		if(maxmedian>0){ //starting binary search
				best = middle;
				x = middle+1;
		}
		else{
				y = middle-1;
		}
	}
	cout<<best<<"\n";
}
