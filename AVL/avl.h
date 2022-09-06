#pragma once

#include <vector>

class AvlTree {

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

        AvlTree();

        ~AvlTree() ;

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

        //std::vector<int> PrintInOrder() const;
        //std::vector<int> PrintPreOrder() const;
        //std::vector<int> PrintPostOrder() const;
        //void Clear() ;

        std::vector< std::vector<int> > PrintByLevels() ;

        std::vector<int> Print() const ;

    private:

        Node* beginNode() const ;
        Node* nextNode(Node* node) const ;

        Node* minFromNode(Node* node) const ;
        Node* maxFromNode(Node* node) const ;

        bool isNodeLeftChild(Node* node) const ;
        bool isNodeCorrectByMinMax(Node* node, int min, int max) const ;

        int height(Node* node) const ;
        bool isHeightCorrect(Node* node) const;
        void updateHeight(Node* node) ;
        bool hasTwoChildren(Node* node) const ;
        Node* updateAndRotateIfNeeded(Node* node) ;
        bool isBalanced(Node* node) const;
        Node* balance(Node* node) ;


        bool needRotateRight(Node* node) ;
        bool needRotateLeft(Node* node) ;
        bool needRotateRightLeft(Node* node) ;
        bool needRotateLeftRight(Node* node) ;

        Node* rotateRight(Node* node) ;
        Node* rotateLeft(Node* node) ;
        Node* rotateLeftRight(Node* node) ;
        Node* rotateRightLeft(Node* node) ;

        Node* root;
        size_t size;

};

