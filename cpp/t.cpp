#include <iostream>
using namespace std
int main()  
{  
  const int n=9;  
    int i,f,sign=1;    f=0;     
	  for(i=1;i<=n;i++)  
	    {                
		    f=f+sign*i;  
			    sign=-sign;   }  
				  cout<<f<<endl;  
				  }  
