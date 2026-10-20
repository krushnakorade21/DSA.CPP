# 🌳 Leaf and Non-Leaf Node Counting in a General Tree

## 📌 Project Overview

The Leaf and Non-Leaf Node Counting project is a C++ mini-project that constructs a *General Tree* (a tree in which every node can have any number of children) and counts its leaf and non-leaf nodes. Each node stores its data, a pointer to its *first child* and a pointer to its *next sibling*.

Along with counting, the program displays the actual leaf and non-leaf node values, counts the nodes at each level, and lets the user query the children of any selected node.

The project is written using structures only (no classes) and has a menu-driven interface.

## 🎯 Objectives

- To construct a general tree in which a node can have any number of children.
- To count and display the leaf nodes (no children) and non-leaf nodes (one or more children).
- To display the actual values of the leaf and non-leaf nodes.
- To count the number of nodes at each level of the tree.
- To allow the user to query the children of a selected node.
- To understand pointers, recursion, tree traversal and dynamic memory allocation.

## ✨ Features

- Create the root and add children to any node.
- Display the tree structure with indentation (leaf nodes are marked).
- Display the actual leaf and non-leaf node values with their counts and the total number of nodes.
- Count the nodes at each level and show the height of the tree.
- Query the children of a selected node (leaf or non-leaf, number of children and their values).
- Load a ready-made sample tree for quick testing.
- Duplicate value checking and parent existence checking.
- Menu-driven user interface.

## 🛠️ Technologies Used

- *Programming Language:* C++
- *Data Structures:* General Tree (first-child, next-sibling), Array, Queue (array based)
- *Concepts:* Structures, Pointers, Recursion, Preorder and Level-order Traversal, Dynamic Memory Allocation
- *Platform:* Visual Studio Code / Code::Blocks / any compatible C++ compiler

## ⚙️ How It Works

1. The user selects an operation from the menu.
2. The root is created first, then children are added under any existing node. A new child is inserted as the last child of its parent.
3. To count leaf and non-leaf nodes, the tree is traversed in preorder. A node with no first child is a leaf node, otherwise it is a non-leaf node. The values are stored in two arrays and displayed with their counts.
4. To count nodes at each level, the tree is traversed level by level using a queue, and the number of nodes at every level is displayed.
5. To query a node, the tree is searched for the value and its children are displayed by moving through the first child and its siblings.

## 🧩 Data Structures Used

| Data Structure | Used For |
|---|---|
| General Tree (first child, next sibling) | Stores the tree nodes with any number of children |
| Array (100 values) | Stores the leaf node values and non-leaf node values |
| Queue (array based) | Level-order traversal to count nodes at each level |

### Node Structure

Each node of the tree contains:

- Data (integer value)
- First child pointer
- Next sibling pointer

## ▶️ How to Run the Project

1. Clone or download this repository.
2. Open the project folder in your preferred C++ IDE.
3. Compile the source code using a C++ compiler.

bash
g++ Leaf_NonLeaf_Node_Counting.cpp -o general_tree


4. Run the program.

*Windows:*

bash
general_tree.exe


*Linux/macOS:*

bash
./general_tree


## 📋 Menu Options

| Choice | Operation |
|---|---|
| 1 | Create root |
| 2 | Add child to a node |
| 3 | Display tree |
| 4 | Display leaf and non-leaf nodes (with count) |
| 5 | Count nodes at each level |
| 6 | Query children of a node |
| 7 | Load sample tree |
| 8 | Exit |

## 🖥️ Sample Output

After loading the sample tree (option 7):


----- Tree Structure -----
1
    |-- 2
        |-- 5  (leaf)
        |-- 6
            |-- 11  (leaf)
            |-- 12  (leaf)
    |-- 3
        |-- 7  (leaf)
    |-- 4
        |-- 8  (leaf)
        |-- 9  (leaf)
        |-- 10  (leaf)

Leaf nodes (7): 5 11 12 7 8 9 10
Non-leaf nodes (5): 1 2 6 3 4
Total nodes: 12

----- Nodes at Each Level -----
Level 0 : 1 node(s) -> 1
Level 1 : 3 node(s) -> 2 3 4
Level 2 : 6 node(s) -> 5 6 7 8 9 10
Level 3 : 2 node(s) -> 11 12
Height of tree (levels): 4

Node 4 is a NON-LEAF node with 3 child(ren): 8 9 10
Node 7 is a LEAF node. It has no children.


## 📚 Data Structure Operations

| Operation | Description | Time Complexity |
|---|---|---|
| Create Root | Creates the root node | O(1) |
| Add Child | Finds the parent, checks the value is unique and inserts the child at the end | O(n) |
| Display Tree | Prints all nodes in preorder with indentation | O(n) |
| Leaf and Non-Leaf Nodes | Visits every node and stores leaf and non-leaf values | O(n) |
| Count Nodes at Each Level | Level-order traversal using a queue | O(n) |
| Query Children | Searches the node and lists its children | O(n) |
| Load Sample Tree | Builds a fixed tree of 12 nodes | O(1) |

## ✅ Advantages

- A node can have any number of children, using only two pointers per node.
- Shows the actual leaf and non-leaf node values, not just the counts.
- Level-wise counting gives a clear view of the shape and height of the tree.
- The child query makes it easy to inspect any part of the tree.
- Demonstrates practical use of a tree, an array and a queue together.
- Memory of all nodes is freed when the program exits.

## ⚠️ Limitations

- The tree can hold a maximum of 100 nodes.
- Node values are integers and must be unique.
- The tree is lost when the program terminates, as file storage is not implemented.
- Searching for a node requires traversing the tree (linear time).
- A node cannot be deleted once it is added.
- The project is intended for educational purposes and is not production-ready.

## 🔮 Future Enhancements

- Add an option to delete a node or a subtree.
- Display the path from the root to a selected node.
- Show the height and the number of nodes of any selected subtree.
- Support string values (such as names) instead of only integers.
- Add file handling to save and load the tree.

## 🎓 Learning Outcomes

- Understand the first-child, next-sibling representation of a general tree.
- Learn preorder and level-order traversal of a tree.
- Understand the difference between leaf and non-leaf nodes.
- Develop practical C++ programming skills with pointers and recursion.
- Learn dynamic memory management by creating and freeing tree nodes.

## 👨‍💻 Author

Student Mini-Project — Data Structures and Algorithms (DSA)

## 📄 License

This project is intended for educational and academic purposes.
