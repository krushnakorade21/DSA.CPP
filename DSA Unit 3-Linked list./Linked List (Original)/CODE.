#include <iostream>
#include <string>
using namespace std;

#define MAX 10

// Doubly linked list node (contact records)
struct Contact
{
    int contactID;
    string name;
    string phone;

    Contact* prev;
    Contact* next;
};

// Binary search tree node (sorted by name)
struct TreeNode
{
    int contactID;
    string name;

    TreeNode* left;
    TreeNode* right;
};

// Queue node (call log)
struct CallNode
{
    string name;

    CallNode* next;
};

Contact* head = NULL;
TreeNode* root = NULL;
CallNode* front = NULL;
CallNode* rear = NULL;

// Graph (adjacency matrix): contact ID 1 uses index 0
int graph[MAX][MAX] = {0};

// Find contact by ID
Contact* findContact(int id)
{
    Contact* temp = head;

    while (temp != NULL)
    {
        if (temp->contactID == id)
        {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}

// Insert into BST
TreeNode* insertTree(TreeNode* node, int id, string name)
{
    if (node == NULL)
    {
        node = new TreeNode;

        node->contactID = id;
        node->name = name;
        node->left = NULL;
        node->right = NULL;

        return node;
    }

    if (name < node->name)
    {
        node->left = insertTree(node->left, id, name);
    }
    else
    {
        node->right = insertTree(node->right, id, name);
    }

    return node;
}

// Search in BST
TreeNode* searchTree(TreeNode* node, string name)
{
    if (node == NULL || node->name == name)
    {
        return node;
    }

    if (name < node->name)
    {
        return searchTree(node->left, name);
    }

    return searchTree(node->right, name);
}

// Inorder traversal (alphabetical order)
void inorder(TreeNode* node)
{
    if (node == NULL)
    {
        return;
    }

    inorder(node->left);

    cout << "\nContact ID : " << node->contactID;
    cout << "\nName       : " << node->name;
    cout << "\n-------------------------------------";

    inorder(node->right);
}

// Add contact at end
void addContact()
{
    Contact* newNode = new Contact;

    cout << "\nEnter Contact ID (1-" << MAX << "): ";
    cin >> newNode->contactID;

    if (newNode->contactID < 1 || newNode->contactID > MAX ||
        findContact(newNode->contactID) != NULL)
    {
        cout << "\nInvalid or duplicate Contact ID!";
        delete newNode;
        return;
    }

    cin.ignore();

    cout << "Enter Contact Name: ";
    getline(cin, newNode->name);

    cout << "Enter Phone Number: ";
    getline(cin, newNode->phone);

    newNode->prev = NULL;
    newNode->next = NULL;

    // If list is empty
    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        Contact* temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->prev = temp;
    }

    // Insert into BST
    root = insertTree(root, newNode->contactID, newNode->name);

    cout << "\nContact added successfully!";
}

// Display all contacts
void displayContacts()
{
    if (head == NULL)
    {
        cout << "\nNo contact records found!";
        return;
    }

    Contact* temp = head;

    cout << "\n========== CONTACT RECORDS ==========\n";

    while (temp != NULL)
    {
        cout << "\nContact ID : " << temp->contactID;
        cout << "\nName       : " << temp->name;
        cout << "\nPhone      : " << temp->phone;
        cout << "\n-------------------------------------";

        temp = temp->next;
    }
}

// Display contacts in reverse order
void displayReverse()
{
    if (head == NULL)
    {
        cout << "\nNo contact records found!";
        return;
    }

    Contact* temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    cout << "\n======= CONTACTS: REVERSE ORDER =======\n";

    while (temp != NULL)
    {
        cout << "\nContact ID : " << temp->contactID;
        cout << "\nName       : " << temp->name;
        cout << "\n-------------------------------------";

        temp = temp->prev;
    }
}

// Search contact by ID
void searchContact()
{
    int id;

    cout << "\nEnter Contact ID to search: ";
    cin >> id;

    Contact* temp = findContact(id);

    if (temp == NULL)
    {
        cout << "\nContact not found!";
        return;
    }

    cout << "\nContact Found!";
    cout << "\nContact ID : " << temp->contactID;
    cout << "\nName       : " << temp->name;
    cout << "\nPhone      : " << temp->phone;
}

// Search contact by name (using BST)
void searchByName()
{
    string name;

    cin.ignore();

    cout << "\nEnter Contact Name to search: ";
    getline(cin, name);

    TreeNode* result = searchTree(root, name);

    if (result == NULL)
    {
        cout << "\nContact not found!";
        return;
    }

    Contact* temp = findContact(result->contactID);

    cout << "\nContact Found!";
    cout << "\nContact ID : " << temp->contactID;
    cout << "\nName       : " << temp->name;
    cout << "\nPhone      : " << temp->phone;
}

// Connect two contacts (graph edge)
void addConnection()
{
    int a, b;

    cout << "\nEnter first Contact ID: ";
    cin >> a;

    cout << "Enter second Contact ID: ";
    cin >> b;

    if (findContact(a) == NULL || findContact(b) == NULL || a == b)
    {
        cout << "\nInvalid Contact IDs!";
        return;
    }

    graph[a - 1][b - 1] = 1;
    graph[b - 1][a - 1] = 1;

    cout << "\nContacts connected successfully!";
}

// BFS traversal of contact network
void bfs()
{
    int id;

    cout << "\nEnter starting Contact ID: ";
    cin >> id;

    if (findContact(id) == NULL)
    {
        cout << "\nContact not found!";
        return;
    }

    bool visited[MAX] = {false};
    int queue[MAX];
    int f = 0, r = 0;

    visited[id - 1] = true;
    queue[r++] = id - 1;

    cout << "\nBFS Traversal (nearest first):";

    while (f < r)
    {
        int u = queue[f++];

        cout << "\n  " << findContact(u + 1)->name;

        for (int v = 0; v < MAX; v++)
        {
            if (graph[u][v] == 1 && !visited[v])
            {
                visited[v] = true;
                queue[r++] = v;
            }
        }
    }
}

// DFS helper function
void dfs(int u, bool visited[])
{
    visited[u] = true;

    cout << "\n  " << findContact(u + 1)->name;

    for (int v = 0; v < MAX; v++)
    {
        if (graph[u][v] == 1 && !visited[v])
        {
            dfs(v, visited);
        }
    }
}

// DFS traversal of contact network
void dfsTraversal()
{
    int id;

    cout << "\nEnter starting Contact ID: ";
    cin >> id;

    if (findContact(id) == NULL)
    {
        cout << "\nContact not found!";
        return;
    }

    bool visited[MAX] = {false};

    cout << "\nDFS Traversal:";

    dfs(id - 1, visited);
}

// Call contact (enqueue in call log)
void callContact()
{
    int id;

    cout << "\nEnter Contact ID to call: ";
    cin >> id;

    Contact* temp = findContact(id);

    if (temp == NULL)
    {
        cout << "\nContact not found!";
        return;
    }

    CallNode* newNode = new CallNode;

    newNode->name = temp->name;
    newNode->next = NULL;

    if (front == NULL)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }

    cout << "\nCalling " << temp->name << " (" << temp->phone << ")...";
}

// Remove oldest call (dequeue)
void removeOldestCall()
{
    if (front == NULL)
    {
        cout << "\nCall log is empty!";
        return;
    }

    CallNode* temp = front;
    front = front->next;

    if (front == NULL)
    {
        rear = NULL;
    }

    cout << "\nRemoved oldest call: " << temp->name;

    delete temp;
}

// Main function
int main()
{
    int choice;

    do
    {
        cout << "\n\n====================================";
        cout << "\n    CONTACT MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Add Contact";
        cout << "\n2. Display Contacts";
        cout << "\n3. Display Contacts in Reverse";
        cout << "\n4. Search Contact by ID";
        cout << "\n5. Search Contact by Name";
        cout << "\n6. Display Contacts Sorted by Name";
        cout << "\n7. Connect Two Contacts";
        cout << "\n8. BFS Traversal";
        cout << "\n9. DFS Traversal";
        cout << "\n10. Call Contact";
        cout << "\n11. Remove Oldest Call from Log";
        cout << "\n12. Exit";
        cout << "\n====================================";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addContact();
                break;

            case 2:
                displayContacts();
                break;

            case 3:
                displayReverse();
                break;

            case 4:
                searchContact();
                break;

            case 5:
                searchByName();
                break;

            case 6:
                cout << "\n====== CONTACTS SORTED BY NAME ======\n";
                inorder(root);
                break;

            case 7:
                addConnection();
                break;

            case 8:
                bfs();
                break;

            case 9:
                dfsTraversal();
                break;

            case 10:
                callContact();
                break;

            case 11:
                removeOldestCall();
                break;

            case 12:
                cout << "\nProgram ended.";
                break;

            default:
                cout << "\nInvalid choice!";
        }

    } while (choice != 12);

    return 0;
}
