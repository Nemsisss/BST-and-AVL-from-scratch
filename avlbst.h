#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
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
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
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
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
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

    // Add helper functions here
    void rotateLeft(AVLNode<Key,Value>* parent);
    void rotateRight(AVLNode<Key,Value>* parent);
    bool isRightChild( AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node);
    bool isLeftChild( AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node);
    void insertFix( AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node);
    void removeFix( AVLNode<Key,Value>* node, char diff);
    bool isZigZig ( AVLNode<Key,Value>* grandParent,AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node);
    bool isZigZag ( AVLNode<Key,Value>* grandParent,AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node);
};


/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item) //O(log n)
{
    // TODO
    if(this->root_==nullptr) //if it's the first node
    {
        this->root_= new AVLNode<Key, Value>(new_item.first,new_item.second,nullptr) ; //balance is set to zero in constructor
    }
    else //if root is not nullptr
    {
         if( this->internalFind(new_item.first)!=nullptr) //if key already exists , O(h) i.e. O(logn)
         {
            this->internalFind(new_item.first)->setValue(new_item.second);
         }    
         else //if key does not exist
         {
            Node<Key,Value>* temp= this->root_;
            Node<Key, Value>* newNode= new AVLNode<Key, Value>(new_item.first, new_item.second,nullptr) ; //balance is set to zero in constructor
            while(temp!=nullptr) // loop's runtime is O(h) i.e. O(logn)
            {
                if(temp->getKey()> newNode->getKey())
                {
                    if(temp->getLeft()==nullptr) 
                    {
                        newNode->setParent(temp);
                        temp->setLeft(newNode);
                        break; //stop looping once inserted
                    }
                    temp=temp->getLeft();
                }
                else if(temp->getKey() < newNode->getKey())
                {
                    if(temp->getRight()==nullptr)
                    {
                        newNode->setParent(temp);
                        temp->setRight(newNode);
                        break; //stop looping once inserted
                    }
                    temp=temp->getRight();
                }
            }
            AVLNode<Key,Value>* newNodeParent= static_cast<AVLNode<Key,Value>*>(newNode->getParent());
            if(newNodeParent->getBalance()==-1)
            {
                newNodeParent->setBalance(0);
            }
            else if(newNodeParent->getBalance()==1)
            {
                newNodeParent->setBalance(0);
            }
            else if(newNodeParent->getBalance()==0)
            {
                if( isLeftChild(newNodeParent, static_cast<AVLNode<Key,Value>*>(newNode) ))
                {
                    newNodeParent->setBalance(-1);
                }
                else if(isRightChild(newNodeParent, static_cast<AVLNode<Key,Value>*>(newNode)))
                {
                    newNodeParent->setBalance(1);
                }
                insertFix(newNodeParent, static_cast<AVLNode<Key,Value>*> (newNode)); //outside the while loop
            }  
        }   
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key) // O(logn)
{
    // TODO
    Node<Key, Value>* curr= this->internalFind(key); //O(h) i.e. O(logn)
    Node<Key, Value>* temp;
    char diff;
    if(curr==nullptr) //if the key does not exist or the tree is empty
    {
        return;
    }
    Node<Key, Value>* parent=curr->getParent();
    if(curr->getRight()==nullptr && curr->getLeft()==nullptr) //the node is a leaf node, has 0 children
    {
        if(parent==nullptr) //if this is the only node in the tree
        {
            this->root_=nullptr;
        }
        else if(parent->getRight()==curr) //if the leaf node is a right child
        {
            parent->setRight(nullptr);
            diff= -1;
        }
        else if(parent->getLeft()==curr) //if the leaf node is a left child
        {
            parent->setLeft(nullptr);
            diff= 1;
        }
    }
    else if(curr->getRight()==nullptr && curr->getLeft()!=nullptr) //if the node has one left child only
    {
        temp=curr->getLeft();
        temp->setParent(parent);
        if(parent==nullptr)//if the newly promoted node is the root
        {
            this->root_=temp;
        }
         else if(parent->getRight()==curr) //if the node is a right child
        {
            parent->setRight(temp);
            diff= -1;
        }
        else if(curr->getParent()->getLeft()==curr) //if the node is a left child
        {
            parent->setLeft(temp);
            diff=1;
        }
    }
    else if(curr->getRight()!=nullptr && curr->getLeft()==nullptr) //if the node has a right child
    {
        temp=curr->getRight();
        temp->setParent(parent);
        if(parent==nullptr)//if the newly promoted node is the root
        {
            this->root_=temp;
        }
        else if(parent->getRight()==curr) //if the node is a right child
        {
            parent->setRight(temp);
            diff= -1;
        }
        else if(parent->getLeft()==curr) //if the node is a left child
        {
            parent->setLeft(temp);
            diff= 1;
        }
    }
     else if(curr->getRight()!=nullptr && curr->getLeft()!=nullptr) //if the node has both left and right children
    {
        Node<Key, Value>* pred = this->predecessor(curr); //O(h) i.e. O(logn)
        nodeSwap( static_cast<AVLNode<Key,Value>*>(curr), static_cast<AVLNode<Key,Value>*>(pred)); //O(1)
        temp=curr->getParent();
        if(curr->getRight()==nullptr && curr->getLeft()==nullptr) //the node is a leaf node, has 0 children
        {
            if(temp->getLeft()== curr)
            {
                temp->setLeft(nullptr);
                diff=1;
            }
            else if(temp->getRight()== curr)
            {
                temp->setRight(nullptr);
                diff=-1;
            }
        }
        else if(curr->getRight()==nullptr && curr->getLeft()!=nullptr) //node to be removed has a left child
        {
            if(temp->getRight()== curr)
            {
                temp->setRight(curr->getLeft());
                diff=-1;
            }
            else if(temp->getLeft()== curr)
            {
                temp->setLeft(curr->getLeft());
                diff=1;
            }
            curr->getLeft()->setParent(temp);
        }
        else if(curr->getRight()!=nullptr && curr->getLeft()==nullptr) //node to be removed has a right child
        {

             if(temp->getLeft()== curr)
            {
                temp->setLeft(curr->getRight());
                diff=1;
            }
            else if(temp->getRight()==curr)
            {
                temp->setRight(curr->getRight());
                diff=-1;
            }
            curr->getRight()->setParent(temp);
        }
        parent=temp;
    }
    delete curr;
    curr=nullptr;
    removeFix(static_cast<AVLNode<Key,Value>*>(parent), diff);
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isRightChild( AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node) //O(1)
{
    if(parent->getRight()== node)
    {
        return true;
    }
    return false;
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isLeftChild( AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node) //O(1)
{
    if(parent->getLeft()== node)
    {
        return true;
    }
    return false;
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* parent) //parent is right child of grandparent , O(1)
{
    AVLNode<Key,Value>* grandParent= parent->getParent();
    AVLNode<Key,Value>* oldRightChildOfParent= parent->getRight();
    AVLNode<Key,Value>* oldLeftChildOfParentsRightChild = oldRightChildOfParent->getLeft();
    if(grandParent==nullptr) // if grandparent is  nullptr
    {
        this->root_= oldRightChildOfParent;
    }
    else if(isLeftChild(grandParent, parent) )
    {
        grandParent->setLeft(oldRightChildOfParent);
    }
    else if(isRightChild(grandParent,parent))
    {
        grandParent->setRight(oldRightChildOfParent);
    }
    if(oldLeftChildOfParentsRightChild!=nullptr)
    {
        oldLeftChildOfParentsRightChild->setParent(parent);
    }
    parent->setParent(oldRightChildOfParent);
    oldRightChildOfParent->setParent(grandParent);
    oldRightChildOfParent->setLeft(parent);
    parent->setRight(oldLeftChildOfParentsRightChild);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* parent) //parent is left child of grandparent, O(1)
{
    AVLNode<Key,Value>* grandParent= parent->getParent();
    AVLNode<Key,Value>* oldLeftChildOfParent= parent->getLeft();
    AVLNode<Key,Value>* oldRightChildOfParentsLeftChild = oldLeftChildOfParent->getRight();
    if(grandParent==nullptr) // if grandparent's is  nullptr
    {
        this->root_= oldLeftChildOfParent;
    }
    else if(isLeftChild(grandParent, parent) )
    {
        grandParent->setLeft(oldLeftChildOfParent);
    }
    else if(isRightChild(grandParent,parent))
    {
        grandParent->setRight(oldLeftChildOfParent);
    }
    if(oldRightChildOfParentsLeftChild!=nullptr)
    {
        oldRightChildOfParentsLeftChild->setParent(parent);
    }
    parent->setParent(oldLeftChildOfParent);
    oldLeftChildOfParent->setParent(grandParent);
    oldLeftChildOfParent->setRight(parent);
    parent->setLeft(oldRightChildOfParentsLeftChild);
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix( AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node)
{
    if(parent==nullptr || parent->getParent()==nullptr)
    {
        return;
    }
    AVLNode<Key,Value>* grandParentOfP= parent->getParent();
    if(isLeftChild(grandParentOfP, parent))
    {
        grandParentOfP->setBalance( grandParentOfP->getBalance()-1); //update grandParent's balance
        if(grandParentOfP->getBalance()==0) //case 1
        {
            return;
        }
        else if(grandParentOfP->getBalance()==-1) //case 2
        {
            insertFix(grandParentOfP, parent);
        }
        else if(grandParentOfP->getBalance()==-2) //case 3
        {
            if(isZigZig(grandParentOfP, parent, node)) //if left zigzig
            {
                rotateRight(grandParentOfP);
                parent->setBalance(0);
                grandParentOfP->setBalance(0);
            }
            else if(isZigZag(grandParentOfP,parent, node)) //if < zigzag, i.e. left-right
            {
                rotateLeft(parent);
                rotateRight( grandParentOfP);
                if(node->getBalance()==-1)
                {
                    parent->setBalance(0);
                    grandParentOfP->setBalance(1);
                    node->setBalance(0);
                }
                else if(node->getBalance()==0)
                {
                    parent->setBalance(0);
                    grandParentOfP->setBalance(0);
                    node->setBalance(0);
                }
                else if(node->getBalance()==1)
                {
                    parent->setBalance(-1);
                    grandParentOfP->setBalance(0);
                    node->setBalance(0);
                }
            }
        }
    }
    else if(isRightChild(grandParentOfP, parent))
    {
        grandParentOfP->setBalance(grandParentOfP->getBalance()+1);
        if(grandParentOfP->getBalance()==0) //case 1
        {
            return; 
        }
        else if (grandParentOfP->getBalance()==1) //case 2
        {
            insertFix(grandParentOfP, parent); //recurse
        }
        else if(grandParentOfP->getBalance()==2) //case 3
        {
            if(isZigZig(grandParentOfP, parent, node))
            {
                rotateLeft(grandParentOfP);
                parent->setBalance(0);
                grandParentOfP->setBalance(0);
            }
            else if(isZigZag(grandParentOfP, parent, node))
            {
                rotateRight(parent);
                rotateLeft(grandParentOfP);
                if(node->getBalance()==1)
                {
                    parent->setBalance(0);
                    grandParentOfP->setBalance(-1);
                    node->setBalance(0);
                }
                else if(node->getBalance()==0)
                {
                    parent->setBalance(0);
                    grandParentOfP->setBalance(0);
                    node->setBalance(0);
                }
                else if(node->getBalance()==-1)
                {
                    parent->setBalance(1);
                    grandParentOfP->setBalance(0);
                    node->setBalance(0);
                }

            }
        }
    }

}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix( AVLNode<Key,Value>* node, char diff)
{
    if(node==nullptr)
    {
        return;
    }
    else
    {
        AVLNode<Key,Value>* parent= node->getParent();
        char ndiff;
        AVLNode<Key,Value>* child;
        AVLNode<Key,Value>* grandchild;
        if(parent!=nullptr)
        {
            if(isLeftChild(parent, node))
            {
                ndiff=1;
            }
            else if(isRightChild(parent, node))
            {
                ndiff=-1;
            }
        }
        if(diff==-1) //assume diff== -1
        {
            if(node->getBalance()+diff== -2) 
            {
                child= node->getLeft(); //taller child
                if(child->getBalance()==-1) //zigzig case
                {
                    rotateRight(node);
                    node->setBalance(0);
                    child->setBalance(0);
                    removeFix(parent,ndiff);
                }
                else if(child->getBalance()==0) //zigzig case
                {
                    rotateRight(node);
                    node->setBalance(-1);
                    child->setBalance(1);
                    return;
                }
                else if(child->getBalance()==1) //zigzag case
                {
                    grandchild= child->getRight();
                    rotateLeft(child);
                    rotateRight(node);
                    if(grandchild->getBalance()==1)
                    {
                        node->setBalance(0);
                        child->setBalance(-1);
                        grandchild->setBalance(0);
                    }
                    else if(grandchild->getBalance()==0)
                    {
                        node->setBalance(0);
                        child->setBalance(0);
                        grandchild->setBalance(0);
                    }
                    else if(grandchild->getBalance()==-1)
                    {
                        node->setBalance(1);
                        child->setBalance(0);
                        grandchild->setBalance(0);
                    }
                    removeFix(parent, ndiff);
                }

            }
            else if(node->getBalance()+diff== 2)
            {
                child= node->getRight(); //taller child
                if(child->getBalance()== 1) //zigzig case
                {
                    rotateLeft(node);
                    node->setBalance(0);
                    child->setBalance(0);
                    removeFix(parent,ndiff);
                }
                else if(child->getBalance()==0) //zigzig case
                {
                    rotateLeft(node);
                    node->setBalance(1);
                    child->setBalance(-1);
                    return;
                }
                else if(child->getBalance()==1) //zigzag case
                {
                    grandchild= child->getLeft();
                    rotateRight(child);
                    rotateLeft(node);
                    if(grandchild->getBalance()== -1)
                    {
                        node->setBalance(0);
                        child->setBalance(1);
                        grandchild->setBalance(0);
                    }
                    else if(grandchild->getBalance()==0)
                    {
                        node->setBalance(0);
                        child->setBalance(0);
                        grandchild->setBalance(0);
                    }
                    else if(grandchild->getBalance()==1)
                    {
                        node->setBalance(-1);
                        child->setBalance(0);
                        grandchild->setBalance(0);
                    }
                    removeFix(parent, ndiff);
                }
            }
            else if(node->getBalance()+diff == -1)
            {
                node->setBalance(-1);
                return;
            }
            else if(node->getBalance()+diff ==0)
            {
                node->setBalance(0);
                removeFix(parent, ndiff);
            }
        }
        else if(diff==1)
        {
            if(node->getBalance()+diff== 2) 
            {
                child= node->getRight(); //taller child
                if(child->getBalance()==1) //zigzig case
                {
                    rotateLeft(node);
                    node->setBalance(0);
                    child->setBalance(0);
                    removeFix(parent,ndiff);
                }
                else if(child->getBalance()==0) //zigzig case
                {
                    rotateLeft(node);
                    node->setBalance(1);
                    child->setBalance(-1);
                    return;
                }
                else if(child->getBalance()== -1) //zigzag case
                {
                    grandchild= child->getLeft();
                    rotateRight(child);
                    rotateLeft(node);
                    if(grandchild->getBalance()== -1)
                    {
                        node->setBalance(0);
                        child->setBalance(1);
                        grandchild->setBalance(0);
                    }
                    else if(grandchild->getBalance()==0)
                    {
                        node->setBalance(0);
                        child->setBalance(0);
                        grandchild->setBalance(0);
                    }
                    else if(grandchild->getBalance()== 1)
                    {
                        node->setBalance(-1);
                        child->setBalance(0);
                        grandchild->setBalance(0);
                    }
                    removeFix(parent, ndiff);
                }

            }
            else if(node->getBalance()+diff== -2) //case 1
            {
                child= node->getLeft(); //taller child
                if(child->getBalance()==-1) //zigzig case
                {
                    rotateRight(node);
                    node->setBalance(0);
                    child->setBalance(0);
                    removeFix(parent,ndiff);
                }
                else if(child->getBalance()==0) //zigzig case
                {
                    rotateRight(node);
                    node->setBalance(-1);
                    child->setBalance(1);
                    return;
                }
                else if(child->getBalance()==1) //zigzag case
                {
                    grandchild= child->getRight();
                    rotateLeft(child);
                    rotateRight(node);
                    if(grandchild->getBalance()==1)
                    {
                        node->setBalance(0);
                        child->setBalance(-1);
                        grandchild->setBalance(0);
                    }
                    else if(grandchild->getBalance()==0)
                    {
                        node->setBalance(0);
                        child->setBalance(0);
                        grandchild->setBalance(0);
                    }
                    else if(grandchild->getBalance()==-1)
                    {
                        node->setBalance(1);
                        child->setBalance(0);
                        grandchild->setBalance(0);
                    }
                    removeFix(parent, ndiff);
                }

            }
            else if(node->getBalance()+diff == 1)
            {
                node->setBalance(1);
                return;
            }
            else if(node->getBalance()+diff ==0)
            {
                node->setBalance(0);
                removeFix(parent, ndiff);
            }
        }
    }
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isZigZig ( AVLNode<Key,Value>* grandParent,AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node) //O(1)
{
    if( (isRightChild(grandParent, parent) && isRightChild(parent, node)) || (isLeftChild(grandParent, parent) && isLeftChild(parent, node)))
    {
        return true;
    }
    return false;
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isZigZag ( AVLNode<Key,Value>* grandParent,AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node) //O(1)
{
    if( (isRightChild(grandParent, parent) && isLeftChild(parent, node)) || (isLeftChild(grandParent, parent) && isRightChild(parent, node)))
    {
        return true;
    }
    return false;
}

#endif
