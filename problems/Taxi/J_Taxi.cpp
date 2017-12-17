#include <iostream>

using namespace std;

int main()
{

    int groups[100000];

    int n ; // number of groups
    int min_number = 0;
    int num_1 = 0 ;
    int num_2 = 0 ;
    int num_3 = 0 ;

    cin >> n ;

    for(int i = 0 ; i < n ; i++)
    {
        cin >> groups[i];

        if( groups[i] == 4)
            min_number ++;

        else if (groups[i] == 3)
            num_3 ++;

        else if (groups[i] == 2)
            num_2 ++;

        else if (groups[i] == 1)
            num_1 ++;

    }


// 2 + 2
min_number += num_2 / 2;
num_2 = num_2 % 2; // even or odd 0 > even , 1 > odd

 // 3 + 1 or 1 + 3
 if (num_3 < num_1)
 {
    min_number += num_3;
     num_1 -= num_3;
    num_3 = 0;

 }


else if (num_1 < num_3)
 {
    min_number += num_1;
    num_3 -= num_1;
    num_1 = 0;

 }


else if (num_1 == num_3)
 {
    min_number += num_1;
    num_1 = 0;
    num_3 = 0;
 }

// 1 + 1 + 1 + 1
min_number += num_1 / 4 ;
num_1 = num_1 % 4;

// 2 + 1 + 1
if(num_2 == 1 && (num_1 == 2 ))
{
            min_number++;
            num_1= 0;
            num_2= 0;
}


// 1 + 1 + 1
if(num_1 == 3 )
{
            min_number++;
            num_1= 0;
}



// 1 + 1
if(num_1 == 2 )
{
            min_number++;
            num_1= 0;
}

// 2 + 1
if(num_2 == 1 && (num_1 == 1 ))
{
            min_number++;
            num_1= 0;
            num_2= 0;
}



min_number+= num_1 + num_2 + num_3;

cout << min_number << endl;


    return 0;
}
