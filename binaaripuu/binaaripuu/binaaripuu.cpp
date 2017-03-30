#include <iostream>

struct node_t
{
	int value;
	struct node_t* left; // pienempiä kuin value
	struct node_t* right; // isompia kuin value
};

// palauttaa true jos lisääminen onnistuu
// false jos arvon on jo olemassa

bool binaryInsertRecursive(node_t* root, int value)
{
	//koska ei duplikaatteja BST:ssä
	if (root->value == value) return false;

	if (value < root->value)
	{
		//meidän node on leaf
		if (root->left == NULL)
		{
			node_t* leftNode = (node_t*)malloc(sizeof(node_t));
			leftNode->left = NULL;
			leftNode->right = NULL;
			leftNode->value = value;
			root->left = leftNode;
			return true;
		}
		else
		{
			binaryInsertRecursive(root->left, value);
		}
	}
	
	if (root->right == NULL)
		{
			node_t* rightNode = (node_t*)malloc(sizeof(node_t));
			rightNode->left = NULL;
			rightNode->right = NULL;
			rightNode->value = value;
			root->right = rightNode;
			return true;
		}
	return binaryInsertRecursive(root->right, value);
}

node_t* createNode(int x)
{
	node_t* node = (node_t*)malloc(sizeof(node_t));
	node->value = x;
	node->left = NULL;
	node->right = NULL;
	return node;

}

bool binaryInsertIterative(node_t* root, int value)
{
	node_t* current = root;

	for (;;)
	{
		if (current->value == value) return false;
		else if (value < current->value)
		{
			if (current->left == NULL)
			{
				current->left = createNode(value);
				return true;
			}
			current = current->left;
		}
		else
		{
			if (current->right == NULL)
			{
				current->right = createNode(value);
				return true;
			}
			current = current->right;
		}
	}
	return false;
}

bool binaryExistsRecursive(const node_t* root, int value)
{
	if (value == root->value) return true;
	else if (value < root->value && root->left != NULL)
		return binaryExistsRecursive(root->left, value);
	else if (value > root->value && root->right != NULL)
		return binaryExistsRecursive(root->right, value);

	return false;

}

// iteratiivinen versio
bool binaryExistsIterative(const node_t* root, int value)
{

	const node_t* current = root;
	//node_t* current = root;
	while (current != NULL)
	{
		if (value == current->value) return true;
		else if (value < current->value) current = current->left;
		else current = current->right;
	}
	return false;
}

#include <Windows.h>
#include <vector>
#include <numeric>

int main()
{
	node_t* recursive = createNode(100);
	node_t* iterative = createNode(100);

	int dataCount = 4000;
	std::vector<int> data(dataCount, 0);
	std::iota(data.begin(), data.end(), 0);

	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	LARGE_INTEGER recursiveStart, recursiveEnd, iterativeStart, iterativeEnd;
	QueryPerformanceCounter(&iterativeStart);

	for (int i : data)
	{
		binaryInsertIterative(iterative, i);
		//binaryInsertRecursive(iterative, i);
	}

	//testi

	QueryPerformanceCounter(&iterativeEnd);

	LARGE_INTEGER iterativeElapsedUs;
	iterativeElapsedUs.QuadPart = iterativeEnd.QuadPart - iterativeStart.QuadPart;
	iterativeElapsedUs.QuadPart *= 1000 * 1000;
	iterativeElapsedUs.QuadPart /= frequency.QuadPart;

	std::cout << "Iterative binary instert took " << iterativeElapsedUs.QuadPart << " microseconds" << std::endl;

	QueryPerformanceCounter(&recursiveStart);

	for (int i : data)
	{
		//binaryInsertIterative(iterative, i);
		binaryInsertRecursive(recursive, i);
	}

	QueryPerformanceCounter(&recursiveEnd);

	LARGE_INTEGER recursiveElapsedUs;
	recursiveElapsedUs.QuadPart = recursiveEnd.QuadPart - recursiveStart.QuadPart;
	recursiveElapsedUs.QuadPart *= 1000 * 1000;
	recursiveElapsedUs.QuadPart /= frequency.QuadPart;

	std::cout << "Recursive binary instert took " << recursiveElapsedUs.QuadPart << " microseconds" << std::endl;


	/*
	root.value = 10;
	root.left = NULL;
	root.right = NULL;
	
		   10
		   /
		  7
		 / \
		2   8
	binaryInsertIterative(&root, 7);
	binaryInsertIterative(&root, 2);
	binaryInsertIterative(&root, 8);

	for (int i = 11; i < 10000; i += 3)
	{
		binaryInsertRecursive(&root, i);
	}


	std::cout << binaryExistsIterative(&root, 7) << "\n";
	std::cout << binaryExistsIterative(&root, 2) << "\n";
	std::cout << binaryExistsIterative(&root, 5) << "\n";
	std::cout << binaryExistsIterative(&root, 8) << "\n";
	//std::cout << binaryExists(&root, 996) << "\n";
	*/
	return 0;
}