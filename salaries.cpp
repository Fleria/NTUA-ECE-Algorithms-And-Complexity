/*g++ salaries.cpp -o salaries.exe*/  
#include <stdio.h>  
#include <iostream>  
  
#define NMAX 200000    
int m[NMAX+1];  
int n,k;  
  
using namespace std;  
  
int main() {  
    cin >> n; //reading  
    cin >> k;  
      
    int salary[n+1], LDS[n+1];  
    salary[0] = LDS[0] = 0;  
    m[0] = NMAX;                     
    for (int i = 1; i <= n; i++) {  
        m[i] = LDS[i] = 0;  
        cin >> salary[i];  
    }  
  
    int l;  
    m[1] = salary[n], LDS[n] = 1;  
    for (int i = n - 1; i > 0; i--) {  
        /*binary search*/  
        int lo=0, hi=n-i, sal=salary[i];  
        int mid = (lo + hi)/2, len = -1;    
        while (lo <= hi)  {    
            if (m[mid] >= 0 && sal < m[mid]) {    
            lo = mid + 1;    
            len = mid;    
            }    
            else    
                hi = mid - 1;     
          
            mid = (lo + hi)/2;    
        }    
        l = len + 1;  
        m[l] = max(m[l], salary[i]);  
        LDS[i] = l;  
    }  
    m[0] = 0;                                 
    for (int i = 1; i <= n; i++) m[i] = NMAX;  
    int max_length = 0;  
    for (int i = 1; i <= n; i++) {  
        /*binary search*/  
        int lo=0, hi=i, sal=salary[i]+k;  
        int mid = (lo + hi)/2, len = -1;    
        while (lo <= hi)  {    
            if (m[mid] >= 0 && sal > m[mid]) {    
            lo = mid + 1;    
            len = mid;    
            }    
            else    
                hi = mid - 1;     
          
            mid = (lo + hi)/2;    
        }    
        l = len + 1;
        max_length = max(max_length, l + LDS[i] - 1);  

        /*binary search*/  
        lo=0, hi=l, sal=salary[i];  
        mid = (lo + hi)/2, len = -1;    
        while (lo <= hi)  {    
            if (m[mid] >= 0 && sal > m[mid]) {    
            lo = mid + 1;    
            len = mid;    
            }    
            else    
                hi = mid - 1;     
          
            mid = (lo + hi)/2;    
        }    
        l = len + 1;
        m[l] = min(m[l], salary[i]) ;  
    }  
  
    cout << max_length << "\n"; 
}  