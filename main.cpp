#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

bool founded = false;

typedef struct link
{
	int id;
	int weight;
	link* left, * right;
} tree;

typedef struct stack
{
	int verth, weight;
	stack* next;
};

void push_st(stack*& top, int _verth, int _weight)
{
	stack* a = new stack;
	a->weight = _weight;
	a->verth = _verth;
	if (top == NULL)
	{
		a->next = NULL;
	}
	else
	{
		a->next = top;
	}
	top = a;
}

void del_st(stack*& top)
{
	if (top != NULL)
	{
		while (top->next != NULL)
		{
			stack* q = top->next;
			delete top;
			top = q;
		}
		delete top;
	}
}

void print_st(stack*& top)
{
	if (top != NULL)
	{
		while (top->next != NULL)
		{
			cout << top->verth << ' ';
			stack* q = top->next;
			delete top;
			top = q;
		}
		cout << top->verth << ' ';
		delete top;
	}
}

void push(link*& top, int D, int W)
{
	if (top == NULL)
	{
	link* a = new link;
	a->id = D;
	a->weight = W;
	a->left = NULL;
	a->right = NULL;
		top = a;
	}
	else if (D <= top->id)
	{
		push(top->left, D, W);
	}
	else
	{
			push(top->right, D, W);
	}
}

bool tree_empty(link*& top)
{
	if (top == NULL)
		return true;
	else
		return false;
}

link* found_right(link*& top)
{
if (top->right != NULL)
return found_right(top->right);
else
{
return top;
}
}

link* delete_id(link*& top, int D)
{
	if (top == NULL)
	{
		return top;
	}
	else if (D < top->id)
	{
		top->left = delete_id(top->left, D);
	}
	else if (D > top->id)
	{
		top->right = delete_id(top->right, D);
	}
	else
	{
		founded = true;
		if (top->left == NULL && top->right == NULL)
		{
			top = NULL;
		}
		else
		{
			if (top->left != NULL && top->right != NULL)
{ int c=found_right(top->left)->id;
int a=found_right(top->left)->weight;
top=delete_id(top, c);
top->id = c;
top->weight=a;
}
			}
		}

	return top;
}

void show_inorder(link*& top, int n)
{
	if (top->left != NULL)
	{
		show_inorder(top->left, n + 1);
	}
	cout << setw(n * 3) << top->id << '('<< top->weight <<")\n";
	if (top->right != NULL)
	{
		show_inorder(top->right, n + 1);
	}
}

void show_preorder(link*& top)
{
	cout << "Verth: " << top->id << ", weight:" << top->weight << '\n';
	if (top->left != NULL)
	{
		show_preorder(top->left);
	}
	if (top->right != NULL)
	{
		show_preorder(top->right);
	}
}

void show_postorder(link*& top)
{
	if (top->left != NULL)
	{
		show_postorder(top->left);
	}
	if (top->right != NULL)
	{
		show_postorder(top->right);
	}
	cout << "Verth: " << top->id << ", weight:" << top->weight << '\n';
}

int sum_stack(stack*& top)
{
	int S = 0;
	stack* i = top;
	while (i != NULL)
	{
		S += i->weight;
		i = i->next;
	}
	return S;
}

stack* max_way(link*& top)
{
	stack* stack_result = NULL;;

	if (top->left != NULL && top->right != NULL)
	{
		stack* stack_left = max_way(top->left);
		stack* stack_right = max_way(top->right);

		if (sum_stack(stack_left) > sum_stack(stack_right))
		{
			stack_result = stack_left;
			del_st(stack_right);
		}
		else
		{
			stack_result = stack_right;
			del_st(stack_left);
		}
		push_st(stack_result, top->id, top->weight);

	}
	else if (top->left == NULL && top->right == NULL)
	{
		push_st(stack_result, top->id, top->weight);

	}
	else if (top->left == NULL)
	{
		stack_result = max_way(top->right);
		push_st(stack_result, top->id, top->weight);

	}
	else
	{
		stack_result = max_way(top->left);
		push_st(stack_result, top->id, top->weight);

	}
	return stack_result;
}


void menu(int com, link*& top)
{
	switch (com)
	{
	case 1:
	{
		int D, W;
		cout << "Enter new id: ";
		cin >> D;
		cout << "Enter weight: ";
		cin >> W;
		push(top, D, W);
		break;
	}
	case 2:
	{
		cout << "Enter ";
		int D;
		cin >> D;
		link* buf = delete_id(top, D);
		if (!founded)
			cout << "Id not found\n";
		founded = false;
		break;
	}
	case 3:
	{
		if (!tree_empty(top))
		{
			cout << "Tree(inorder):\n";
			show_inorder(top, 0);
			cout << '\n';
		}
		else
		{
			cout << "Tree is empty\n";
		}
		break;
	}
	case 4:
	{
		if (!tree_empty(top))
		{
			cout << "Tree(preorder):\n";
			show_preorder(top);
			cout << '\n';
		}
		else
		{
			cout << "Tree is empty\n";
		}
		break;
	}
	case 5:
	{
		if (!tree_empty(top))
		{
			cout << "Tree(postorder):\n";
			show_postorder(top);
			cout << '\n';
		}
		else
		{
			cout << "Tree is empty\n";
		}
		break;
	}
	case 6:
	{
		if (!tree_empty(top))
		{
			stack* MW = max_way(top);
			//vector<pair<int, int>> MW = max_way(top);
			cout << "Max way: ";
			print_st(MW);
			/*for (int i = MW.size() - 1; i >= 0; i--)
			{
				cout << MW[i].first << ' ';
			}*/
			cout << endl;
		}
		else
		{
			cout << "Tree is empty\n";
		}
		break;
	}
	case 7:
	{
		break;
	}
	default:
	{
		cout << "Uknown command\n";
		break;
	}
	}
}

void print_menu()
{
	cout << "Menu:\n"
		<< "1. Push new id;\n"
		<< "2. Delete id;\n"
		<< "3. Show tree(inorder);\n"
		<< "4. Show tree(preorder);\n"
		<< "5. Show tree(postorder);\n"
		<< "6. Find max path;\n"
		<< "7. Exit.\n";
}

void create_nonempty_tree(link *&top)
{
	push(top, 10, 0);
	push(top, 3, 1);
	push(top, 1, 0);
	push(top, 4, -1);
	push(top, 6, -1);
	push(top, 21, 1);
	push(top, 19, 0);
	push(top, 15, 1);
}

int main()
{
	link* top = NULL;
	create_nonempty_tree(top);
	print_menu();
	int c = 0;
	while (c != 7)
	{
		cout << "Enter the command: ";
		cin >> c;
		menu(c, top);
	}
	return 0;
}
