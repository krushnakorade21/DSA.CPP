Leaf and Non-Leaf Node Counting in a General Tree

Problem Statement
Write a C++ program to construct a general tree and count and display its leaf nodes and non-leaf nodes.

Objective
To construct a general tree and count and display its leaf nodes and non-leaf nodes using a preorder traversal.

Algorithm

Start.
Define a node structure containing data, a pointer to the first child, and a pointer to the next sibling.
Initialize the root of the tree as NULL, and set leafCount = 0 and nonLeafCount = 0.
Construct the general tree:
Read the root value and create the root node.
For each node, read the number of children.
Create each child node and link it to its parent (first child, then next siblings).
Repeat for every child until all nodes are created.
Traverse the tree starting from the root (Preorder Traversal):
Visit the current node.
If the node has no child (firstChild = NULL), it is a leaf node: increase leafCount and store its data in the leaf list.
Otherwise, it is a non-leaf node: increase nonLeafCount and store its data in the non-leaf list.
Repeat the same for the first child and then for each of its siblings.
Display all the leaf nodes and the value of leafCount.
Display all the non-leaf nodes and the value of nonLeafCount.
Display the total number of nodes (leafCount + nonLeafCount).
Stop.

Time Complexity

Tree construction: O(n).
Counting leaf and non-leaf nodes (Preorder traversal): O(n).
Displaying leaf and non-leaf nodes: O(n).

Space Complexity

Tree storage: O(n).
Recursive traversal stack: O(h), where h is the height of the tree.
Leaf and non-leaf lists: O(n).

Technologies Used

Programming Language: C++
Data Structure: General Tree (first-child, next-sibling representation)
Traversal Technique: Preorder Traversal

Author
Student Name: [Your Name]

I left the author name as a placeholder because I’m not sure the name in your BST page is yours, so type your own name there. The steps, complexity and tree representation are the same as the algorithm, flowchart and complexity page I made earlier for this topic. I can also turn this into a PDF in the same style as your BST pages.
