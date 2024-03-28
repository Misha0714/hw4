#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;

//helper function to find the height 
 int height(Node* node) {
    
    if (node == nullptr) {
        return 0; 
    }
    else {
        int leftH = height(node->left); 
        int rightH = height(node->right);  
        if (leftH > rightH) {
            return leftH + 1; 
        }
        else {
            return rightH + 1; 
        }  
    }
}
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

    int right = height(root->right); 
    int left = height(root->left); 
  

    if(right!=left && root->right != nullptr && root->left!= nullptr) {
        return false; 
    }
    else {
        return equalPaths(root->left) && equalPaths(root->right);  
    }

}


