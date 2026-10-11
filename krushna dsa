/*
 * CONTACT MANAGEMENT SYSTEM
 * Subject : Data Structures and Algorithms (C++)
 * Concepts: Pointers, Dynamic Memory, Doubly Linked List, Circular Linked List,
 *           Stack (linked list), Queue (linked list), AVL Tree (BST), Graph
 *           (using struct only, no classes)
 *
 * Data structures used:
 *   1. Doubly Linked List   -> stores all contacts (forward/backward traversal)
 *   2. AVL Tree (BST)       -> name index: fast search + sorted display + traversals
 *   3. Stack (linked list)  -> deleted contacts (history + undo last delete)
 *   4. Queue (linked list)  -> scheduled call queue (first come, first called)
 *   5. Circular Linked List -> recent calls (fixed size, oldest is overwritten)
 *   6. Graph (adj. list)    -> "who knows whom" connections between contacts,
 *                              with BFS, DFS, adjacency matrix and shortest introduction path
 */

#include <iostream>
#include <string>
#include <limits>
using namespace std;

#define MAX_ID 30        // contact IDs allowed: 1 to 30 (also graph vertices)
#define MAX_RECENT 5     // size of the recent-calls circular list

/* ------------------------------------------------------------------ */
/*                           STRUCTURES                                */
/* ------------------------------------------------------------------ */

// Node of the doubly linked list (one contact)
struct Contact {
    int id;
    string name;
    string phone;
    string group;
    Contact *prev;       // pointer to previous node
    Contact *next;       // pointer to next node
};

// Doubly linked list holder
struct ContactList {
    Contact *head;
    Contact *tail;
    int count;
};

// Node of the AVL tree (name index)
struct AVLNode {
    string key;          // lower case name (used for comparison)
    string name;         // original name (used for display)
    int id;              // contact id
    AVLNode *left;
    AVLNode *right;
    int height;
};

// Plain record (no list pointers) kept in the stack after delete
struct DeletedRecord {
    int id;
    string name;
    string phone;
    string group;
};

// Node of the stack (linked list implementation)
struct StackNode {
    DeletedRecord data;
    StackNode *next;
};

struct Stack {
    StackNode *top;
    int count;
};

// Node of the call queue (linked list implementation)
struct QueueNode {
    int id;
    string name;
    string phone;
    QueueNode *next;
};

struct Queue {
    QueueNode *front;
    QueueNode *rear;
    int count;
};

// Node of the circular linked list (recent calls)
struct RecentNode {
    int id;
    string name;
    string phone;
    RecentNode *next;
};

struct RecentList {
    RecentNode *last;    // points to the newest node; last->next is the oldest
    int count;
};

// Node of the graph adjacency list
struct AdjNode {
    int id;
    AdjNode *next;
};

struct Graph {
    AdjNode *adj[MAX_ID + 1];
};

/* ------------------------------------------------------------------ */
/*                        INITIALIZATION                               */
/* ------------------------------------------------------------------ */

void initList(ContactList &list) {
    list.head = NULL;
    list.tail = NULL;
    list.count = 0;
}

void initStack(Stack &s) {
    s.top = NULL;
    s.count = 0;
}

void initQueue(Queue &q) {
    q.front = NULL;
    q.rear = NULL;
    q.count = 0;
}

void initRecent(RecentList &r) {
    r.last = NULL;
    r.count = 0;
}

void initGraph(Graph &g) {
    for (int i = 0; i <= MAX_ID; i++) g.adj[i] = NULL;
}

/* ------------------------------------------------------------------ */
/*                        INPUT HELPERS                                */
/* ------------------------------------------------------------------ */

int readInt(const string &msg, int minVal, int maxVal) {
    int x;
    while (true) {
        cout << msg;
        if (cin >> x && x >= minVal && x <= maxVal) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cout << "  Invalid input! Enter a number between " << minVal
             << " and " << maxVal << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readText(const string &msg) {
    string s;
    while (true) {
        cout << msg;
        getline(cin, s);
        if (!s.empty()) return s;
        cout << "  Input cannot be empty!\n";
    }
}

string readPhone(const string &msg) {
    while (true) {
        string s = readText(msg);
        bool ok = (s.length() == 10);
        for (size_t i = 0; i < s.length() && ok; i++)
            if (s[i] < '0' || s[i] > '9') ok = false;
        if (ok) return s;
        cout << "  Phone number must be exactly 10 digits!\n";
    }
}

string toLower(string s) {
    for (size_t i = 0; i < s.length(); i++)
        if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] + 32;
    return s;
}

/* ------------------------------------------------------------------ */
/*                  DOUBLY LINKED LIST OPERATIONS                      */
/* ------------------------------------------------------------------ */

Contact* searchById(ContactList &list, int id) {
    Contact *temp = list.head;
    while (temp != NULL) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return NULL;
}

// Insert a node at the end of the list
void insertEnd(ContactList &list, int id, string name, string phone,
               string group) {
    Contact *p = new Contact;
    p->id = id;
    p->name = name;
    p->phone = phone;
    p->group = group;
    p->next = NULL;
    p->prev = list.tail;

    if (list.head == NULL)
        list.head = list.tail = p;
    else {
        list.tail->next = p;
        list.tail = p;
    }
    list.count++;
}

// Remove a node from the list (does not free it, caller deletes)
void unlinkNode(ContactList &list, Contact *p) {
    if (p->prev != NULL) p->prev->next = p->next;
    else                 list.head = p->next;      // deleting first node

    if (p->next != NULL) p->next->prev = p->prev;
    else                 list.tail = p->prev;      // deleting last node

    list.count--;
}

void printContact(Contact *p) {
    cout << "ID: " << p->id << " | Name: " << p->name
         << " | Phone: " << p->phone << " | Group: " << p->group << "\n";
}

string nameOf(ContactList &list, int id) {
    Contact *p = searchById(list, id);
    if (p != NULL) return p->name;
    return "(deleted)";
}

void freeAll(ContactList &list) {
    Contact *temp = list.head;
    while (temp != NULL) {
        Contact *nx = temp->next;
        delete temp;
        temp = nx;
    }
    list.head = list.tail = NULL;
    list.count = 0;
}

/* ------------------------------------------------------------------ */
/*                        AVL TREE OPERATIONS                          */
/* ------------------------------------------------------------------ */

int height(AVLNode *n) { return (n == NULL) ? 0 : n->height; }

int maxOf(int a, int b) { return (a > b) ? a : b; }

int balanceFactor(AVLNode *n) {
    return (n == NULL) ? 0 : height(n->left) - height(n->right);
}

AVLNode* newAVLNode(string key, string name, int id) {
    AVLNode *n = new AVLNode;
    n->key = key;
    n->name = name;
    n->id = id;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

// Right rotation (used for LL case)
AVLNode* rotateRight(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *t = x->right;
    x->right = y;
    y->left = t;
    y->height = 1 + maxOf(height(y->left), height(y->right));
    x->height = 1 + maxOf(height(x->left), height(x->right));
    return x;
}

// Left rotation (used for RR case)
AVLNode* rotateLeft(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *t = y->left;
    y->left = x;
    x->right = t;
    x->height = 1 + maxOf(height(x->left), height(x->right));
    y->height = 1 + maxOf(height(y->left), height(y->right));
    return y;
}

// Fix balance of a node after insert/delete (LL, RR, LR, RL)
AVLNode* rebalance(AVLNode *node) {
    node->height = 1 + maxOf(height(node->left), height(node->right));
    int bf = balanceFactor(node);

    if (bf > 1 && balanceFactor(node->left) >= 0)          // LL
        return rotateRight(node);
    if (bf > 1 && balanceFactor(node->left) < 0) {         // LR
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (bf < -1 && balanceFactor(node->right) <= 0)        // RR
        return rotateLeft(node);
    if (bf < -1 && balanceFactor(node->right) > 0) {       // RL
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

AVLNode* insertAVL(AVLNode *node, string key, string name, int id) {
    if (node == NULL) return newAVLNode(key, name, id);
    if (key < node->key)      node->left = insertAVL(node->left, key, name, id);
    else if (key > node->key) node->right = insertAVL(node->right, key, name, id);
    else return node;                                      // names are unique
    return rebalance(node);
}

AVLNode* minNode(AVLNode *node) {
    while (node->left != NULL) node = node->left;
    return node;
}

AVLNode* deleteAVL(AVLNode *node, string key) {
    if (node == NULL) return NULL;
    if (key < node->key)      node->left = deleteAVL(node->left, key);
    else if (key > node->key) node->right = deleteAVL(node->right, key);
    else {
        if (node->left == NULL || node->right == NULL) {
            AVLNode *child = (node->left != NULL) ? node->left : node->right;
            delete node;
            return child;                                  // 0 or 1 child
        }
        AVLNode *succ = minNode(node->right);              // 2 children
        node->key = succ->key;
        node->name = succ->name;
        node->id = succ->id;
        node->right = deleteAVL(node->right, succ->key);
    }
    return rebalance(node);
}

AVLNode* searchAVL(AVLNode *node, string key) {
    while (node != NULL) {
        if (key == node->key) return node;
        node = (key < node->key) ? node->left : node->right;
    }
    return NULL;
}

void inorder(AVLNode *n) {
    if (n == NULL) return;
    inorder(n->left);
    cout << "  " << n->name << " (ID " << n->id << ")\n";
    inorder(n->right);
}

void preorder(AVLNode *n) {
    if (n == NULL) return;
    cout << "  " << n->name << " (ID " << n->id << ")\n";
    preorder(n->left);
    preorder(n->right);
}

void postorder(AVLNode *n) {
    if (n == NULL) return;
    postorder(n->left);
    postorder(n->right);
    cout << "  " << n->name << " (ID " << n->id << ")\n";
}

void freeTree(AVLNode *n) {
    if (n == NULL) return;
    freeTree(n->left);
    freeTree(n->right);
    delete n;
}

/* ------------------------------------------------------------------ */
/*                  STACK OPERATIONS (LINKED LIST)                     */
/* ------------------------------------------------------------------ */

bool isStackEmpty(Stack &s) { return s.top == NULL; }

void push(Stack &s, DeletedRecord r) {
    StackNode *n = new StackNode;
    n->data = r;
    n->next = s.top;
    s.top = n;
    s.count++;
}

bool pop(Stack &s, DeletedRecord &r) {
    if (isStackEmpty(s)) return false;
    StackNode *n = s.top;
    r = n->data;
    s.top = n->next;
    delete n;
    s.count--;
    return true;
}

void freeStack(Stack &s) {
    DeletedRecord r;
    while (pop(s, r)) {}
}

/* ------------------------------------------------------------------ */
/*                  QUEUE OPERATIONS (LINKED LIST)                     */
/* ------------------------------------------------------------------ */

bool isQueueEmpty(Queue &q) { return q.front == NULL; }

void enqueue(Queue &q, int id, string name, string phone) {
    QueueNode *n = new QueueNode;
    n->id = id;
    n->name = name;
    n->phone = phone;
    n->next = NULL;
    if (q.rear == NULL) q.front = q.rear = n;
    else {
        q.rear->next = n;
        q.rear = n;
    }
    q.count++;
}

bool dequeue(Queue &q, int &id, string &name, string &phone) {
    if (isQueueEmpty(q)) return false;
    QueueNode *n = q.front;
    id = n->id;
    name = n->name;
    phone = n->phone;
    q.front = n->next;
    if (q.front == NULL) q.rear = NULL;
    delete n;
    q.count--;
    return true;
}

void freeQueue(Queue &q) {
    int id; string name, phone;
    while (dequeue(q, id, name, phone)) {}
}

/* ------------------------------------------------------------------ */
/*              CIRCULAR LINKED LIST OPERATIONS (RECENT CALLS)         */
/* ------------------------------------------------------------------ */

void addRecent(RecentList &r, int id, string name, string phone) {
    if (r.count == MAX_RECENT) {
        // list is full: overwrite the oldest node, it becomes the newest
        RecentNode *oldest = r.last->next;
        oldest->id = id;
        oldest->name = name;
        oldest->phone = phone;
        r.last = oldest;
        return;
    }
    RecentNode *n = new RecentNode;
    n->id = id;
    n->name = name;
    n->phone = phone;
    if (r.last == NULL) {
        n->next = n;                 // single node points to itself
        r.last = n;
    } else {
        n->next = r.last->next;      // new node points to the oldest
        r.last->next = n;
        r.last = n;
    }
    r.count++;
}

void displayRecent(RecentList &r) {
    cout << "\n--- RECENT CALLS (Oldest to Latest) ---\n";
    if (r.last == NULL) { cout << "No calls made yet.\n"; return; }
    RecentNode *temp = r.last->next;
    int i = 1;
    do {
        cout << i++ << ". " << temp->name << " | " << temp->phone
             << " (ID " << temp->id << ")\n";
        temp = temp->next;
    } while (temp != r.last->next);
    cout << "(Only the last " << MAX_RECENT << " calls are kept)\n";
}

void freeRecent(RecentList &r) {
    if (r.last == NULL) return;
    RecentNode *cur = r.last->next;
    r.last->next = NULL;             // break the circle
    while (cur != NULL) {
        RecentNode *nx = cur->next;
        delete cur;
        cur = nx;
    }
    r.last = NULL;
    r.count = 0;
}

/* ------------------------------------------------------------------ */
/*                  GRAPH OPERATIONS (ADJACENCY LIST)                  */
/* ------------------------------------------------------------------ */

bool hasEdge(Graph &g, int u, int v) {
    AdjNode *t = g.adj[u];
    while (t != NULL) {
        if (t->id == v) return true;
        t = t->next;
    }
    return false;
}

void addEdgeOne(Graph &g, int u, int v) {
    AdjNode *n = new AdjNode;
    n->id = v;
    n->next = g.adj[u];
    g.adj[u] = n;
}

void addEdge(Graph &g, int u, int v) {   // undirected: add both ways
    addEdgeOne(g, u, v);
    addEdgeOne(g, v, u);
}

void removeEdgeOne(Graph &g, int u, int v) {
    AdjNode *cur = g.adj[u];
    AdjNode *prev = NULL;
    while (cur != NULL) {
        if (cur->id == v) {
            if (prev == NULL) g.adj[u] = cur->next;
            else prev->next = cur->next;
            delete cur;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

// remove a vertex: delete all its edges in both directions
void removeAllEdges(Graph &g, int id) {
    AdjNode *t = g.adj[id];
    while (t != NULL) {
        removeEdgeOne(g, t->id, id);
        AdjNode *nx = t->next;
        delete t;
        t = nx;
    }
    g.adj[id] = NULL;
}

void freeGraph(Graph &g) {
    for (int i = 0; i <= MAX_ID; i++) {
        AdjNode *t = g.adj[i];
        while (t != NULL) {
            AdjNode *nx = t->next;
            delete t;
            t = nx;
        }
        g.adj[i] = NULL;
    }
}

void displayAdjList(Graph &g, ContactList &list) {
    cout << "\n--- ADJACENCY LIST ---\n";
    bool any = false;
    Contact *c = list.head;
    while (c != NULL) {
        cout << c->name << " (" << c->id << ") -> ";
        AdjNode *t = g.adj[c->id];
        if (t == NULL) cout << "no connections";
        while (t != NULL) {
            cout << nameOf(list, t->id) << " (" << t->id << ")";
            if (t->next != NULL) cout << ", ";
            t = t->next;
        }
        cout << "\n";
        any = true;
        c = c->next;
    }
    if (!any) cout << "No contacts available.\n";
}

void displayAdjMatrix(Graph &g, ContactList &list) {
    cout << "\n--- ADJACENCY MATRIX (contact IDs) ---\n";
    int ids[MAX_ID];
    int n = 0;
    Contact *c = list.head;
    while (c != NULL) { ids[n++] = c->id; c = c->next; }
    if (n == 0) { cout << "No contacts available.\n"; return; }

    cout << "     ";
    for (int i = 0; i < n; i++) cout << ids[i] << "\t";
    cout << "\n";
    for (int i = 0; i < n; i++) {
        cout << ids[i] << "  | ";
        for (int j = 0; j < n; j++)
            cout << (hasEdge(g, ids[i], ids[j]) ? 1 : 0) << "\t";
        cout << "\n";
    }
}

// BFS: contacts reachable level by level
void bfs(Graph &g, ContactList &list, int start) {
    bool visited[MAX_ID + 1] = {false};
    int q[MAX_ID + 1];
    int front = 0, rear = 0;

    visited[start] = true;
    q[rear++] = start;
    cout << "BFS order: ";
    while (front < rear) {
        int u = q[front++];
        cout << nameOf(list, u) << "  ";
        AdjNode *t = g.adj[u];
        while (t != NULL) {
            if (!visited[t->id]) {
                visited[t->id] = true;
                q[rear++] = t->id;
            }
            t = t->next;
        }
    }
    cout << "\n";
}

void dfsUtil(Graph &g, ContactList &list, int u, bool visited[]) {
    visited[u] = true;
    cout << nameOf(list, u) << "  ";
    AdjNode *t = g.adj[u];
    while (t != NULL) {
        if (!visited[t->id]) dfsUtil(g, list, t->id, visited);
        t = t->next;
    }
}

void dfs(Graph &g, ContactList &list, int start) {
    bool visited[MAX_ID + 1] = {false};
    cout << "DFS order: ";
    dfsUtil(g, list, start, visited);
    cout << "\n";
}

// Shortest introduction chain (fewest hops) using BFS
void shortestPath(Graph &g, ContactList &list, int src, int dest) {
    bool visited[MAX_ID + 1] = {false};
    int parent[MAX_ID + 1];
    int q[MAX_ID + 1];
    int front = 0, rear = 0;
    for (int i = 0; i <= MAX_ID; i++) parent[i] = -1;

    visited[src] = true;
    q[rear++] = src;
    while (front < rear) {
        int u = q[front++];
        AdjNode *t = g.adj[u];
        while (t != NULL) {
            if (!visited[t->id]) {
                visited[t->id] = true;
                parent[t->id] = u;
                q[rear++] = t->id;
            }
            t = t->next;
        }
    }

    if (!visited[dest]) {
        cout << "No chain of connections exists between them.\n";
        return;
    }
    int path[MAX_ID + 1];
    int len = 0;
    for (int v = dest; v != -1; v = parent[v]) path[len++] = v;

    cout << "Shortest introduction chain (" << len - 1 << " hop(s)):\n  ";
    for (int i = len - 1; i >= 0; i--) {
        cout << nameOf(list, path[i]);
        if (i > 0) cout << " -> ";
    }
    cout << "\n";
}

/* ------------------------------------------------------------------ */
/*                           MENU FUNCTIONS                            */
/* ------------------------------------------------------------------ */

void addContact(ContactList &list, AVLNode *&root) {
    cout << "\n--- ADD NEW CONTACT ---\n";
    int id = readInt("Enter Contact ID (1-30): ", 1, MAX_ID);
    if (searchById(list, id) != NULL) {
        cout << "A contact with this ID already exists!\n";
        return;
    }
    string name = readText("Enter Name: ");
    if (searchAVL(root, toLower(name)) != NULL) {
        cout << "A contact with this name already exists!\n";
        return;
    }
    string phone = readPhone("Enter 10-digit Phone Number: ");
    string group = readText("Enter Group (Family/Friend/Work): ");

    insertEnd(list, id, name, phone, group);
    root = insertAVL(root, toLower(name), name, id);
    cout << "Contact saved successfully.\n";
}

void deleteContact(ContactList &list, AVLNode *&root, Graph &g, Stack &history) {
    cout << "\n--- DELETE CONTACT ---\n";
    if (list.head == NULL) {
        cout << "No contacts available.\n";
        return;
    }
    int id = readInt("Enter Contact ID to delete: ", 1, MAX_ID);
    Contact *p = searchById(list, id);
    if (p == NULL) {
        cout << "Contact not found.\n";
        return;
    }

    // save record in stack (history)
    DeletedRecord r;
    r.id = p->id;
    r.name = p->name;
    r.phone = p->phone;
    r.group = p->group;
    push(history, r);

    removeAllEdges(g, id);
    root = deleteAVL(root, toLower(p->name));
    unlinkNode(list, p);
    cout << "Contact " << p->name << " deleted.\n";
    delete p;
}

void searchContact(ContactList &list, AVLNode *root) {
    cout << "\n--- SEARCH CONTACT ---\n";
    cout << "1. Search by ID (linked list)\n2. Search by Name (AVL tree)\n";
    int ch = readInt("Enter choice: ", 1, 2);

    if (ch == 1) {
        int id = readInt("Enter Contact ID: ", 1, MAX_ID);
        Contact *p = searchById(list, id);
        if (p) { cout << "Contact found:\n"; printContact(p); }
        else cout << "Contact not found.\n";
    } else {
        string name = readText("Enter Name: ");
        AVLNode *n = searchAVL(root, toLower(name));
        if (n) {
            cout << "Contact found:\n";
            printContact(searchById(list, n->id));
        } else cout << "Contact not found.\n";
    }
}

void updatePhone(ContactList &list) {
    cout << "\n--- UPDATE PHONE NUMBER ---\n";
    int id = readInt("Enter Contact ID: ", 1, MAX_ID);
    Contact *p = searchById(list, id);
    if (p == NULL) {
        cout << "Contact not found.\n";
        return;
    }
    p->phone = readPhone("Enter new 10-digit Phone Number: ");
    cout << "Phone number updated.\n";
}

void displayForward(ContactList &list) {
    cout << "\n--- CONTACTS (Oldest to Newest) ---\n";
    if (list.head == NULL) { cout << "No contacts available.\n"; return; }
    Contact *temp = list.head;
    while (temp != NULL) {
        printContact(temp);
        temp = temp->next;
    }
    cout << "Total contacts: " << list.count << "\n";
}

void displayBackward(ContactList &list) {
    cout << "\n--- CONTACTS (Newest to Oldest) ---\n";
    if (list.tail == NULL) { cout << "No contacts available.\n"; return; }
    Contact *temp = list.tail;
    while (temp != NULL) {
        printContact(temp);
        temp = temp->prev;
    }
    cout << "Total contacts: " << list.count << "\n";
}

void displaySorted(AVLNode *root) {
    cout << "\n--- CONTACTS SORTED BY NAME (AVL inorder) ---\n";
    if (root == NULL) { cout << "No contacts available.\n"; return; }
    inorder(root);
}

void showTreeInfo(AVLNode *root) {
    cout << "\n--- AVL TREE TRAVERSALS ---\n";
    if (root == NULL) { cout << "Tree is empty.\n"; return; }
    cout << "Tree height: " << height(root) << "\n";
    cout << "Root node  : " << root->name << "\n";
    cout << "Inorder:\n";   inorder(root);
    cout << "Preorder:\n";  preorder(root);
    cout << "Postorder:\n"; postorder(root);
}

void makeCall(ContactList &list, RecentList &recent) {
    cout << "\n--- MAKE A CALL ---\n";
    int id = readInt("Enter Contact ID to call: ", 1, MAX_ID);
    Contact *p = searchById(list, id);
    if (p == NULL) {
        cout << "Contact not found.\n";
        return;
    }
    cout << "Calling " << p->name << " on " << p->phone << " ...\n";
    addRecent(recent, p->id, p->name, p->phone);
}

void addToCallQueue(ContactList &list, Queue &q) {
    cout << "\n--- ADD TO CALL QUEUE ---\n";
    int id = readInt("Enter Contact ID to call later: ", 1, MAX_ID);
    Contact *p = searchById(list, id);
    if (p == NULL) {
        cout << "Contact not found.\n";
        return;
    }
    enqueue(q, p->id, p->name, p->phone);
    cout << p->name << " added to call queue. Position: " << q.count << "\n";
}

void processNextCall(Queue &q, RecentList &recent) {
    cout << "\n--- PROCESS NEXT CALL ---\n";
    int id; string name, phone;
    if (!dequeue(q, id, name, phone)) {
        cout << "Call queue is empty.\n";
        return;
    }
    cout << "Calling " << name << " on " << phone << " ...\n";
    addRecent(recent, id, name, phone);
}

void displayQueue(Queue &q) {
    cout << "\n--- CALL QUEUE (Front to Rear) ---\n";
    if (isQueueEmpty(q)) { cout << "Call queue is empty.\n"; return; }
    QueueNode *t = q.front;
    int i = 1;
    while (t != NULL) {
        cout << i++ << ". " << t->name << " | " << t->phone << "\n";
        t = t->next;
    }
}

void undoDelete(ContactList &list, AVLNode *&root, Stack &history) {
    cout << "\n--- UNDO LAST DELETE ---\n";
    if (isStackEmpty(history)) {
        cout << "No delete history available.\n";
        return;
    }
    DeletedRecord r = history.top->data;

    if (searchById(list, r.id) != NULL) {
        cout << "A contact with this ID already exists.\n";
        return;
    }
    if (searchAVL(root, toLower(r.name)) != NULL) {
        cout << "A contact with this name already exists.\n";
        return;
    }

    pop(history, r);
    insertEnd(list, r.id, r.name, r.phone, r.group);
    root = insertAVL(root, toLower(r.name), r.name, r.id);
    cout << "Contact " << r.name << " restored (connections are not restored).\n";
}

void displayHistory(Stack &history) {
    cout << "\n--- DELETED CONTACTS (Latest first) ---\n";
    if (isStackEmpty(history)) { cout << "No contacts deleted yet.\n"; return; }
    StackNode *t = history.top;
    while (t != NULL) {
        cout << "ID: " << t->data.id << " | Name: " << t->data.name
             << " | Phone: " << t->data.phone
             << " | Group: " << t->data.group << "\n";
        t = t->next;
    }
}

void addConnection(ContactList &list, Graph &g) {
    cout << "\n--- ADD CONNECTION (two contacts know each other) ---\n";
    int u = readInt("Enter first Contact ID: ", 1, MAX_ID);
    int v = readInt("Enter second Contact ID: ", 1, MAX_ID);
    if (u == v) { cout << "A contact cannot be connected to itself.\n"; return; }
    if (searchById(list, u) == NULL || searchById(list, v) == NULL) {
        cout << "Both contacts must exist.\n";
        return;
    }
    if (hasEdge(g, u, v)) {
        cout << "They are already connected.\n";
        return;
    }
    addEdge(g, u, v);
    cout << nameOf(list, u) << " and " << nameOf(list, v) << " are now connected.\n";
}

void traverseGraph(ContactList &list, Graph &g) {
    cout << "\n--- GRAPH TRAVERSAL ---\n";
    int start = readInt("Enter starting Contact ID: ", 1, MAX_ID);
    if (searchById(list, start) == NULL) {
        cout << "Contact not found.\n";
        return;
    }
    bfs(g, list, start);
    dfs(g, list, start);
}

void findIntroduction(ContactList &list, Graph &g) {
    cout << "\n--- SHORTEST INTRODUCTION CHAIN ---\n";
    int s = readInt("Enter your Contact ID: ", 1, MAX_ID);
    int d = readInt("Enter target Contact ID: ", 1, MAX_ID);
    if (searchById(list, s) == NULL || searchById(list, d) == NULL) {
        cout << "Both contacts must exist.\n";
        return;
    }
    shortestPath(g, list, s, d);
}

/* ------------------------------------------------------------------ */
/*                               MAIN                                  */
/* ------------------------------------------------------------------ */

int main() {
    ContactList list;
    AVLNode *root = NULL;
    Stack history;
    Queue callQueue;
    RecentList recent;
    Graph graph;

    initList(list);
    initStack(history);
    initQueue(callQueue);
    initRecent(recent);
    initGraph(graph);

    int choice;
    do {
        cout << "\n=========================================\n";
        cout << "        CONTACT MANAGEMENT SYSTEM\n";
        cout << "=========================================\n";
        cout << " 1. Add contact\n";
        cout << " 2. Delete contact\n";
        cout << " 3. Search contact\n";
        cout << " 4. Update phone number\n";
        cout << " 5. Display all contacts (forward)\n";
        cout << " 6. Display all contacts (backward)\n";
        cout << " 7. Display contacts sorted by name\n";
        cout << " 8. Show AVL tree traversals\n";
        cout << " 9. Make a call\n";
        cout << "10. Add contact to call queue\n";
        cout << "11. Process next call in queue\n";
        cout << "12. Show call queue\n";
        cout << "13. Show recent calls\n";
        cout << "14. Undo last delete\n";
        cout << "15. Show deleted contacts history\n";
        cout << "16. Add connection between contacts\n";
        cout << "17. Show connections (list and matrix)\n";
        cout << "18. BFS / DFS from a contact\n";
        cout << "19. Shortest introduction chain\n";
        cout << " 0. Exit\n";
        choice = readInt("Enter your choice: ", 0, 19);

        switch (choice) {
            case 1:  addContact(list, root); break;
            case 2:  deleteContact(list, root, graph, history); break;
            case 3:  searchContact(list, root); break;
            case 4:  updatePhone(list); break;
            case 5:  displayForward(list); break;
            case 6:  displayBackward(list); break;
            case 7:  displaySorted(root); break;
            case 8:  showTreeInfo(root); break;
            case 9:  makeCall(list, recent); break;
            case 10: addToCallQueue(list, callQueue); break;
            case 11: processNextCall(callQueue, recent); break;
            case 12: displayQueue(callQueue); break;
            case 13: displayRecent(recent); break;
            case 14: undoDelete(list, root, history); break;
            case 15: displayHistory(history); break;
            case 16: addConnection(list, graph); break;
            case 17: displayAdjList(graph, list);
                     displayAdjMatrix(graph, list); break;
            case 18: traverseGraph(list, graph); break;
            case 19: findIntroduction(list, graph); break;
            case 0:  cout << "Exiting... Thank you!\n"; break;
        }
    } while (choice != 0);

    freeAll(list);
    freeTree(root);
    freeStack(history);
    freeQueue(callQueue);
    freeRecent(recent);
    freeGraph(graph);
    return 0;
}
