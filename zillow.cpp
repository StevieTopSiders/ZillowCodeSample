// Zillow.cpp : Defines the entry point for the console application.
// Created by Stephen McMurtry, March 2015

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

long stringToLong(string s)
{
	long newLong = 0;
	int digits = 0;
	string parseString;
	bool negative = false; //True if negative.

	if (s.at(0) == '-')
	{
		negative = true;
	}

	for (int i = 0; i < s.length(); i++)
	{
		if (isdigit(s.at(i)))
		{
			parseString += s.at(i);
			digits++;
		}
	}

	for (int i = 0; i < parseString.length(); i++)
	{
		int thisNum = parseString.at(i) - 48; // Convert for ASCII position.
		int powerValue = digits - 1 - i;
		int thisDigit = (thisNum) * (pow(10, powerValue));
		newLong += thisDigit;
	}

	if (negative)
	{
		newLong *= -1;
	}

	return newLong;
}

void test()
{
	long i = stringToLong("111");

	cout << "Testing " << i << endl;

	if (i == 111)
	{
		cout << "Great job. I am successful." << endl;
	}
	else
	{
		cout << "Darn! I am a failure." << endl;
	}
}

// Trinary tree
struct node {
	int value;
	node* left;
	node* middle;
	node* right;
};

// Helper method creates a new node with a given value and sets child nodes to NULL
struct node * createNode(int nodeValue)
{
	node *head = new node;
	head->value = nodeValue;
	head->left = NULL;
	head->middle = NULL;
	head->right = NULL;

	return head;
}

// Does what it sounds like.
void insertNode(node* root, node* branch)
{
	if (branch->value < root->value)
	{
		if (root->left == NULL)
		{
			root->left = branch;
		}
		else
		{
			insertNode(root->left, branch);
		}
	}
	else if (branch->value == root->value)
	{
		if (root->middle == NULL)
		{
			root->middle = branch;
		}
		else
		{
			insertNode(root->middle, branch);
		}
	}
	else
	{
		if (root->right == NULL)
		{
			root->right = branch;
		}
		else
		{
			insertNode(root->right, branch);
		}
	}
	return;
}

// Creates a node and inserts it into the specified tree
void insert(node *tree, int value)
{
	if (tree->middle == NULL)
	{
		node * head = createNode(value);
		tree->middle = head;
	}
	else
	{
		node * branch = createNode(value);
		insertNode(tree->middle, branch);
	}
}

// Returns a pointer to a node with the smallest value.
struct node * minValue(node* tree)
{
	if (tree != NULL)
	{
		while (tree->left != NULL)
		{
			return minValue(tree->left);
		}
	}
	return tree;
	
}


struct node * deleteNode(node* tree, int value)
{
	if (tree != NULL)
	{
		if (value < tree->value)
		{
			tree->left = deleteNode(tree->left, value);
		}
		else if (value > tree->value)
		{
			tree->right = deleteNode(tree->right, value);
		}
		else
		{
			if (tree->middle != NULL)
			{
				tree->middle = deleteNode(tree->middle, value);
			}
			else if (tree->right != NULL)
			{
				int minimum = minValue(tree)->value;
				tree->value = minimum;
				tree->right = deleteNode(tree->right, value);
			}
			else
			{
				tree = tree->left;
			}
		}
	}
	return tree;
	
}

void deletion(node* tree, int value)
{
	tree = deleteNode(tree, value);
}

// Prints a traversal of the tree.
void print(node* root)
{
	if (root != NULL)
	{
		cout << "Node: " << root->value << endl;
		print(root->left);
		print(root->middle);
		print(root->right);
	}
	else
	{
		return;
	}
}

int main()
{
	node *tree = new struct node;
	tree->middle = NULL;
	insert(tree, 5);
	insert(tree, 4);
	insert(tree, 9);
	insert(tree, 5);
	insert(tree, 7);
	insert(tree, 2);
	insert(tree, 2);
	print(tree->middle);

	cout << "About to delete a 5." << endl;

	deletion(tree->middle, 5);
	print(tree->middle);

	cout << "About to delete a 7." << endl;

	deletion(tree->middle, 7);
	print(tree->middle);

	cout << "About to delete a 9." << endl;

	deletion(tree->middle, 9);
	print(tree->middle);

	test();

	system("pause");
	return 0;
}
