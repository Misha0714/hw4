#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool equalPaths(Node * root)
{
    // Add your code below
    //if root equals null 
    if (root == NULL) {
        return true; 
    }
    //if root does not have a left or right node 
    if (root->left == NULL && root->right == NULL) {
        return true; 
    }
    // Check if the root has both left and right children
    bool hasLeft = root->left != NULL;
    bool hasRight = root->right != NULL;
    //count for right and left to keep track of path 
    int right = 0; 
    int left = 0; 
    //call equalPaths on left side of tree 
    bool leftPath = equalPaths(root->left);  
    //call equalPaths on left side of tree 
    bool rightPath = equalPaths(root->right); 
    
    if (root->right != nullptr) {
        right++; 
    }
    if (root->left!= nullptr) {
        left++; 
    }
    if(right==left && (leftPath && rightPath) && (hasLeft && hasRight)) {
        return true; 
    }
    else {
        return false; 
    }


}

