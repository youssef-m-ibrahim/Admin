#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

using namespace std;

class Node
{
	public:
	Node *child;
	char value;
	Node(char value)
	{
		this->value = value;
	}
	
};

class OperandNode
{
	public:
	OperandNode *child;
	float value;
	OperandNode(float value)
	{
		this->value = value;
	}
	
};

int get_operator_order(char cur)
{
	if(cur == '+' || cur == '-')return 1;
	if(cur == '*' || cur == '/')return 2;
	if(cur == '^')return 3;
	if(cur == '$')return 4;
	if(cur == '(')return 0;
	if(cur == ')')return 0;
};

bool is_higher_order_than(char cur, Node* node)
{
	if(node->value == '(' && cur == ')')return true;
	if(get_operator_order(cur) > get_operator_order(node->value))
	{
		return true;
	}
	return false;
};

template <class T>
class Stack
{
	public:
	T *top;
	Stack()
	{
		this->top = NULL;
	}
	void add(T *node)
	{
		node->child = this->top;
		this->top = node;
	}
	T* pop()
	{
		T * temp = this->top;
		this->top = this->top->child;
		return temp;
	}
	void print()
	{
		T *current = this->top;
		while(current != NULL)
		{
			cout<<current->value<<endl;
			current = current->child;
		}
	}
};

char* infix_to_reverse_polish(char *infix)
{
	char *temp = new char[800];
	Stack<Node>* temp_stack = new Stack<Node>();
	int j = 0;
	bool flag = true;
	for (int i = 0; infix[i] != '\0'; ++i)
	{
		if(infix[i] != ' ')
		{
			if(infix[i] == '[')
			{
				while(infix[i] != ']')
				{
					if(infix[i] != ' ')
					{
						temp[j] = infix[i];
						j++;
					}
					i++;
				}
			}
			if(infix[i] == '.' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^' || infix[i] == '+' || infix[i] == '-' || infix[i] == '(' || infix[i] == ')')
			{
				flag = false;
				if(temp_stack->top != NULL)
				{
					if((infix[i] == '(' || is_higher_order_than(infix[i], temp_stack->top))&& infix[i] != ')'){
						Node *x = new Node(infix[i]);
						if(infix[i] == '.')
						{
							x->value = '$';
							i++;
						}
						temp_stack->add(x);
					}else{
						Node *x = temp_stack->pop();
						if(x->value != '(')
						{
							temp[j] = x->value;
							j++;
							i--;
						}
						delete x;
					}
				}else{
					Node *x = new Node(infix[i]);
					temp_stack->add(x);
				}
			}else{
				if(!flag)
				{
					temp[j] = ';';
					j++;
				}
				temp[j] = infix[i];
				j++;
				flag = true;
			}
		}
	}
	while(temp_stack->top != NULL){
		Node *x = temp_stack->pop();
		temp[j] = x->value;
		j++;
	}

	return temp;
}

float reverse_polish_to_float(char *reverse_polish)
{
	Stack<OperandNode>* temp_stack = new Stack<OperandNode>();
	for (int i = 0; reverse_polish[i] != '\0'; ++i)
	{
		if(reverse_polish[i] == ';');
		else if(reverse_polish[i] == '[')
		{
			char *temp_string = new char[0];
			int j = 0;
			i++;
			while(reverse_polish[i] != ']')
			{
				if(reverse_polish[i] != ' ')
				{
					temp_string[j] = reverse_polish[i];
					j++;
				}
				i++;
			}
			OperandNode *tempNode = new OperandNode(atof(temp_string));
			temp_stack->add(tempNode);
			delete temp_string;
		}
		else if(reverse_polish[i] == '$')
		{
			OperandNode *left = temp_stack->pop();
			OperandNode *tempNode = new OperandNode(left->value * -1);
			temp_stack->add(tempNode);
			delete left;
		}
		else if(reverse_polish[i] == '*' || reverse_polish[i] == '/' || reverse_polish[i] == '^' || reverse_polish[i] == '+' || reverse_polish[i] == '-')
		{
			OperandNode *right = temp_stack->pop();
			OperandNode *left = temp_stack->pop();
			OperandNode *tempNode = NULL;
			switch(reverse_polish[i]){
				case '+':
					tempNode = new OperandNode(left->value + right->value);
					break;
				case '-':
					tempNode = new OperandNode(left->value - right->value);
					break;
				case '*':
					tempNode = new OperandNode(left->value * right->value);
					break;
				case '/':
					tempNode = new OperandNode(left->value / right->value);
					break;
				case '^':
					tempNode = new OperandNode(pow(left->value, right->value));
					break;
			}
			temp_stack->add(tempNode);
			delete right;
			delete left;
		}else{
			int temp = i;
			while(true)
			{
				i++;
				if(reverse_polish[i] != '\0')
				{
					if(reverse_polish[i] == ';' || reverse_polish[i] == '*' || reverse_polish[i] == '/' || reverse_polish[i] == '^' || reverse_polish[i] == '+' || reverse_polish[i] == '-' || reverse_polish[i] == '(' || reverse_polish[i] == ')' || reverse_polish[i] == '$' || reverse_polish[i] == '[')
					{
						i--;
						break;	
					}
				}else{
					break;
				}
			}
			OperandNode *tempNode = new OperandNode(atof(reverse_polish+temp));
			temp_stack->add(tempNode);
		}
	}
	return temp_stack->pop()->value;
}

int main()
{
	char infix[] = "2*([-255]+2)*5322321/126316./+321-2112361+([262]+323)"; //or "5+152*./263[255]"
	char *temp = infix_to_reverse_polish(infix);
	// for (int i = 0; temp[i] != '\0'; ++i)
	// {
	// 	cout<<endl<<temp[i]<<endl;
	// }
	//cout<<temp<<endl;
	cout<<reverse_polish_to_float(temp)<<endl;
}
