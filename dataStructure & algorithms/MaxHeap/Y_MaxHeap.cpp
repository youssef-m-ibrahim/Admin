#include <iostream>
using namespace std;
void max_heapify(int *a, int i, int n)
{
	int j = i*2;
    if(j <= n)
    {
    	int left = a[j-1];
    	if((j+1)<=n){
	    	int right = a[j];
	    	if(right > left)
	    	{
	    		if(right > a[i-1])
	    		{
	    			int temp = a[i-1];
	    			a[i-1] = right;
	    			a[j] = temp;
	    			max_heapify(a,j+1,n);
	    		}
	    	}else{
	    		if(left > a[i-1])
	    		{
	    			int temp = a[i-1];
	    			a[i-1] = left;
	    			a[j-1] = temp;
	    			max_heapify(a,j,n);
	    		}
	    	}
	    }else{
	    	if(left > a[i-1])
	    	{
	    		int temp = a[i-1];
	    		a[i-1] = left;
	    		a[j-1] = temp;
	    		max_heapify(a,j,n);
	    	}
	    }
    }
    
}
void build_maxheap(int *a,int n)
{
    for(int i = n/2;i>=1;i--){
    	max_heapify(a,i,n);
    }
}
int main()
{
    int n, i, x;
    cout<<"enter no of elements of array\n";
    cin>>n;
    int a[20];
    for (i = 0; i < n; i++)
    {
        cout<<"enter element"<<(i+1)<<endl;
        cin>>a[i];
    }
    build_maxheap(a,n);
    cout<<"Max Heap\n";
    for (i = 0; i < n; i++)
    {
        cout<<a[i]<<endl;
    }
}
