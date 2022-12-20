#include "equal-paths.h"
#include <iostream>
using namespace std;


bool equalPaths_helper (Node* root, int& firstLeafDepth, int levelCounter); //helper function

bool equalPaths(Node * root)
{
    // Add your code below
    int firstLeafDepth=0;
    int levelCounter=0;;
    return (equalPaths_helper(root,firstLeafDepth,levelCounter) ); 
}
bool equalPaths_helper (Node* root, int& firstLeafDepth, int levelCounter)
{
    if(root==nullptr )
    {
        return true;
    }
    else if(root->right==nullptr && root->left==nullptr) //if it's a leaf node
    {
        if(firstLeafDepth==0) //first leaf found
        {
            firstLeafDepth=levelCounter; //depth of first leaf node found
            return true;
        }
        else if( (firstLeafDepth -levelCounter)!=0) //if the height difference of the first leaf node found and other leaf nodes is not 0
        {
            return false; 
        }
        return true;
    }
    else
    {
        bool left =  equalPaths_helper(root->left,firstLeafDepth,levelCounter+1);
        bool right =  equalPaths_helper(root->right,firstLeafDepth,levelCounter+1);
        if(left==true && right==true) //if both left and right subtrees have equal paths
        {
            return true;
        }
        return false;
    }
}

// int equalPaths_helper(Node* root);
//  bool equalPaths(Node * root)
// {
//     // TODO
//     return ( !(equalPaths_helper(root)==-1));

// }

// int equalPaths_helper(Node* root)
// {
//     if(root==nullptr)
//     {
//         return 0;
//     }
//     int leftChildHeight = equalPaths_helper(root->left);
//     int rightChildHeight =equalPaths_helper(root->right);

//     if((abs(leftChildHeight - rightChildHeight) !=0 ) || (rightChildHeight==-1 || leftChildHeight==-1))
//     {
//         return -1; //if not balanced return -1
//     }
//     return 1+max(leftChildHeight, rightChildHeight) ; // Return Height
// }