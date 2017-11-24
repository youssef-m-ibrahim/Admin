#include <iostream>
using namespace std;


struct Node
{
	Node *parent, *left, *right;
	int height, value;
};

class AVL
{

	public:
	Node *root;

	AVL(){
		this->root = NULL;
	};

	Node* left_rotate(Node *node_x)
	{
		Node *node_y, *temp;
		node_y = node_x->right;
		node_y->parent = node_x->parent;
		node_x->parent = node_y;
		temp = node_y->left;
		node_y->left = node_x;
		node_x->right = temp;
		if(temp != NULL){
			temp->parent = node_x;
		}
		if(node_y->parent != NULL)
		{
			if(node_y->parent->left == node_x){
				node_y->parent->left = node_y;
			}else{
				node_y->parent->right = node_y;
			}
		}else{
			this->root = node_y;
		}
		node_x->height = this->height(node_x);
		node_y->height = this->height(node_y);
		return node_x;
	};

	Node* right_rotate(Node *node_y)
	{
		Node *node_x, *temp;
		node_x = node_y->left;
		node_x->parent = node_y->parent;
		node_y->parent = node_x;
		temp = node_x->right;
		node_x->right = node_y;
		node_y->left = temp;
		if(temp != NULL){
			temp->parent = node_y;
		}
		if(node_x->parent != NULL)
		{
			if(node_x->parent->left == node_y){
				node_x->parent->left = node_x;
			}else{
				node_x->parent->right = node_x;
			}
		}else{
			this->root = node_x;
		}
		node_y->height = this->height(node_y);
		node_x->height = this->height(node_x);
		return node_y;
	};

	bool check_balance(Node *node)
	{
		if(node == NULL)return true;
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
		if(leftHeight >= rightHeigh)
		{
			return (leftHeight-rightHeigh > 1) ? false : true;
		}else{
			return (rightHeigh-leftHeight > 1) ? false : true;
		}
	};

	void update_heights(Node *node)
	{
		if(node == NULL)return;
		node->height = this->height(node);
		this->update_heights(node->parent);
	}

	int height(Node *node)
	{
		if(node == NULL)return -1;
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
		Node *current = this->root;
		if(this->root != NULL)
		{
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
		current = node;
		bool is_next_left = true /* left*/, is_prev_left = true /*left*/;
		while(current->parent != NULL)
		{
			if(current->parent->left == current)
			{
				is_prev_left = is_next_left;
				is_next_left = true;
			}else
			{
				is_prev_left = is_next_left;
				is_next_left = false;
			}
			bool flag = false;
			if(!this->check_balance(current->parent))
			{
				/* case 0 : left left*/
				if(is_prev_left && is_next_left)
				{
					current = this->right_rotate(current->parent);
					flag = true;
					current = current->parent;
				}
				/* case 1 : left right*/
				if(!is_prev_left && is_next_left)
				{
					current = this->left_rotate(current);
					current = current->parent;
					current = this->right_rotate(current->parent);
					current = current->parent;
					flag = true;	
				}
				/* case 2 : right right*/
				if(!is_prev_left && !is_next_left)
				{
					current = this->left_rotate(current->parent);
					flag = true;
					current = current->parent;
				}
				/* case 3 : right left*/
				if(is_prev_left && !is_next_left)
				{
					current = this->right_rotate(current);
					current = current->parent;
					current = this->left_rotate(current->parent);
					current = current->parent;
					flag = true;
				}
			}
			if(flag)
			{
				this->update_heights(current);
			}else{
				current = current->parent;
			}
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
			cout<<current->value<<" at "<<current->height<<endl;
			current = this->next_max(current);
		}
	}

};


int main()
{
	AVL tree;
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
