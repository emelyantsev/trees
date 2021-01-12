#pragma once

#include <memory>
#include <vector>

class BST {

    public:

        struct Node {

            Node(int val);

            int value;
            
            Node* parent = nullptr;
            Node* left = nullptr;
            Node* right = nullptr; 

            ~Node() ;

        } ;

        BST() = default;

        ~BST() ;

        void insert(int val);
        bool find(int val);
        void erase(int val);

        int min();
        int max();

        size_t size();

        int max_height() ;

        bool is_correct() ;

        std::vector<int> print() ;

    private:

        Node* find_node(int val);

        int height_node(Node* p_node);

        Node* begin_node() ;
        
        Node* next_node(Node* p_node);


        Node* root = nullptr;
        size_t size_ = 0;

};

