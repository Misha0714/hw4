#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
    virtual void insertfix(AVLNode<Key, Value>* parentNode, AVLNode<Key, Value>* node); 
    virtual void rotateLeft(AVLNode<Key, Value>* node);
    virtual void rotateRight(AVLNode<Key, Value>* node);
    virtual void removefix(AVLNode<Key, Value>* node, int diff);
    //Add helper functions here


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    
    //check if tree is empty 
     if(this->root_ == nullptr) {
       
        //set new-item as root 
        AVLNode<Key,Value>* newNode = new AVLNode<Key,Value>(new_item.first, new_item.second, nullptr);
        this->root_ = newNode; 
        newNode->setBalance(0); 

        return;
    }

    //Figure out where to insert the new node 
    //create parentNode and set it equal to nullptr 
    AVLNode<Key,Value>* parentNode = nullptr; 
    //create currentNode and set it equal to the root_ 
    AVLNode<Key,Value>* currentNode = static_cast<AVLNode<Key,Value>*>(this->root_); 
    //transverse through the list till you hit nullptr 
    while(currentNode != nullptr) {
        //set parentNode to currentNode to start comparison
        parentNode = currentNode;
        //if the current node's key is less than key value pair than have current equal left side now 
        if (new_item.first < currentNode->getKey()) {
            currentNode = currentNode->getLeft();
        } 
        //if the current node's key is greater than key value pair than have current equal right side now 
        else if (new_item.first > currentNode->getKey()) {
            currentNode = currentNode->getRight();
        } 

        else {
            // Key already exists, update the value
            currentNode->setValue(new_item.second);
            return;
        }
    }
    //create a new node once you find where you want to insert it  
    AVLNode<Key,Value>* newNode = new AVLNode<Key,Value>(new_item.first, new_item.second, parentNode);
    //decide where to set it based on if it is greater or less than
    //set newNode to be child 
    if (new_item.first < parentNode->getKey()) {
        parentNode->setLeft(newNode);
       
    } 
    else {
        parentNode->setRight(newNode);
        
    }

    if(parentNode->getBalance() == -1) {
        
        parentNode->setBalance(0); 
    }
    else if(parentNode->getBalance() == 1) {
        parentNode->setBalance(0); 
    }
    else if(parentNode->getBalance() == 0) {
        if(newNode == parentNode->getLeft()) {
            parentNode->setBalance(-1); 
        }
        else if(newNode == parentNode->getRight()) {
            parentNode->setBalance(1); 
        }
        insertfix(newNode->getParent(), newNode);
    }
}
/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    // Perform standard BST removal
    // Rebalance the tree starting from the root
    //find node

    //create a node with the key to remove using internal find 
    AVLNode<Key,Value>* nodeToRemove = (AVLNode<Key, Value>*)(this->internalFind(key));

     //if key not found, do nothing
    if (nodeToRemove == nullptr) {
        return;
    }

    // check for 2 children
    if(nodeToRemove->getLeft() != nullptr && nodeToRemove->getRight() != nullptr) {
        //get the predecessor of the node you want to remove
        Node<Key,Value>* pred = BinarySearchTree<Key,Value>::predecessor(nodeToRemove);
        //swap the node with the predecessor 
        nodeSwap(nodeToRemove, (AVLNode<Key, Value>*)pred);
        //delete that node 
        //delete nodeToRemove; 
    }

    //make a variable to keep track of difference. This amt will be added to update balance of parentNode
    int diff = 0; 
    //make a parentnode 
    AVLNode<Key,Value>* parentNode = nodeToRemove->getParent();

    if(parentNode != nullptr) {
        //if nodeToRemove is a left child set diff to 1 so right subtree has greater height
        if(nodeToRemove == parentNode->getLeft()) {
            diff = 1; 
         }
        //if nodeToRemove is a right child set diff to -1 so left subtree has greater height 
        else if(nodeToRemove == parentNode->getRight()) {
            diff = -1; 
        }
    }

    //Delete the node based on these cases 
    //Case 1: parent to be removed has no children
        if (nodeToRemove->getLeft() == nullptr && nodeToRemove->getRight() == nullptr) {
            //if the node to remove is the root than delete it and set root to nullptr 
            if (nodeToRemove == this->root_) {
                delete this->root_;
                this->root_ = nullptr;
            //get the node's parent and update it's left or right and then delete the node to remove  
            } else {
                Node<Key,Value>* parent = nodeToRemove->getParent();
                if (parent->getLeft() == nodeToRemove) {
                    parent->setLeft(nullptr);
                } else {
                    parent->setRight(nullptr);
                }
                delete nodeToRemove;
                nodeToRemove = nullptr; 
            }
        }
    // Case 2: Node to be removed has exactly one child

    //THERE IS A RIGHT NODE BUT NOT A LEFT NODE 
    else if(nodeToRemove->getLeft()==nullptr && nodeToRemove->getRight() != nullptr) {
    
        AVLNode<Key,Value>* child = nodeToRemove->getRight();  
        if (nodeToRemove == this->root_) {
            //update the root to be child 
            this->root_ = child;
            //set next to null 
            child->setParent(nullptr);
            delete nodeToRemove;
            nodeToRemove = nullptr; 
        
        } 
        else {
            AVLNode<Key,Value>* parent = nodeToRemove->getParent();
            // if nodeToRemove is a left child of its parent, then parent's left child becomes "child"
            if (nodeToRemove == parent->getLeft()) {
                parent->setLeft(child);
            }
            else if (nodeToRemove == parent->getRight()) {
                parent->setRight(child);
            }
            child->setParent(parent);
            delete nodeToRemove;
            nodeToRemove = nullptr; 
        }
    }
    //THERE IS A LEFT NODE BUT NOT A RIGHT NODE 
    else if(nodeToRemove->getLeft()!=nullptr && nodeToRemove->getRight() == nullptr) {
        AVLNode<Key,Value>* child = nodeToRemove->getLeft(); 
        if (nodeToRemove == this->root_) {
            //update the root to be the child 
            this->root_ = child;
            //set next to null 
            child->setParent(nullptr);
            delete nodeToRemove;
            nodeToRemove = nullptr; 
        }
         else {
            AVLNode<Key,Value>* parent = nodeToRemove->getParent();

            // if nodeToRemove is a left child of its parent, then parent's left child becomes "child"
            if (nodeToRemove == parent->getLeft()) {
                parent->setLeft(child);
            }
            else if (nodeToRemove == parent->getRight()) {
                parent->setRight(child);
            }
            
            child->setParent(parent);
            delete nodeToRemove;
            nodeToRemove = nullptr; 
        }
    }
    removefix(parentNode, diff);
}
template<class Key, class Value>
void AVLTree<Key, Value>::insertfix(AVLNode<Key, Value>* parentNode, AVLNode<Key, Value>* node) {
    //if parentNode or grandparent node is null then return 
    if (parentNode == nullptr || parentNode->getParent() == nullptr) {
        return; 
    }
    //create a grandparent node 
    AVLNode<Key,Value>* gParentNode = parentNode->getParent(); 
    //if parentnode is equal to the grandaparent node's LEFT child 
    if(parentNode == gParentNode->getLeft()) {
        //increase the grandparent's node by 1 
        gParentNode->setBalance(gParentNode->getBalance() - 1); 
        //if the balance equals 0 
        if (gParentNode->getBalance() == 0) {
            return; 
        }
        //if the balance equals -1 
        else if(gParentNode->getBalance() == -1) {
            //recurse 
            insertfix(gParentNode, parentNode); 
        }
        //if the balance equals -2 
        else if(gParentNode->getBalance() == -2) {
            //if it is a zig-zig
            if(node == parentNode->getLeft()) {
                rotateRight(gParentNode); 
                parentNode->setBalance(0);
                gParentNode->setBalance(0); 

            }
            //if it is a zig-zag
            else if(node == parentNode->getRight()) {
                rotateLeft(parentNode); 
                rotateRight(gParentNode); 
                //if node's balance is -1 
                if(node->getBalance() == -1) {
                    parentNode->setBalance(0);
                    gParentNode->setBalance(1); 
                    node->setBalance(0); 
                }
                //if node's balance is 0
                else if(node->getBalance() == 0) {
                    parentNode->setBalance(0);
                    gParentNode->setBalance(0); 
                    node->setBalance(0); 
                }
                //if node's balance is 1
                else if(node->getBalance() == 1) {
                    parentNode->setBalance(-1);
                    gParentNode->setBalance(0); 
                    node->setBalance(0); 
                }
            }
        }
    }
    else if(parentNode == gParentNode->getRight()) {
        //increase the grandparent's node by 1 
        gParentNode->setBalance(gParentNode->getBalance() + 1); 
        //if the balance equals 0 
        if (gParentNode->getBalance() == 0) {
            return; 
        }
        //if the balance equals -1 
        else if(gParentNode->getBalance() == 1) {
            //recurse 
            insertfix(gParentNode, parentNode); 
        }
        //if the balance equals -2 
        else if(gParentNode->getBalance() == 2) {
            //if it is a zig-zig
            if(node == parentNode->getRight()) {
                rotateLeft(gParentNode); 
                parentNode->setBalance(0);
                gParentNode->setBalance(0); 

            }
            //if it is a zig-zag
            else if(node == parentNode->getLeft()) {
                rotateRight(parentNode); 
                rotateLeft(gParentNode); 
                //if node's balance is -1 
                if(node->getBalance() == 1) {
                    parentNode->setBalance(0);
                    gParentNode->setBalance(-1); 
                    node->setBalance(0); 
                }
                //if node's balance is 0
                else if(node->getBalance() == 0) {
                    parentNode->setBalance(0);
                    gParentNode->setBalance(0); 
                    node->setBalance(0); 
                }
                //if node's balance is 1
                else if(node->getBalance() == -1) {
                    parentNode->setBalance(1);
                    gParentNode->setBalance(0); 
                    node->setBalance(0); 
                }
            }
        }
    }
}
template<class Key, class Value>
void AVLTree<Key, Value>::removefix(AVLNode<Key, Value>* node, int diff) {
    //if node is null return 
    if (node == nullptr) {
        return;
    }
    //set parent node 
    AVLNode<Key,Value>* parentNode = node->getParent(); 
    int ndiff = 0; 
    //if parentnode does not equal nullptr 
    if(parentNode != nullptr) {
        //if node is left child 
        if(node == parentNode->getLeft()) {
            //then set ndiff to 1 
            ndiff = 1; 
        }
        else if(node == parentNode->getRight()) {
            //else if it is the right child sest ndiff to -1 
            ndiff = -1; 
        }
    }
    //if diff equals -1 
    if (diff == -1) {
        //if node's balance 
        if(node->getBalance() + diff == -2) {
            //left subtree is taller 
            AVLNode<Key,Value>* tallerNode = node->getLeft(); 
            //zig-zig case 
            if (tallerNode->getBalance() == -1) {
                rotateRight(node); 
                node->setBalance(0); 
                tallerNode->setBalance(0); 
                removefix(parentNode, ndiff); 
            }
            //zig-zig case 
            else if(tallerNode->getBalance() == 0) {
                rotateRight(node); 
                node->setBalance(-1); 
                tallerNode->setBalance(1);
            }
            //zig-zag case 
            else if(tallerNode->getBalance() == 1) {
                AVLNode<Key,Value>* gParentNode = tallerNode->getRight(); 
                rotateLeft(tallerNode); 
                rotateRight(node); 
                if(gParentNode->getBalance() == 1) {
                    node->setBalance(0);
                    tallerNode->setBalance(-1);
                    gParentNode->setBalance(0);
                }
                else if(gParentNode->getBalance() == 0) {
                    node->setBalance(0);
                    tallerNode->setBalance(0);
                    gParentNode->setBalance(0);
                }
                else if(gParentNode->getBalance() == -1) {
                    node->setBalance(1);
                    tallerNode->setBalance(0);
                    gParentNode->setBalance(0);
                }
                removefix(parentNode, ndiff); 
            }
        }
        else if(node->getBalance() + diff == -1) {
            node->setBalance(-1);
        }
        else if(node->getBalance() + diff == 0) {
            node->setBalance(0);
            removefix(parentNode, ndiff); 
        }
    }
    //other case 
    else if (diff == 1) {
        if(node->getBalance() + 1 == 2) {
            AVLNode<Key,Value>* tallerNode = node->getRight(); 
            //zig-zig case 
            if (tallerNode->getBalance() == 1) {
                rotateLeft(node); 
                node->setBalance(0); 
                tallerNode->setBalance(0); 
                removefix(parentNode, ndiff); 
            }
            //zig-zig case 
            else if(tallerNode->getBalance() == 0) {
                rotateLeft(node); 
                node->setBalance(1); 
                tallerNode->setBalance(-1);
            }
            //zig-zag case 
            else if(tallerNode->getBalance() == -1) {
                AVLNode<Key,Value>* gParentNode = tallerNode->getLeft(); 
                rotateRight(tallerNode); 
                rotateLeft(node); 
                if(gParentNode->getBalance() == -1) {
                    node->setBalance(0);
                    tallerNode->setBalance(1);
                    gParentNode->setBalance(0);
                }
                else if(gParentNode->getBalance() == 0) {
                    node->setBalance(0);
                    tallerNode->setBalance(0);
                    gParentNode->setBalance(0);
                }
                else if(gParentNode->getBalance() == 1) {
                    node->setBalance(-1);
                    tallerNode->setBalance(0);
                    gParentNode->setBalance(0);
                }
                removefix(parentNode, ndiff); 
            }
        }
        else if(node->getBalance() + diff == 1) {
            node->setBalance(1);
        }
        else if(node->getBalance() + diff == 0) {
            node->setBalance(0);
            removefix(parentNode, ndiff); 
        }
    }

}
template<class Key, class Value>

void AVLTree<Key, Value>::nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* node) {
    AVLNode<Key, Value>* pivot = node->getRight();
    if(pivot != nullptr) {
        node->setRight(pivot->getLeft());

        if (pivot->getLeft() != nullptr) {
            pivot->getLeft()->setParent(node);
        }

        pivot->setParent(node->getParent());

        if (node->getParent() == nullptr) {
            this->root_ = pivot;
        } else if (node == node->getParent()->getLeft()) {
            node->getParent()->setLeft(pivot);
        } else {
            node->getParent()->setRight(pivot);
        }

        pivot->setLeft(node);
        node->setParent(pivot);
        }
 }

template<class Key, class Value>
//segfault here 
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* node) {
    AVLNode<Key, Value>* pivot = node->getLeft();

    if(pivot != nullptr) {
        node->setLeft(pivot->getRight());
        if (pivot->getRight() != nullptr) {
            pivot->getRight()->setParent(node);
        }

        pivot->setParent(node->getParent());

        if (node->getParent() == nullptr) {
            this->root_ = pivot;
        } else if (node == node->getParent()->getRight()) {
            node->getParent()->setRight(pivot);
        } else {
            node->getParent()->setLeft(pivot);
        }

        pivot->setRight(node);
        node->setParent(pivot);
    }
}




#endif
