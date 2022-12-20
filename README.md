# BST-and-AVL-from-scratch
Implemented a BST (Binary Search Tree) and Balanced Binary Search Tree (AVL Tree) in C++ from scratch where:

- A Templated Node class is defined inside the header file of BST class to be used for a node in the search tree. The getter functions of the Node class are virtual so that they can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees. 
- Inside the BST class, I have also implemented a nested Iterator class from scratch which is used to traverse the contents of the BST. 
- The AVL Tree inherits the template Node class defined inside the BST. 
- AVL Tree has an optimized efficiency of O(logn) for insertion, removal and find operations.
