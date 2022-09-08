#pragma once

#include <vector>

class AvlSMTree {

    public:

        struct Node {

            Node(int val);

            int value;
            int size;
            
            Node* parent;
            Node* left;
            Node* right;
            int height;

            ~Node() ;

        } ;

        AvlSMTree();
        AvlSMTree(AvlSMTree&& other);

        ~AvlSMTree() ;

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
        bool IsSizeCorrect() const ;
        bool IsBalanced() const ;

        std::vector< std::vector<int> > PrintByLevels() ;
        std::vector<int> Print() const ;

        static AvlSMTree Merge(AvlSMTree& T1, AvlSMTree& T2);
        static Node* MergeWithRoot(Node* v1, Node* v2, Node* T);
        static Node* AVLMergeWithRoot(Node* v1, Node* v2, Node* T);

        static std::pair<AvlSMTree, AvlSMTree> SplitAVL(AvlSMTree& T, int key) ;
        static std::pair<Node*, Node*> Split(Node* v, int key);

    private:

        Node* beginNode() const ;
        Node* nextNode(Node* node) const ;

        static Node* minFromNode(Node* node) ;
        static Node* maxFromNode(Node* node) ;

        static bool isNodeLeftChild(Node* node) ;
        static bool isNodeCorrectByMinMax(Node* node, int min, int max) ;

        static int height(Node* node) ;
        static bool isHeightCorrect(Node* node);
        void updateHeight(Node* node) ;
        static bool hasTwoChildren(Node* node) ;
        static Node* updateAndRotateIfNeeded(Node* node) ;
        static bool isBalanced(Node* node);
        static Node* balance(Node* node) ;


        static bool needRotateRight(Node* node) ;
        static bool needRotateLeft(Node* node) ;
        static bool needRotateRightLeft(Node* node) ;
        static bool needRotateLeftRight(Node* node) ;

        static Node* rotateRight(Node* node) ;
        static Node* rotateLeft(Node* node) ;
        static Node* rotateLeftRight(Node* node) ;
        static Node* rotateRightLeft(Node* node) ;

        static int sizeNode(Node* node) ;
        static void updateSize(Node* node) ;
        static void updateNodeHeight(Node* node) ;
        static bool isSizeCorrect(Node* node) ;

        Node* root;
        size_t size;
};

