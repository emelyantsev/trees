#include <iostream>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <algorithm>

#include <cassert>
#include <unordered_map>
#include <climits>
#include <utility>

#include <vector>

class AvlSMTree {

    public:

        struct Node {

            Node(char val);

            char value;
            int size;
            
            Node* parent;
            Node* left;
            Node* right;
            int height;

            ~Node() ;

        } ;

        AvlSMTree();
        AvlSMTree(char c);
        AvlSMTree(AvlSMTree&& other);

        ~AvlSMTree() ;

        Node* Erase(Node* value);

        Node* Min() const;
        Node* Max() const;

        size_t Size() const;

        int Height() const;

        bool IsHeightCorrect() const;
        bool IsSizeCorrect() const ;
        bool IsBalanced() const ;

        std::vector< std::vector<char> > PrintByLevels() ;
        std::vector<char> Print() const ;

        static AvlSMTree Merge(AvlSMTree& T1, AvlSMTree& T2);
        static Node* MergeWithRoot(Node* v1, Node* v2, Node* T);
        static Node* AVLMergeWithRoot(Node* v1, Node* v2, Node* T);

        static std::pair<AvlSMTree, AvlSMTree> SplitAVL(AvlSMTree& T, int position) ;
        static std::pair<Node*, Node*> Split(Node* v, int position);

        AvlSMTree& operator=(AvlSMTree&& other) ;

        Node* OrderStatistics(int k) ;

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

        Node* orderStatistics(Node* node, int k) ;

        Node* root;
        size_t size;
};



AvlSMTree::Node::Node(char val) : value(val), parent(nullptr), left(nullptr), right(nullptr), height(1), size(1)  {}


AvlSMTree::Node::~Node() {}


AvlSMTree::AvlSMTree() : root(nullptr), size(0) {}

AvlSMTree::AvlSMTree(char c) : root(new Node(c) ) , size(1) {}

AvlSMTree::AvlSMTree(AvlSMTree&& other) : root(other.root), size(other.size) {
    other.root = nullptr;
    other.size = 0;
}

AvlSMTree& AvlSMTree::operator=(AvlSMTree&& other) {
    root = other.root;
    size = other.size;
    other.root = nullptr;
    other.size = 0;

    return *this;
}


AvlSMTree::~AvlSMTree() {

    //std::cout << "AvlSMTree destructor called " << root << " " << size << std::endl;

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




AvlSMTree::Node* AvlSMTree::Erase(Node* node) {

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
                nextNodeToReturn = nextNode( maxFromNode(node->left) ) ;
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

        Node* nodeMaxLeft = maxFromNode( node->left ) ;

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

AvlSMTree::Node* AvlSMTree::Min() const { 
    
    return minFromNode(root);
}

AvlSMTree::Node* AvlSMTree::Max() const { 
    
    return maxFromNode(root) ;
}


size_t AvlSMTree::Size() const {

    return size;
}

int AvlSMTree::Height() const {

    return height(root) ;
}

int AvlSMTree::height(Node* node) {

    if (node == nullptr) {
        return 0;
    }
    else {
        return node->height;
    }
}

int AvlSMTree::sizeNode(Node* node) {

    if (node == nullptr) {
        return 0;
    }
    else {
        return node->size;
    }
};

void AvlSMTree::updateHeight(Node* node) {

    if (node == nullptr) {
        return ;
    }

    Node* current = node;

    while ( true ) {

        current = updateAndRotateIfNeeded( current ) ;

        if (current->parent == nullptr) {
            root = current;
            break;
        }
        else {
            current = current->parent;
        }

    }
}

void AvlSMTree::updateSize(Node* node) {

    node->size = 1 + sizeNode(node->left) + sizeNode(node->right) ;
}

void AvlSMTree::updateNodeHeight(Node* node) {

    node->height = std::max( height(node->left), height( node->right) ) + 1;
}

AvlSMTree::Node* AvlSMTree::updateAndRotateIfNeeded(Node* node) {

    if ( isBalanced(node) ) {

        node->height = std::max( height(node->left), height( node->right) ) + 1;
        node->size = 1 + sizeNode(node->left) + sizeNode(node->right) ;

        return node;
    }

    else {

        return balance(node) ;
    }
}

AvlSMTree::Node* AvlSMTree::balance(Node* node) {

    Node* result ;

    if ( needRotateRight(node) ) {

        result = rotateRight(node) ;
    }
    else if (needRotateLeft(node)) {
        
        result = rotateLeft(node) ;
    }
    else if (needRotateLeftRight(node)) {
        
        result = rotateLeftRight(node) ;
    }
    else if( needRotateRightLeft(node)) {
        
        result = rotateRightLeft(node) ;
    }
    else {

        updateSize(node) ;
        updateNodeHeight(node) ;

        result = node;
    }

    return result;
}

bool AvlSMTree::needRotateRight(Node* node) {

    if ( height( node->left) - height( node->right ) > 1 && height(node->left->left) >= height(node->left->right) ) {

        return true;
    }
    else {
        return false;
    }
};

AvlSMTree::Node* AvlSMTree::rotateRight(Node* node) {

    Node* nodeA = node;
    Node* nodeB = nodeA->left;
    Node* nodeC = nodeB->left;
    Node* nodeD = nodeB->right;
    Node* nodeP = node->parent;

    if (nodeP == nullptr) {
        ;
    }
    else {
        if (isNodeLeftChild(node) ) {
            nodeP->left = nodeB;
        }
        else {
            nodeP->right = nodeB;
        }
    }



    nodeA->left = nodeD;
    nodeA->parent = nodeB;
    nodeA->height = std::max( height(nodeA->left), height(nodeA->right) ) + 1 ;
    updateSize(nodeA);

    nodeB->right = nodeA;
    nodeB->parent = nodeP;
    nodeB->height = std::max( height(nodeB->left), height(nodeB->right) ) + 1 ;
    updateSize(nodeB);

    if (nodeD != nullptr) {
        nodeD->parent = nodeA;
    }

    return nodeB;
}


bool AvlSMTree::needRotateLeftRight(Node* node) {

    if ( height( node->left) - height( node->right ) > 1 && height(node->left->left) < height(node->left->right) ) {

        return true;
    }
    else {
        return false;
    }

}

AvlSMTree::Node* AvlSMTree::rotateLeftRight(Node* node) {

    Node* nodeA = node;
    Node* nodeB = nodeA->left;
    Node* nodeD = nodeB->right;
    Node* nodeF = nodeD->left;
    Node* nodeG = nodeD->right;
    Node* nodeP = nodeA->parent;


    if (nodeP == nullptr) {
        ;
    }
    else {
        if (isNodeLeftChild(node) ) {
            nodeP->left = nodeD;
        }
        else {
            nodeP->right = nodeD;
        }
    }



    nodeA->left = nodeG;
    nodeA->parent = nodeD;
    nodeA->height = std::max( height(nodeA->left), height(nodeA->right) ) + 1 ;
    updateSize(nodeA);

    if (nodeG != nullptr) {
        nodeG->parent = nodeA;
    }

    nodeB->right = nodeF;
    nodeB->parent = nodeD;
    nodeB->height = std::max( height(nodeB->left), height(nodeB->right) ) + 1 ;
    updateSize(nodeB);

    if (nodeF != nullptr) {
        nodeF->parent = nodeB;
    }

    nodeD->parent = nodeP;
    nodeD->left = nodeB;
    nodeD->right = nodeA;
    nodeD->height = std::max( height(nodeD->left), height(nodeD->right) ) + 1 ;    
    updateSize(nodeD);

    return nodeD;

}


bool AvlSMTree::needRotateLeft(Node* node) {

    if ( height( node->left) - height( node->right ) < -1 && height(node->right->right) >= height(node->right->left) ) {

        return true;
    }
    else {
        return false;
    }
}

AvlSMTree::Node* AvlSMTree::rotateLeft(Node* node) {

    Node* nodeA = node;
    Node* nodeB = nodeA->right;
    Node* nodeC = nodeB->right;
    Node* nodeD = nodeB->left;
    Node* nodeP = node->parent;

    if (nodeP == nullptr) {
        ;
    }
    else {
        if (isNodeLeftChild(node) ) {
            nodeP->left = nodeB;
        }
        else {
            nodeP->right = nodeB;
        }
    }



    nodeA->right = nodeD;
    nodeA->parent = nodeB;
    nodeA->height = std::max( height(nodeA->left), height(nodeA->right) ) + 1 ;
    updateSize(nodeA);

    nodeB->left = nodeA;
    nodeB->parent = nodeP;
    nodeB->height = std::max( height(nodeB->left), height(nodeB->right) ) + 1 ;
    updateSize(nodeB);

    if (nodeD != nullptr) {
        nodeD->parent = nodeA;
    }

    return nodeB;
}


bool AvlSMTree::needRotateRightLeft(Node* node) {

    if ( height( node->left ) - height( node->right ) < -1 && height(node->right->left) > height(node->right->right) ) {

        return true;
    }
    else {
        return false;
    }

}

AvlSMTree::Node* AvlSMTree::rotateRightLeft(Node* node) {

    Node* nodeA = node;
    Node* nodeB = nodeA->right;
    Node* nodeD = nodeB->left;
    Node* nodeF = nodeD->right;
    Node* nodeG = nodeD->left;
    Node* nodeP = nodeA->parent;


    if (nodeP == nullptr) {
        ;
    }
    else {
        if (isNodeLeftChild(node) ) {
            nodeP->left = nodeD;
        }
        else {
            nodeP->right = nodeD;
        }
    }


    nodeA->right = nodeG;
    nodeA->parent = nodeD;
    nodeA->height = std::max( height(nodeA->left), height(nodeA->right) ) + 1 ;
    updateSize(nodeA);

    if (nodeG != nullptr) {
        nodeG->parent = nodeA;
    }

    nodeB->left = nodeF;
    nodeB->parent = nodeD;
    nodeB->height = std::max( height(nodeB->left), height(nodeB->right) ) + 1 ;
    updateSize(nodeB);

    if (nodeF != nullptr) {
        nodeF->parent = nodeB;
    }

    nodeD->parent = nodeP;
    nodeD->left = nodeA;
    nodeD->right = nodeB;
    nodeD->height = std::max( height(nodeD->left), height(nodeD->right) ) + 1 ;    
    updateSize(nodeD);

    return nodeD;

}

bool AvlSMTree::IsBalanced() const {

    return isBalanced(root) ;
};

bool AvlSMTree::isBalanced(Node* node) {

    if (node == nullptr ) {
        return true;
    }

    int heightDiff = height(node->left) - height(node->right) ;

    return heightDiff < 2 && heightDiff > -2 ;
}


bool AvlSMTree::IsHeightCorrect() const {

    return isHeightCorrect(root);
}

bool AvlSMTree::isHeightCorrect(Node* node) {

    if (node == nullptr) {

        return true;
    }

    else {

        return node->height == std::max( height(node->left) , height(node->right) ) + 1 && isHeightCorrect(node->left) && isHeightCorrect(node->right);
    }

}

bool AvlSMTree::IsSizeCorrect() const {

    return isSizeCorrect(root);
}


bool AvlSMTree::isSizeCorrect(Node* node) {

    if (node == nullptr) {
        
        return true;
    }
    else {

        return node->size == 1 + sizeNode(node->left) + sizeNode(node->right) && isSizeCorrect(node->left) && isSizeCorrect(node->right) ;
    }
}

AvlSMTree::Node* AvlSMTree::beginNode() const {

    if (root == nullptr) {
        
        return nullptr;
    }

    Node* current = root;

    while (current->left != nullptr) {

        current = current->left;
    }
    
    return current;

}


AvlSMTree::Node* AvlSMTree::nextNode(Node* node) const {

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

std::vector<char> AvlSMTree::Print() const {

    std::vector<char> result;

    Node* current = beginNode() ;

    while ( current != nullptr ) {

        result.push_back(current->value );

        current = nextNode(current) ;
    }

    return result;
}


bool AvlSMTree::isNodeLeftChild(Node* node) {

    return node->parent->left == node;
}


AvlSMTree::Node* AvlSMTree::minFromNode(Node* node) {
    
    if (node == nullptr) {

        return nullptr;
    }

    Node* current = node;

    while ( current->left != nullptr) {

        current = current->left;
    }

    return current;

}

AvlSMTree::Node* AvlSMTree::maxFromNode(Node* node) {
    
    if (node == nullptr) {

        return nullptr;
    }

    Node* current = node;

    while ( current->right != nullptr) {

        current = current->right;
    }

    return current;

}

bool AvlSMTree::hasTwoChildren(Node* node) {
    
    return node->left != nullptr && node->right != nullptr;
}

std::vector<std::vector<char>> AvlSMTree::PrintByLevels() {
     
        
    std::vector< std::vector<char> > result;
    
    if (root == nullptr) {
        
        return result;
    }
    
    
    std::unordered_map< Node*, int> nodesLevels;
    
    std::vector< Node*> nodes;
    
    nodesLevels[root] = 0;
    
    std::queue<Node*> q;
    
    q.push(root);
    
    while ( !q.empty() ) {
        
        Node* current = q.front() ;
        q.pop();
        
        if (current->left != nullptr ) {
            
            nodesLevels[current->left ] = nodesLevels[current] + 1;
            
            q.push(current->left) ;
        }
        
        if (current->right != nullptr ) {
            
            nodesLevels[current->right ] = nodesLevels[current] + 1;
            
            q.push(current->right) ;
        }
        
        nodes.push_back(current) ;
        
    }
    
    
    for (auto node : nodes) {
        
        if (result.size() < nodesLevels[node] + 1 ) {
            
            
            result.resize(result.size()+1) ;
            
            
        }
        
        result[ nodesLevels[node] ].push_back(node->value) ;
        
    }

    return result;
}


AvlSMTree::Node* AvlSMTree::MergeWithRoot(Node* v1, Node* v2, Node* T) {

    T->left = v1;
    T->right = v2;

    if (v1 != nullptr) {
        v1->parent = T;
    }

    if (v2 != nullptr ) {
        v2->parent = T;
    }

    updateSize(T);
    T->height = std::max( height(v1), height( v2) ) + 1;

    return T;
}

AvlSMTree AvlSMTree::Merge(AvlSMTree& T1, AvlSMTree& T2) {


    if ( T1.Size() == 0) {
        return std::move(T2);
    }
    else if (T2.Size() == 0) {
        return std::move(T1) ;
    }

    Node* maxValueT1 = T1.Max() ;

    Node* T = new Node(maxValueT1->value) ;

    T1.Erase(maxValueT1) ;

    T = AVLMergeWithRoot( T1.root, T2.root, T ) ;

    AvlSMTree result;

    result.root = T;
    result.size = T->size;

    T1.root = nullptr;
    T2.root = nullptr;
    T1.size = 0;
    T2.size = 0;

    return std::move(result);
}

AvlSMTree::Node* AvlSMTree::AVLMergeWithRoot(Node* v1, Node* v2, Node* T) {


    int heightDiff = height(v1) - height(v2);

    if (heightDiff <= 1 && heightDiff >= -1 ) {

        MergeWithRoot(v1, v2, T);

        return T;
    }
    else if ( height(v1) > height(v2) ) {

        Node* newT = AVLMergeWithRoot(v1->right, v2, T) ;
 
        v1->right = newT;
        newT->parent = v1;

        return balance(v1);
    }
    else {

        Node* newT = AVLMergeWithRoot(v1, v2->left, T) ;

        v2->left = newT;
        newT->parent = v2;

        return balance(v2);
    }
}


std::pair<AvlSMTree::Node*, AvlSMTree::Node*> AvlSMTree::Split(Node* v, int position) {

    if (v == nullptr) {

        return {nullptr, nullptr} ;
    }

    if (position < sizeNode(v->left) + 1) {
        

        auto vertices = Split(v->left, position) ;

        Node* v1 = vertices.first;
        Node* v2 = vertices.second;

        if (v != nullptr) {
            v->parent = nullptr;
        }

        if (v2 != nullptr) {
            v2->parent = nullptr;
        }

        if (v->right != nullptr) {

            v->right->parent = nullptr;
        }

    
        Node* v2_ = AVLMergeWithRoot(v2, v->right, v) ;

        if (v1 != nullptr) {
            v1->parent = nullptr;
        }
        if (v2_ != nullptr ) {
            v2_->parent = nullptr;
        }

        return {v1, v2_} ;
    }
    
    else {

        auto vertices = Split(v->right, position - sizeNode(v->left) - 1 ) ;

        Node* v1 = vertices.first;
        Node* v2 = vertices.second;

        if (v != nullptr) {
            v->parent = nullptr;
        }

        if (v1 != nullptr) {
            v1->parent = nullptr;
        }

        if (v->left != nullptr) {

            v->left->parent = nullptr;
        }

        Node* v1_ = AVLMergeWithRoot(v->left, v1, v) ;

        if (v1_ != nullptr) {
            v1_->parent = nullptr;
        }
        if (v2 != nullptr ) {
            v2->parent = nullptr;
        }


        return {v1_, v2} ;

    }

}


std::pair<AvlSMTree, AvlSMTree> AvlSMTree::SplitAVL(AvlSMTree& T, int position) {


    auto [v1, v2] = Split(T.root, position) ;

    AvlSMTree T1;
    T1.root = v1;
    T1.size = v1 == nullptr ? 0 : v1->size;

    AvlSMTree T2;
    T2.root = v2;
    T2.size = v2 == nullptr ? 0 : v2->size;

    T.root = nullptr;
    T.size = 0;

    return {std::move(T1), std::move(T2)} ;

}


AvlSMTree::Node* AvlSMTree::OrderStatistics(int k) {

    return orderStatistics(root, k) ;
}

AvlSMTree::Node* AvlSMTree::orderStatistics(Node* node, int k) {

    if (node == nullptr) {
        return nullptr;
    }

    if (k == sizeNode(node->left) + 1  ) {
        return node;
    }
    else if (k < sizeNode(node->left) + 1) {

        return orderStatistics(node->left, k);
    }
    else {

        return orderStatistics(node->right, k - sizeNode(node->left) - 1) ;
    }
}


std::ostream& operator<<( std::ostream& os, const std::vector<char>& v )
{

    os << "[ ";

    for( int i = 0; i < v.size(); ++i ) {

        os << " " << v[i] << " ";
    }

    os << "]";

    return os;
}


int main() {


    std::string S;

    std::cin >> S;
    
    int Q;

    std::cin >> Q;

    AvlSMTree avl;

    for (char c : S) {

        AvlSMTree prevTree = std::move( avl );

        AvlSMTree nextTree(c);

        AvlSMTree mergedTree = AvlSMTree::Merge(prevTree, nextTree);

        avl = std::move(mergedTree) ;
    }


    for (int q = 0; q < Q; ++q) {

        int i, j, k;
        std::cin >> i >> j >> k;

        auto [T1, T2] = AvlSMTree::SplitAVL(avl, j+1) ;

        auto [T3, T4] = AvlSMTree::SplitAVL(T1, i) ;

        AvlSMTree mergedT = AvlSMTree::Merge(T3, T2);

        auto [T5, T6] = AvlSMTree::SplitAVL(mergedT, k) ;

        AvlSMTree mergedT2 = AvlSMTree::Merge(T5, T4);

        AvlSMTree mergedT3 = AvlSMTree::Merge(mergedT2, T6);

        avl = std::move(mergedT3);

    }

    std::vector<char> v = avl.Print();


    std::string result ;

    result.reserve(v.size() );

    for (char c : v) {
        result.push_back(c);
    }


    std::cout << result << std::endl;


    return 0;
}