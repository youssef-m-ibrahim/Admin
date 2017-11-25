#include <iostream>
using namespace std;

class Node
{
public:
	Node *left, *right;
	int leftDist, rightDist;
	Node(int left, int right)
	{
		this->leftDist = left;
		this->rightDist = right;
	}
};

class spinner
{
	Node *cur;
public:
	spinner(int a,int b, int c)
	{
		Node *Rabbit = new Node(b,a);
		Node *Owl = new Node(a,c);
		Node *Eeyore = new Node(c,b);
		Rabbit->left = Eeyore;
		Rabbit->right = Owl;
		Eeyore->left = Owl;
		Eeyore->right = Rabbit;
		Owl->left = Rabbit;
		Owl->right = Eeyore;
		cur = Rabbit;
	}
	int spin()
	{
		int left = cur->leftDist;
		int right = cur->rightDist;
		if(left <= right)
		{
			cur = cur->left;
			return left;
		}else{
			cur = cur->right;
			return right;
		}
	}
};

int main()
{
	int numMeals;
	cin>>numMeals;
	int a,b,c;
	cin>>a;
	cin>>b;
	cin>>c;
	spinner route(a,b,c);
	int dist = 0;
	for (int i = 1; i < numMeals; i++)
	{
		dist += route.spin();
	}
	cout<<dist<<endl;
	return 1;
}
