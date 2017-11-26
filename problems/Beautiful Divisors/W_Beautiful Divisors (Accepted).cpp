#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int t = 32640;
    for(int i = 14; i >= 0 ; i -= 2)
    {
        if((n % t) == 0)
        {
            cout << t <<endl;
            return 0;
        }
        else
        {
            t &= ~(1<<i);
            t >>= 1;
        }
    }
    return 0;
}
