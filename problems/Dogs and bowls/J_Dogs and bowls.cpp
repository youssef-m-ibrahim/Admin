#include <iostream>
#include <cmath>
using namespace std;

typedef struct
{
    int position;
    bool eat;
    bool wait;
}dog;


typedef struct
{
    int position;
    int time;
    bool eat;
}bowl;




int main()
{

    dog *dogs = new dog[200000];
    bowl *bowls = new bowl[200000];

    int n , m ; // n number of dogs , m number of bowls

  // getting the input
  cin >> n; cin >> m;
  for(int i =0 ; i < n ; i++)
  {
     cin >> dogs[i].position;
     dogs[i].eat = false;
     dogs[i].wait = false;
  }

  for(int i = 0 ; i < m ; i++)
  {
      cin >> bowls[i].position;
      cin >> bowls[i].time;
      bowls[i].eat = false;
  }

//sort the bowls with respect to time
for(int i = 0 ; i <  m ; i++)
    for(int j=0 ; j < m-1 ; j++)
     if(bowls[j].time>bowls[j+1].time)
     {
       bowl temp = bowls[j];
       bowls[j] = bowls[j+1];
       bowls[j+1] = temp;
    }




//Customize the wait flag
int available_bowls_for_dog;
for ( int i = 0 ; i < n ; i++)
{
available_bowls_for_dog =0;
for (int j = 0 ; j < m ; j++)
if( abs(dogs[i].position-bowls[j].position)<= bowls[j].time)
    available_bowls_for_dog++;

 // the next condition is to see if a dog can wait and eat later (have more than a bowl to eat)
 if(available_bowls_for_dog>1) dogs[i].wait= true;
}


//the operation finally here :D
int max_dogs = 0;

for(int i =0 ; i < m ; i++)
    for(int j = 0 ; j<n ; j++)
    {
    if(!dogs[j].eat && !dogs[j].wait && !bowls[i].eat &&
       abs(bowls[i].position - dogs[j].position <=bowls[i].time) )
     //if finally bowl is eaten
    {
    bowls[i].eat = true;
     dogs[j].eat = true;
     max_dogs ++;
    }

    }

// back to the not eaten and waited dogs
for(int i =0 ; i < m ; i++)
    for(int j = 0 ; j<n ; j++)
    {
  if(!dogs[j].eat && dogs[j].wait && !bowls[i].eat &&
       abs(bowls[i].position - dogs[j].position <=bowls[i].time) )
     //if finally bowl is eaten
    {
     bowls[i].eat = true;
     dogs[j].eat = true;
     max_dogs ++;
    }

    }


cout << max_dogs << endl;

delete [] dogs;
delete [] bowls;
return 0;
}
