// Leaf and Non-Leaf Node Counting in a General Tree
// Features:
//   1. Construct a general tree (any number of children per node)
//   2. Display the tree structure
//   3. Count + display leaf nodes and non-leaf nodes (with actual values)
//   4. Count nodes at each level
//   5. Query the children of a selected node
//
// Node representation: first child + next sibling (structures only, no classes)

#include <iostream>
using namespace std;

#define MAX 100

struct Node
{
    int data;
    Node* firstChild;
    Node* nextSibling;
};

Node* root = NULL;
int totalNodes = 0;

int leaves[MAX], nonLeaves[MAX];
int leafCount = 0, nonLeafCount = 0;

// Create a new node
Node* newNode(int value)
{
    Node* n = new Node;

    n->data = value;
    n->firstChild = NULL;
    n->nextSibling = NULL;

    return n;
}

// Find a node by value
Node* findNode(Node* cur, int key)
{
    if (cur == NULL)
    {
        return NULL;
    }

    if (cur->data == key)
    {
        return cur;
    }

    Node* result = findNode(cur->firstChild, key);

    if (result != NULL)
    {
        return result;
    }

    return findNode(cur->nextSibling, key);
}

// Create root
void createRoot()
{
    if (root != NULL)
    {
        cout << "\nRoot already exists!";
        return;
    }

    int value;

    cout << "\nEnter root value: ";
    cin >> value;

    root = newNode(value);
    totalNodes++;

    cout << "\nRoot created successfully!";
}

// Add child to a node
void addChild(int parentValue, int childValue)
{
    Node* parent = findNode(root, parentValue);

    if (parent == NULL)
    {
        cout << "\nParent " << parentValue << " not found!";
        return;
    }

    if (findNode(root, childValue) != NULL)
    {
        cout << "\nValue " << childValue << " already exists (values must be unique)!";
        return;
    }

    if (totalNodes == MAX)
    {
        cout << "\nTree is full!";
        return;
    }

    Node* child = newNode(childValue);

    // Insert as last child of the parent
    if (parent->firstChild == NULL)
    {
        parent->firstChild = child;
    }
    else
    {
        Node* temp = parent->firstChild;

        while (temp->nextSibling != NULL)
        {
            temp = temp->nextSibling;
        }

        temp->nextSibling = child;
    }

    totalNodes++;

    cout << "\nChild " << childValue << " added under " << parentValue << ".";
}

// Read parent and child, then add
void addChildMenu()
{
    if (root == NULL)
    {
        cout << "\nCreate the root first!";
        return;
    }

    int parentValue, childValue;

    cout << "\nEnter parent value: ";
    cin >> parentValue;

    cout << "Enter child value: ";
    cin >> childValue;

    addChild(parentValue, childValue);
}

// Print tree with indentation
void printTree(Node* cur, int depth)
{
    if (cur == NULL)
    {
        return;
    }

    for (int i = 0; i < depth; i++)
    {
        cout << "    ";
    }

    if (depth > 0)
    {
        cout << "|-- ";
    }

    cout << cur->data;

    if (cur->firstChild == NULL)
    {
        cout << "  (leaf)";
    }

    cout << endl;

    Node* child = cur->firstChild;

    while (child != NULL)
    {
        printTree(child, depth + 1);
        child = child->nextSibling;
    }
}

// Display tree
void displayTree()
{
    if (root == NULL)
    {
        cout << "\nTree is empty!";
        return;
    }

    cout << "\n----- Tree Structure -----\n";

    printTree(root, 0);
}

// Collect leaf and non-leaf values (preorder)
void collect(Node* cur)
{
    if (cur == NULL)
    {
        return;
    }

    if (cur->firstChild == NULL)
    {
        leaves[leafCount++] = cur->data;
    }
    else
    {
        nonLeaves[nonLeafCount++] = cur->data;
    }

    Node* child = cur->firstChild;

    while (child != NULL)
    {
        collect(child);
        child = child->nextSibling;
    }
}

// Display leaf and non-leaf nodes with count
void showLeafNonLeaf()
{
    if (root == NULL)
    {
        cout << "\nTree is empty!";
        return;
    }

    leafCount = 0;
    nonLeafCount = 0;

    collect(root);

    cout << "\nLeaf nodes (" << leafCount << "): ";

    for (int i = 0; i < leafCount; i++)
    {
        cout << leaves[i] << " ";
    }

    cout << "\nNon-leaf nodes (" << nonLeafCount << "): ";

    for (int i = 0; i < nonLeafCount; i++)
    {
        cout << nonLeaves[i] << " ";
    }

    cout << "\nTotal nodes: " << leafCount + nonLeafCount;
}

// Count nodes at each level (level order traversal using a queue array)
void levelCounts()
{
    if (root == NULL)
    {
        cout << "\nTree is empty!";
        return;
    }

    Node* queue[MAX];
    int front = 0, rear = 0;
    int level = 0;

    queue[rear++] = root;

    cout << "\n----- Nodes at Each Level -----\n";

    while (front < rear)
    {
        int size = rear - front;

        cout << "Level " << level << " : " << size << " node(s) -> ";

        for (int i = 0; i < size; i++)
        {
            Node* cur = queue[front++];

            cout << cur->data << " ";

            Node* child = cur->firstChild;

            while (child != NULL)
            {
                queue[rear++] = child;
                child = child->nextSibling;
            }
        }

        cout << endl;
        level++;
    }

    cout << "Height of tree (levels): " << level;
}

// Query the children of a selected node
void queryChildren()
{
    if (root == NULL)
    {
        cout << "\nTree is empty!";
        return;
    }

    int value;

    cout << "\nEnter node value to query: ";
    cin >> value;

    Node* n = findNode(root, value);

    if (n == NULL)
    {
        cout << "Node " << value << " not found in the tree.";
        return;
    }

    if (n->firstChild == NULL)
    {
        cout << "Node " << value << " is a LEAF node. It has no children.";
        return;
    }

    int count = 0;
    Node* child = n->firstChild;

    while (child != NULL)
    {
        count++;
        child = child->nextSibling;
    }

    cout << "Node " << value << " is a NON-LEAF node with "
         << count << " child(ren): ";

    child = n->firstChild;

    while (child != NULL)
    {
        cout << child->data << " ";
        child = child->nextSibling;
    }
}

// Load a sample tree
void loadSample()
{
    if (root != NULL)
    {
        cout << "\nTree already exists. Cannot load sample.";
        return;
    }

    root = newNode(1);
    totalNodes = 1;

    addChild(1, 2);  addChild(1, 3);  addChild(1, 4);
    addChild(2, 5);  addChild(2, 6);
    addChild(3, 7);
    addChild(4, 8);  addChild(4, 9);  addChild(4, 10);
    addChild(6, 11); addChild(6, 12);

    cout << "\nSample tree loaded.";
}

// Free all nodes
void freeTree(Node* cur)
{
    if (cur == NULL)
    {
        return;
    }

    freeTree(cur->firstChild);
    freeTree(cur->nextSibling);

    delete cur;
}

// Main function
int main()
{
    int choice;

    do
    {
        cout << "\n\n========== GENERAL TREE MENU ==========";
        cout << "\n1. Create root";
        cout << "\n2. Add child to a node";
        cout << "\n3. Display tree";
        cout << "\n4. Display leaf and non-leaf nodes (with count)";
        cout << "\n5. Count nodes at each level";
        cout << "\n6. Query children of a node";
        cout << "\n7. Load sample tree";
        cout << "\n8. Exit";
        cout << "\n=======================================";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                createRoot();
                break;

            case 2:
                addChildMenu();
                break;

            case 3:
                displayTree();
                break;

            case 4:
                showLeafNonLeaf();
                break;

            case 5:
                levelCounts();
                break;

            case 6:
                queryChildren();
                break;

            case 7:
                loadSample();
                break;

            case 8:
                cout << "\nExiting program.";
                break;

            default:
                cout << "\nInvalid choice!";
        }

    } while (choice != 8);

    freeTree(root);

    return 0;
}
