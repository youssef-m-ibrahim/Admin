#include <iostream>
using namespace std;


struct Node
{
	Node *parent, *left, *right;
	int height, value;
};

class BST
{
	Node *root;

	public:

	BST(){
		this->root = NULL;
	};

	int height(Node *node)
	{
		int leftHeight, rightHeigh;
		if(node->right != NULL)
		{
			rightHeigh = node->right->height;
		}else{
			rightHeigh = -1;
		}
		if(node->left != NULL)
		{
			leftHeight = node->left->height;
		}else{
			leftHeight = -1;
		}
		return (leftHeight >= rightHeigh) ? leftHeight+1 : rightHeigh+1;
	};

	void insert(int value)
	{
		Node *node = new Node;
		node->value = value;
		node->parent = NULL;
		node->left = NULL;
		node->right = NULL;
		if(this->root != NULL)
		{
			Node *current = this->root;
			while(true){
				if(node->value <= current->value)
				{
					if(current->left != NULL){
						current = current->left;
					}else{
						current->left = node;
						node->parent = current;
						break;
					}
				}else{
					if(current->right != NULL){
						current = current->right;
					}else{
						current->right = node;
						node->parent = current;
						break;
					}
				}
			}
			current = node;
			while(current->parent != NULL){
				current = current->parent;
				current->height = this->height(current);
			}
		}else{
			this->root = node;
			node->height = 0;
		}
	};

	Node* min(Node *node)
	{
		Node *current = node;
		bool flag = true;
		while(current->left != NULL){
			current = current->left;
			flag = false;
		}
		return flag ? node : current;
	};

	Node* max(Node *node)
	{
		Node *current = node;
		bool flag = true;
		while(current->right != NULL){
			current = current->right;
			flag = false;
		}
		return flag ? node : current;
	};

	Node* next_max(Node *node)
	{
		if(node->right != NULL)
		{
			return this->min(node->right);
		}if(this->root == node){
			return NULL;
		}
		else if(node->parent->left == node){
			return node->parent;
		}else{
			Node *current = node;
			while(current->parent != NULL && current->parent->right == current){
				current = current->parent;
			}
			if(current->parent != NULL){
				return current->parent;
			}
			return NULL;
		}
	};

	void print()
	{
		Node *current = this->min(this->root);
		while(current != NULL){
			cout<<current->value<<endl;
			current = this->next_max(current);
		}
	}

};


int main()
{
	BST tree;
	int n;
	cin>>n;
	for (int i = 0; i < n; ++i)
	{
		int value;
		cin>>value;
		tree.insert(value);
	}
	cout<<"----------"<<endl;
	tree.print();
}
