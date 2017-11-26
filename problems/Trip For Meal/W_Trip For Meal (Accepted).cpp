#include <bits/stdc++.h>

using namespace std;

int dist, nc=1, a, b, c, n;
char state = 'R';

int main()
{
    cin >> n >> a >> b >> c;
    while (nc < n)
    {
        switch (state)
        {
        case 'R':
            if(a<b)
            {
                state = 'O';
                dist += a;
            }
            else
            {
                state = 'E';
                dist += b;
            }
            break;
        case 'O':
            if(a<c)
            {
                state = 'R';
                dist += a;
            }
            else
            {
                state = 'E';
                dist += c;
            }
            break;
        case 'E':
            if(b<c)
            {
                state = 'R';
                dist += b;
            }
            else
            {
                state = 'O';
                dist += c;
            }
            break;
        }
        nc++;
    }
    cout << dist << endl;
    return 0;
}
