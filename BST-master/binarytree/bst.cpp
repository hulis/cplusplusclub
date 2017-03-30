#include <iostream>

struct LinearAllocator
{
    char* start;
    char* end;
    char* current;

    LinearAllocator(size_t bytes) :
        start((char*)malloc(bytes)),
        end(start + bytes),
        current(NULL)
    {
        current = start;
    }

    void* allocate(size_t bytes)
    {
        void* ptr = current;
        current += bytes;

        if (current >= end) return NULL;

        return ptr;
    }
};

const size_t Kilobyte = 1024;
const size_t Megabyte = 1024 * Kilobyte;

static LinearAllocator s_alloc(64u * Megabyte);

struct node_t
{
    int value;
    struct node_t* left; // pienempiä kuin value
    struct node_t* right; // isompia kuin value
};
// palauttaa true jos lisääminen onnistui
// false jos arvo on jo olemassa
bool binaryInsertRecursive(node_t* root, int value)
{
    // koska ei duplikaatteja BST:ssä
    if (root->value == value) return false;

    if (value < root->value)
    {
        // Meidän node on leaf, joten asetetaan arvo
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
            return binaryInsertRecursive(root->left, value);
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
    void* ptr = s_alloc.allocate(sizeof(node_t));
    if (ptr == NULL) return NULL;

    node_t* node = (node_t*)ptr;
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
    // ei koskaan päästä tänne
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

bool binaryExistsIterative(const node_t* root, int value)
{
    // iteratiivinen versio
    const node_t* current = root;
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
#include <assert.h>
int main()
{
    //node_t* recursive = createNode(100);
    node_t* iterative = createNode(100);
    int dataCount = 100000;
    std::vector<int> data(dataCount, 0);
    std::iota(data.begin(), data.end(), 0);

    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);

    LARGE_INTEGER recursiveStart, recursiveEnd, iterativeStart, iterativeEnd;
    QueryPerformanceCounter(&iterativeStart);

    for (int i : data)
    {
        binaryInsertIterative(iterative, i);
    }

    for (int i : data)
    {
        bool r = binaryExistsIterative(iterative, i);
        assert(r);
    }

    QueryPerformanceCounter(&iterativeEnd);

    LARGE_INTEGER iterativeElapsedUs;
    iterativeElapsedUs.QuadPart = iterativeEnd.QuadPart - iterativeStart.QuadPart;
    iterativeElapsedUs.QuadPart *= 1000 * 1000;
    iterativeElapsedUs.QuadPart /= frequency.QuadPart;

    std::cout << "Iterative binary insert took "
        << iterativeElapsedUs.QuadPart << " microseconds" << std::endl;

    return 0;
}