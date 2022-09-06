
#include "bst.h"

#include <iostream>
#include <queue>
#include <stdexcept>
#include <algorithm>


BinarySearchTree::Node::Node(int val) : value(val), parent(nullptr), left(nullptr), right(nullptr), height(1)  {}


BinarySearchTree::Node::~Node() {

    // std::cout << "Node with " << value << " deleted" << std::endl;
}


BinarySearchTree::BinarySearchTree() : root(nullptr), size(0) {}


BinarySearchTree::~BinarySearchTree() {

    std::queue<Node*> nodeQueue;

    if (root != nullptr) {

        nodeQueue.push(root);
    }

    while (! nodeQueue.empty() ) {

        Node* topNode = nodeQueue.front();

        if (topNode->left != nullptr) {

            nodeQueue.push(topNode->left);
        }

        if (topNode->right != nullptr) {

            nodeQueue.push(topNode->right);
        }


        delete topNode;

        nodeQueue.pop();

    }
}

BinarySearchTree::Node* BinarySearchTree::Insert(int val) {


    if (root == nullptr) {

        root = new Node(val);
        ++size;

        return root;
    }


    Node* currentNode = root;

    while ( true ) {

        if (currentNode->value == val) {

            return currentNode;
        }

        else if (currentNode->value < val) {


            if (currentNode->right == nullptr) {

                Node* newNode = new Node(val);

                currentNode->right = newNode;
                newNode->parent = currentNode;
                ++size;

                updateHeight(newNode->parent) ;

                return newNode;
            }
            else {
                currentNode = currentNode->right;
            }

        }
        else if (currentNode->value > val) {
            
            if (currentNode->left == nullptr) {

                Node* newNode = new Node(val);

                currentNode->left = newNode;
                newNode->parent = currentNode;
                ++size;

                updateHeight(newNode->parent) ;

                return newNode;
            }
            else {

                currentNode = currentNode->left;
            }
        }

    }
    
}



BinarySearchTree::Node* BinarySearchTree::Find(int val) const { 

    Node* current = root;


    while (current != nullptr) {

        if (current->value == val) {
            return current;
        }

        else if (current->value < val) {
            current = current->right;
        }
        else if (current->value > val) {
            current = current->left;
        }
    }


    return current;

} 


BinarySearchTree::Node* BinarySearchTree::Erase(int val) {


    Node* node = Find( val ) ;

    if (node == nullptr) {
        
        return nullptr;
    }

    Node* nextNodeToReturn = nullptr;

    if ( node->left == nullptr && node->right == nullptr ) {

        if (node != root) {

            if ( isNodeLeftChild( node ) ) {
                
                node->parent->left = nullptr;
                nextNodeToReturn = node->parent;
            }
            else {
                
                node->parent->right = nullptr;
                nextNodeToReturn = nextNode( node->parent) ;
            }
        }

        else {

            root = nullptr ;
        }

        updateHeight(node->parent) ;

        delete node;
        --size ;
        
    }

    else if ( node->left != nullptr && node->right == nullptr ) {

        if (node != root) {

            if (isNodeLeftChild(node) ) {
                
                node->parent->left = node->left;
                node->left->parent = node->parent;
                nextNodeToReturn = node->parent;
            }
            else {
                
                node->parent->right = node->left;
                node->left->parent = node->parent ;
                nextNodeToReturn = nextNode( node->left) ;
            }

        }

        else {

            node->left->parent = nullptr ;
            root = node->left ;
        }

        updateHeight(node->parent) ;

        delete node;
        --size;

    }

    else if (node->left == nullptr && node->right != nullptr ) {

        nextNodeToReturn = minFromNode(node->right);

        if (node != root) {

            if ( isNodeLeftChild(node) ) {
                
                node->parent->left = node->right;
                node->right->parent = node->parent;
            }
            else {
                
                node->parent->right = node->right;
                node->right->parent = node->parent ;
            }
        }

        else {

            node->right->parent = nullptr ;
            root = node->right ;
        }

        updateHeight(node->parent) ;

        delete node;
        --size ;
    }

    else if (node->left != nullptr && node->right != nullptr ) {

        nextNodeToReturn = minFromNode(node->right);

        Node* nodeMaxLeft = node->left;    

        while (nodeMaxLeft->right != nullptr) {

            nodeMaxLeft = nodeMaxLeft->right ;
        }

        node->value = nodeMaxLeft->value;


        if (nodeMaxLeft->left == nullptr) {

            if (isNodeLeftChild(nodeMaxLeft)) {
                
                nodeMaxLeft->parent->left = nullptr ;
            }
            else  {

                nodeMaxLeft->parent->right = nullptr ;
            }

            

        }

        else {

            if ( isNodeLeftChild(nodeMaxLeft) ) {
                
                nodeMaxLeft->parent->left = nodeMaxLeft->left ;
                nodeMaxLeft->left->parent = nodeMaxLeft->parent ;
            }

            else {

                nodeMaxLeft->parent->right = nodeMaxLeft->left ;
                nodeMaxLeft->left->parent = nodeMaxLeft->parent ;
            }

        }

        updateHeight(nodeMaxLeft->parent) ;

        delete nodeMaxLeft;
        --size;

        
    }

    return nextNodeToReturn;

}

BinarySearchTree::Node* BinarySearchTree::Min() const { 
    
    if (root == nullptr) {

        return nullptr;
    }

    Node* current = root;

    while (true) {

        if (current->left == nullptr) {
            return current;
        }

        current = current->left ;
    }
}

BinarySearchTree::Node* BinarySearchTree::Max() const { 
    
    if (root == nullptr) {

        return nullptr;
    }

    Node* current = root;

    while (true) {

        if (current->right == nullptr) {
            return current;
        }

        current = current->right ;
    }
}


size_t BinarySearchTree::Size() const {

    return size;
}

int BinarySearchTree::Height() const {

    return height(root) ;
}

int BinarySearchTree::height(Node* node) const {

    if (node == nullptr) {
        return 0;
    }
    else {
        return node->height;
    }
}

void BinarySearchTree::updateHeight(Node* node) {

    if (node == nullptr) {
        return ;
    }

    Node* current = node;

    while (true) {

        int newHeight = std::max( height(current->left), height( current->right) ) + 1 ;

        if ( newHeight != current->height) {

            current->height = newHeight;
            current = current->parent ;

            if (current == nullptr) {
                break;
            }
        }
        else {
            break;
        }
    }
}

bool BinarySearchTree::IsHeightCorrect() const {

    return isHeightCorrect(root);
}

bool BinarySearchTree::isHeightCorrect(Node* node) const {

    if (node == nullptr) {

        return true;
    }

    else {

        return node->height == std::max( height(node->left) , height(node->right) ) + 1 && isHeightCorrect(node->left) && isHeightCorrect(node->right) ;
    }

}


BinarySearchTree::Node* BinarySearchTree::beginNode() const {

    if (root == nullptr) {
        
        return nullptr;
    }

    Node* current = root;

    while (current->left != nullptr) {

        current = current->left;
    }
    
    return current;

}


BinarySearchTree::Node* BinarySearchTree::nextNode(Node* node) const {

    if ( node->right != nullptr )  {

        Node* current = node->right ;

        while (current->left != nullptr) {

            current = current->left;
        }
    
        return current;
    }


    Node* current = node;

    while ( current->parent != nullptr && !isNodeLeftChild(current) ) {

        current = current->parent;
    }

    return current->parent ;

}


bool BinarySearchTree::IsCorrect() const {

    if (size == 0) {

        return true;
    }

    Node* currentNode = beginNode();
    Node* next = nextNode(currentNode) ;

    while (next != nullptr) {

        if (next->value <= currentNode->value) {
            return false;
        }

        currentNode = next;
        next = nextNode(currentNode);
    }

    return true;
}

bool BinarySearchTree::IsCorrect2() const {

    return isNodeCorrectByMinMax(root, INT_MIN, INT_MAX) ;
}

bool BinarySearchTree::isNodeCorrectByMinMax(Node* node, int min, int max) const {

    if (node == nullptr) {
        return true;
    }

    if (node->value < min || node->value > max) {
        return false;
    }

    return isNodeCorrectByMinMax(node->left, min, node->value-1) && isNodeCorrectByMinMax(node->right, node->value + 1, max );
}


std::vector<int> BinarySearchTree::Print() const {

    std::vector<int> result;

    Node* current = beginNode() ;

    while ( current != nullptr ) {

        result.push_back(current->value );

        current = nextNode(current) ;
    }

    return result;
}


bool BinarySearchTree::isNodeLeftChild(Node* node) const {

    return node->parent->left == node;
}


BinarySearchTree::Node* BinarySearchTree::minFromNode(Node* node) const {
    
    if (node == nullptr) {

        return nullptr;
    }

    Node* current = node;

    while ( current->left != nullptr) {

        current = current->left;
    }

    return current;

}