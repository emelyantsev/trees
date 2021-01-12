
#include "bst.h"

#include <iostream>
#include <queue>
#include <stdexcept>
#include <algorithm>

BST::Node::Node(int val) : value(val) {}

BST::Node::~Node() {

    std::cout << "Node with " << value << " deleted" << std::endl;
}


BST::~BST() {

    std::queue<Node*> p_node_queue;

    if (root != nullptr) {

        p_node_queue.push(root);
    }

    while (! p_node_queue.empty() ) {

        Node* p_top = p_node_queue.front();

        if (p_top->left != nullptr) {

            p_node_queue.push(p_top->left);
        }

        if (p_top->right != nullptr) {

            p_node_queue.push(p_top->right);
        }


        delete p_top;

        p_node_queue.pop();

    }
}

void BST::insert(int val) {


    if (root == nullptr) {

        root = new Node(val);
        ++size_;

        return;
    }


    Node* current = root;
    Node* parent = nullptr;

    while (true) {

        parent = current;

        if (current->value == val) {

            return ;
        }

        else if (current->value < val) {

            current = current->right ;

            if (current == nullptr) {

                Node* p_new = new Node(val);

                parent->right = p_new;
                p_new->parent = parent;
                ++size_;
                break;
            }

        }
        else if (current->value > val) {
            
            current = current->left ;

            if (current == nullptr) {

                Node* p_new = new Node(val);

                parent->left = p_new;
                p_new->parent = parent;
                ++size_;
                break;
            }
        }

    }
    
}



bool BST::find(int val) { 

    Node* current = root;


    while (current != nullptr) {

        if (current->value == val) {
            return true;
        }

        else if (current->value < val) {
            current = current->right;
        }
        else if (current->value > val) {
            current = current->left;
        }
    }


    return false;

} 


BST::Node* BST::find_node(int val) {

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


    return nullptr;

}

void BST::erase(int val) {


    Node* p_node = find_node(val) ;

    if (p_node == nullptr) {
        
        return ;
    }

    if ( p_node->left == nullptr && p_node->right == nullptr ) {

        if (p_node->parent != nullptr) {

            if (p_node->parent->left == p_node ) {
                
                p_node->parent->left = nullptr;
            }
            else if (p_node->parent->right == p_node ) {
                
                p_node->parent->right = nullptr;
            }
        }

        else {

            root = nullptr ;
        }


        delete p_node;
        --size_ ;
        
    }

    else if (p_node->left != nullptr && p_node->right == nullptr ) {


        if (p_node->parent != nullptr) {

            if (p_node->parent->left == p_node ) {
                
                p_node->parent->left = p_node->left;
                p_node->left->parent = p_node->parent;
            }
            else if (p_node->parent->right == p_node ) {
                
                p_node->parent->right = p_node->left;
                p_node->left->parent = p_node->parent ;
            }

        }

        else {

            p_node->left->parent = nullptr ;
            root = p_node->left ;
        }

        delete p_node;
        --size_ ;

    }

    else if (p_node->left == nullptr && p_node->right != nullptr ) {


        if (p_node->parent != nullptr) {

            if (p_node->parent->left == p_node ) {
                
                p_node->parent->left = p_node->right;
                p_node->right->parent = p_node->parent;
            }
            else if (p_node->parent->right == p_node ) {
                
                p_node->parent->right = p_node->right;
                p_node->right->parent = p_node->parent ;
            }
        }

        else {

            p_node->right->parent = nullptr ;
            root = p_node->right ;
        }

        delete p_node;
        --size_ ;

    }

    else if (p_node->left != nullptr && p_node->right != nullptr ) {


        Node* p_left_max = p_node->left;    

        while (p_left_max->right != nullptr) {

            p_left_max = p_left_max->right ;
        }

        p_node->value = p_left_max->value;


        if (p_left_max->left == nullptr) {

            if (p_left_max->parent->left == p_left_max) {
                
                p_left_max->parent->left = nullptr ;
            }
            else if (p_left_max->parent->right == p_left_max) {

                p_left_max->parent->right = nullptr ;
            }

            delete p_left_max;
            --size_;

        }

        else {

            if (p_left_max->parent->left == p_left_max) {
                
                p_left_max->parent->left = p_left_max->left ;
                p_left_max->left->parent = p_left_max->parent ;
            }

            else if (p_left_max->parent->right == p_left_max) {

                p_left_max->parent->right = p_left_max->left ;
                p_left_max->left->parent = p_left_max->parent ;
            }

            delete p_left_max;
            --size_;

        }

    }

}

int BST::min() { 
    
    if (size_ == 0) {

        throw std::logic_error("Empty set");

    }

    Node* current = root;

    while (true) {

        if (current->left == nullptr) {
            return current->value;
        }

        current = current->left ;
    }

}



int BST::max() { 

    if (size_ == 0) {

        throw std::logic_error("Empty set");

    }

    Node* current = root;

    while (true) {

        if (current->right == nullptr) {
 
            return current->value;
        }

        current = current->right ;
    }

}

size_t BST::size() {

    return size_;
}

int BST::max_height() {

    return height_node(root) ;
}

int BST::height_node(BST::Node* p_node) {

    if (p_node == nullptr) {

        return 0;
    }

    else {

        return 1 + std::max(height_node(p_node->left), height_node(p_node->right)) ;
    }
}





BST::Node* BST::begin_node() {

    if (root == nullptr) {
        
        return nullptr;
    }

    Node* result = root;

    while (result->left != nullptr) {

        result = result->left;
    }
    
    return result;

}


BST::Node* BST::next_node(Node* p_node) {

    if (p_node->right != nullptr )  {

        Node* result = p_node->right ;


        while (result->left != nullptr) {

            result = result->left;
        }
    
        return result;


    }


    Node* p_current = p_node;

    while (p_current->parent != nullptr && p_current->parent->right == p_current) {

        p_current = p_current->parent;
    }

    return p_current->parent ;

}


bool BST::is_correct() {

    if (size_ == 0) {

        return true;
    }

    Node* current_node = begin_node();

    Node* next_ = next_node(current_node) ;

    while (next_ != nullptr) {

        if (next_->value <= current_node->value) {
            return false;
        }

        current_node = next_;
        next_ = next_node(current_node);
    }

    return true;
}


std::vector<int> BST::print() {

    std::vector<int> result;

    Node* current = begin_node() ;

    while ( current != nullptr ) {

        result.push_back(current->value );

        current = next_node(current) ;
    }

    return result;
}



