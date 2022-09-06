#pragma once

#include <vector>

class AvlSumTree {

    public:

        struct Node {

            Node(int val);

            int value;
            long long sum;
            
            Node* parent;
            Node* left;
            Node* right;
            int height;

            ~Node() ;

        } ;

        AvlSumTree();

        ~AvlSumTree() ;

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
        bool IsSumCorrect() const ;

        //std::vector<int> PrintInOrder() ;
        //std::vector<int> PrintPreOrder() ;
        //std::vector<int> PrintPostOrder() ;
        // void Clear() ;

        std::vector< std::vector<int> > PrintByLevels() ;

        std::vector<int> Print() const ;

        long long SumLessEqual(int val) const ;

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

        long long sum(Node* node) const;
        void updateSum(Node* node) ;
        bool isSumCorrect(Node* node) const ;

        Node* root;
        size_t size;
};

