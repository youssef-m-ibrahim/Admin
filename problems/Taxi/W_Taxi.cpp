#include <iostream>

using namespace std;

int main()
{
    int g,n,_1=0,_2=0,_3=0,_4=0,c=0;
    cin>>g;
    for (int i = 0 ;i < g ;i++)
    {
        cin>>n;
        switch (n)
        {
        case 1 :
            _1 ++;
            break;
        case 2 :
            _2 ++;
            break;
        case 3 :
            _3 ++;
            break;
        case 4 :
            _4 ++;
            break;

        }
    }

    c += _4;
    c += _3;
    if (_1 > _3)
        _1 -= _3;
    else
        _1 = 0;

    c += _2/2;
    if (_2 % 2 == 0)
        _2 = 0;
    else
        _2 = 1;
    if ((((2*_2)+_1) % 4) == 0)
        c += ((2*_2+_1))/4;
    else
        c += ((2*_2+_1))/4 + 1;
    cout<<c<<endl;

        return 0;
}
















