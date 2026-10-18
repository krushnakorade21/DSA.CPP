// Leaf and Non-Leaf Node Counting in a General Tree
// Features:
//   1. Construct a general tree (any number of children per node)
//   2. Display the tree structure
//   3. Count + display leaf nodes and non-leaf nodes (with actual values)
//   4. Count nodes at each level
//   5. Query the children of a selected node

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int data;
    vector<Node*> children;   // a general tree node can have any number of children
    Node(int v) : data(v) {}
};

class GeneralTree {
    Node* root;

    // search a node by value (recursive DFS)
    Node* findNode(Node* cur, int key) {
        if (cur == NULL) return NULL;
        if (cur->data == key) return cur;
        for (size_t i = 0; i < cur->children.size(); i++) {
            Node* res = findNode(cur->children[i], key);
            if (res != NULL) return res;
        }
        return NULL;
    }

    // collect leaf and non-leaf values (recursive preorder)
    void collect(Node* cur, vector<int>& leaves, vector<int>& nonLeaves) {
        if (cur == NULL) return;
        if (cur->children.empty()) leaves.push_back(cur->data);
        else nonLeaves.push_back(cur->data);
        for (size_t i = 0; i < cur->children.size(); i++)
            collect(cur->children[i], leaves, nonLeaves);
    }

    // print tree with indentation
    void printTree(Node* cur, int depth) {
        if (cur == NULL) return;
        for (int i = 0; i < depth; i++) cout << "    ";
        if (depth > 0) cout << "|-- ";
        cout << cur->data << (cur->children.empty() ? "  (leaf)" : "") << endl;
        for (size_t i = 0; i < cur->children.size(); i++)
            printTree(cur->children[i], depth + 1);
    }

    void freeTree(Node* cur) {
        if (cur == NULL) return;
        for (size_t i = 0; i < cur->children.size(); i++)
            freeTree(cur->children[i]);
        delete cur;
    }

public:
    GeneralTree() : root(NULL) {}
    ~GeneralTree() { freeTree(root); }

    bool isEmpty() { return root == NULL; }

    bool exists(int key) { return findNode(root, key) != NULL; }

    bool createRoot(int val) {
        if (root != NULL) return false;
        root = new Node(val);
        return true;
    }

    // add child under parent; returns 0 ok, 1 parent missing, 2 duplicate value
    int addChild(int parentVal, int childVal) {
        Node* parent = findNode(root, parentVal);
        if (parent == NULL) return 1;
        if (findNode(root, childVal) != NULL) return 2;
        parent->children.push_back(new Node(childVal));
        return 0;
    }

    void display() {
        if (root == NULL) { cout << "Tree is empty.\n"; return; }
        cout << "\n----- Tree Structure -----\n";
        printTree(root, 0);
    }

    void showLeafNonLeaf() {
        if (root == NULL) { cout << "Tree is empty.\n"; return; }
        vector<int> leaves, nonLeaves;
        collect(root, leaves, nonLeaves);

        cout << "\nLeaf nodes (" << leaves.size() << "): ";
        for (size_t i = 0; i < leaves.size(); i++) cout << leaves[i] << " ";

        cout << "\nNon-leaf nodes (" << nonLeaves.size() << "): ";
        for (size_t i = 0; i < nonLeaves.size(); i++) cout << nonLeaves[i] << " ";

        cout << "\nTotal nodes: " << leaves.size() + nonLeaves.size() << endl;
    }

    // level order traversal (BFS) to count nodes at every level
    void levelCounts() {
        if (root == NULL) { cout << "Tree is empty.\n"; return; }
        queue<Node*> q;
        q.push(root);
        int level = 0;
        cout << "\n----- Nodes at Each Level -----\n";
        while (!q.empty()) {
            int sz = q.size();
            cout << "Level " << level << " : " << sz << " node(s) -> ";
            for (int i = 0; i < sz; i++) {
                Node* cur = q.front();
                q.pop();
                cout << cur->data << " ";
                for (size_t j = 0; j < cur->children.size(); j++)
                    q.push(cur->children[j]);
            }
            cout << endl;
            level++;
        }
        cout << "Height of tree (levels): " << level << endl;
    }

    void queryChildren(int val) {
        Node* n = findNode(root, val);
        if (n == NULL) { cout << "Node " << val << " not found in the tree.\n"; return; }
        if (n->children.empty()) {
            cout << "Node " << val << " is a LEAF node. It has no children.\n";
            return;
        }
        cout << "Node " << val << " is a NON-LEAF node with "
             << n->children.size() << " child(ren): ";
        for (size_t i = 0; i < n->children.size(); i++)
            cout << n->children[i]->data << " ";
        cout << endl;
    }

    // sample tree for quick testing
    void loadSample() {
        if (root != NULL) { cout << "Tree already exists. Cannot load sample.\n"; return; }
        createRoot(1);
        addChild(1, 2);  addChild(1, 3);  addChild(1, 4);
        addChild(2, 5);  addChild(2, 6);
        addChild(3, 7);
        addChild(4, 8);  addChild(4, 9);  addChild(4, 10);
        addChild(6, 11); addChild(6, 12);
        cout << "Sample tree loaded.\n";
    }
};

void menu() {
    cout << "\n========== GENERAL TREE MENU ==========\n";
    cout << "1. Create root\n";
    cout << "2. Add child to a node\n";
    cout << "3. Display tree\n";
    cout << "4. Display leaf and non-leaf nodes (with count)\n";
    cout << "5. Count nodes at each level\n";
    cout << "6. Query children of a node\n";
    cout << "7. Load sample tree\n";
    cout << "8. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    GeneralTree t;
    int choice, a, b;

    do {
        menu();
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter root value: ";
            cin >> a;
            if (t.createRoot(a)) cout << "Root created.\n";
            else cout << "Root already exists.\n";
            break;
        case 2:
            if (t.isEmpty()) { cout << "Create the root first.\n"; break; }
            cout << "Enter parent value: ";
            cin >> a;
            cout << "Enter child value: ";
            cin >> b;
            {
                int r = t.addChild(a, b);
                if (r == 0) cout << "Child " << b << " added under " << a << ".\n";
                else if (r == 1) cout << "Parent " << a << " not found.\n";
                else cout << "Value " << b << " already exists (values must be unique).\n";
            }
            break;
        case 3:
            t.display();
            break;
        case 4:
            t.showLeafNonLeaf();
            break;
        case 5:
            t.levelCounts();
            break;
        case 6:
            if (t.isEmpty()) { cout << "Tree is empty.\n"; break; }
            cout << "Enter node value to query: ";
            cin >> a;
            t.queryChildren(a);
            break;
        case 7:
            t.loadSample();
            break;
        case 8:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);

    return 0;
}
