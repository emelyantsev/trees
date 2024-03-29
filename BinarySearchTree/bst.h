#pragma once

#include <vector>

class BinarySearchTree {

    public:

        struct Node {

            Node(int val);

            int value;
            
            Node* parent;
            Node* left;
            Node* right;
            int height;

            ~Node() ;

        } ;

        BinarySearchTree();

        ~BinarySearchTree() ;

        Node* Insert(int value);
        Node* Find(int value) const;
        Node* Erase(int value);

        Node* Min() const;
        Node* Max() const;

        size_t Size() const;

        int Height() const;

        bool IsCorrect() const;
        bool IsCorrect2() const;
        bool IsHeightCorrect() const;

        //std::vector<int> PrintInOrder() ;
        //std::vector<int> PrintPreOrder() ;
        //std::vector<int> PrintPostOrder() ;

        // void Clear() ;


        std::vector<int> Print() const ;

    private:

        Node* beginNode() const ;
        Node* nextNode(Node* node) const ;

        Node* minFromNode(Node* node) const ;

        bool isNodeLeftChild(Node* node) const ;
        bool isNodeCorrectByMinMax(Node* node, int min, int max) const ;

        int height(Node* node) const ;
        bool isHeightCorrect(Node* node) const;
        void updateHeight(Node* node) ;


        Node* root;
        size_t size;

};

