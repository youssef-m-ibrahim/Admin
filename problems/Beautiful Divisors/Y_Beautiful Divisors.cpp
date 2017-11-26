#include <iostream>

int beautifulNumber(int k)
{
	int x = 1;
	for (int i = 1; i < k; i++)
	{
		x = x*2;
	}
	x = ((x*2)-1)*x;
	return x;
}


using namespace std;
int main()
{
	int k, x;
	cin>>x;
	int count = 1;
	int temp = x;
	while (temp/2 != 0)
	{
		temp = temp/2;
		count++;
	}
	do{
		temp = beautifulNumber(count);
		count--;
	}while(temp > x);
	cout<<temp<<endl;
	return 1;
}