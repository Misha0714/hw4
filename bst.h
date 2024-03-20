#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{
   

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;
 
    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
private: 
    //helper functions 
    void clearHelper(Node<Key, Value>* node); 
    bool isBalancedHelper(Node<Key, Value>* node) const; 
    int getHeight(Node<Key, Value>* node) const; 

public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    static Node<Key, Value>* successor(Node<Key, Value>* current); 
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr; 

    

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_= NULL; 


}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    //return a boolean 
    if(this->current_ == rhs.current_) {
        return true; 
    }
    else {
        return false; 
    }

}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    //return a boolean 
    if(this->current_ != rhs.current_) {
        return true; 
    }
    else {
        return false; 
    }


}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    //Should return reference to itself - preincrement 
    this->current_ = successor(this->current_); 
    return *this; 


}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear(); 


}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{

    // TODO
    //If the tree is empty then create a new node and set the values to what was given 
    if(empty()) {
        root_ = new Node<Key,Value>(keyValuePair.first, keyValuePair.second, nullptr);
        return;
    }
    
    //create parentNode and set it equal to nullptr 
    Node<Key,Value>* parentNode = nullptr; 
    //create currentNode and set it equal to the root_ 
    Node<Key,Value>* currentNode = root_; 
    //transverse through the list till you hit nullptr 
    while(currentNode != nullptr) {
        //set parentNode to currentNode to start comparison
        parentNode = currentNode;
        //if the current node's key is less than key value pair than have current equal left side now 
        if (keyValuePair.first < currentNode->getKey()) {
            currentNode = currentNode->getLeft();
        } 
        //if the current node's key is greater than key value pair than have current equal right side now 
        else if (keyValuePair.first > currentNode->getKey()) {
            currentNode = currentNode->getRight();
        } 

        else {
            // Key already exists, update the value
            currentNode->setValue(keyValuePair.second);
            return;
        }
    }
    //create a new node 
    Node<Key,Value>* newNode = new Node<Key,Value>(keyValuePair.first, keyValuePair.second, parentNode);
    //decide where to set it based on if it is greater or less than 
    if (keyValuePair.first < parentNode->getKey()) {
        parentNode->setLeft(newNode);
    } 
    else {
        parentNode->setRight(newNode);
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{

    //find the key to remove 
    Node<Key,Value>* nodeToRemove = internalFind(key);

     //if not found, do nothing
    if (nodeToRemove == nullptr) {
        return;
    }

    // check if 2 children
    if(nodeToRemove->getLeft() != nullptr && nodeToRemove->getRight() != nullptr) {
        //get the predecessor of the node you want to remove
        Node<Key,Value>* pred = predecessor(nodeToRemove);
        //swap the node with the predecessor 
        nodeSwap(nodeToRemove, pred);
        //delete nodeToRemove; 

    }

    // Case 1: Node to be removed has no children
    if (nodeToRemove->getLeft() == nullptr && nodeToRemove->getRight() == nullptr) {
        //if the node to remove is the root than delete it and set root to nullptr 
        if (nodeToRemove == root_) {
            delete root_;
            root_ = nullptr;
        //get the node's parent and update it's left or right and then delete the node to remove  
        } else {
            Node<Key,Value>* parent = nodeToRemove->getParent();
            if (parent->getLeft() == nodeToRemove) {
                parent->setLeft(nullptr);
            } else {
                parent->setRight(nullptr);
            }
            delete nodeToRemove;
        }
    }
    // Case 2: Node to be removed has exactly one child

    //THERE IS A RIGHT NODE BUT NOT A LEFT NODE 
    else if(nodeToRemove->getLeft()==nullptr && nodeToRemove->getRight() != nullptr) {
    
        Node<Key,Value>* child = nodeToRemove->getRight();  
        if (nodeToRemove == root_) {
            //update the root to be child 
            root_ = child;
            //set next to null 
            child->setParent(nullptr);
            delete nodeToRemove;
        
        } 
        else {
            Node<Key,Value>* parent = nodeToRemove->getParent();
            // if nodeToRemove is a left child of its parent, then parent's left child becomes "child"
            if (nodeToRemove == parent->getLeft()) {
                parent->setLeft(child);
            }
            else if (nodeToRemove == parent->getRight()) {
                parent->setRight(child);
            }
            child->setParent(parent);
            delete nodeToRemove;
        }
    }
    //THERE IS A LEFT NODE BUT NOT A RIGHT NODE 
    else if(nodeToRemove->getLeft()!=nullptr && nodeToRemove->getRight() == nullptr) {
        Node<Key,Value>* child = nodeToRemove->getLeft(); 
        if (nodeToRemove == root_) {
            //update the root to be the child 
            root_ = child;
            //set next to null 
            child->setParent(nullptr);
            delete nodeToRemove;
        }
         else {
            Node<Key,Value>* parent = nodeToRemove->getParent();

            // if nodeToRemove is a left child of its parent, then parent's left child becomes "child"
            if (nodeToRemove == parent->getLeft()) {
                parent->setLeft(child);
            }
            else if (nodeToRemove == parent->getRight()) {
                parent->setRight(child);
            }
            // if nodeToRemove is a right child of its parent, then parent's right child becomes "child"
            // parent->getLeft() == nodeToRemove; 
            // parent->setLeft(child);
            child->setParent(parent);
            delete nodeToRemove;
        }
    }

}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{

    // TODO
     if (current == nullptr) {
        return nullptr; // Edge case: If the current node is nullptr, return nullptr
    }

    // If the current node has a left child, the predecessor is the right most node in the left subtree
    if (current->getLeft() != nullptr) {
        Node<Key, Value>* pred = current->getLeft();
        while (pred->getRight() != nullptr) {
            pred = pred->getRight();
        }
        return pred;
    }

    // If the current node does not have a left child, the predecessor is an ancestor whose right child is also an ancestor
    Node<Key, Value>* parent = current->getParent();
    while (parent != nullptr && current == parent->getLeft()) {
        current = parent;
        parent = parent->getParent();
    }
    return parent;
    
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{

    // TODO
     if (current == nullptr) {
        return nullptr; // Edge case: If the current node is nullptr, return nullptr
    }

    // If the current node has a right child, the successor is the left most node in the left subtree
    if (current->getRight() != nullptr) {
        Node<Key, Value>* succ = current->getRight();
        while (succ->getLeft() != nullptr) {
            succ = succ->getLeft();
        }
        return succ;
    }

    // If the current node does not have a right child, the successor is an ancestor whose right child is also an ancestor
    Node<Key, Value>* parent = current->getParent();
    while (parent != nullptr && current == parent->getRight()) {
        current = parent;
        parent = parent->getParent();
    }
    return parent;
    
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO 
    // Call a recursive helper function to delete nodes starting from the root
    clearHelper(root_);
    // After clearing the tree, reset the root to nullptr
    root_ = nullptr; 
    
    
}
//Should I do a helper function?  
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* node) {
    //given the last node of the tree 
    if (node == nullptr) {
        return; // Base case: If the node is nullptr, return
    }

    // Recursively delete nodes in the left subtree
    clearHelper(node->getLeft());
    // Recursively delete nodes in the right subtree
    clearHelper(node->getRight());
    // Delete the nodes 
    delete node;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    Node<Key, Value>* current = root_;

    // Traverse to the leftmost node
    while (current != nullptr && current->getLeft() != nullptr) {
        current = current->getLeft();
    }

    // Return the leftmost node (smallest node)
    return current;
    
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value>* current = root_;
    

    // Traverse the tree until a matching node is found or until we reach a leaf node
    while (current != nullptr) {
        if (key == current->getKey()) {
            return current; // Found the node with the given key
        } else if (key < current->getKey()) {
            current = current->getLeft(); // Move to the left subtree
        } else {
            current = current->getRight(); // Move to the right subtree
        }
    }

    // If the key is not found, return nullptr
    return nullptr;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
     return isBalancedHelper(root_);
}
//Made a helper function 
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalancedHelper(Node<Key, Value>* node) const {
    if (node == nullptr) {
        return true; // An empty subtree is considered balanced
    }

    // Check the height difference between the left and right subtrees
    int leftHeight = getHeight(node->getLeft());
    int rightHeight = getHeight(node->getRight());
    if ( abs(leftHeight - rightHeight) > 1) {
        return false; // Height difference exceeds 1, tree is not balanced
    }

    // Recursively check the balance of left and right subtrees
    return isBalancedHelper(node->getLeft()) && isBalancedHelper(node->getRight());
}
//Made a height function 
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::getHeight(Node<Key, Value>* node) const {
    if (node == nullptr) {
        return 0; // Height of an empty subtree is 0
    }

    // Recursively calculate the height of the subtree
    int leftHeight = getHeight(node->getLeft());
    int rightHeight = getHeight(node->getRight());

    // Return the maximum height of the left and right subtrees, plus 1 (for the current node)
    return 1 + std::max(leftHeight, rightHeight);
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
