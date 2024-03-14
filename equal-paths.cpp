#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int depth(Node* root) {
    int right = 0; 
    int left = 0; 
    if(root == NULL) { 
        return 0; 
    }
    depth(root->left); 
    left+=1; 
    depth(root->right); 
    right+=1; 


}

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

    if(right==left && leftPath && rightPath) {
        reutrn true; 
    }
    else [
        return false; 
    ]


}

