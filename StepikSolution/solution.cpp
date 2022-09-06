#include <vector>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <algorithm>
#include <climits>

#include <cassert>
#include <unordered_map>
#include <string>

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

        std::vector< std::vector<int> > PrintByLevels() ;

        // void Clear() ;


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

AvlSumTree::Node::Node(int val) : value(val), parent(nullptr), left(nullptr), right(nullptr), height(1), sum(val)  {}


AvlSumTree::Node::~Node() {}


AvlSumTree::AvlSumTree() : root(nullptr), size(0) {}


AvlSumTree::~AvlSumTree() {

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

AvlSumTree::Node* AvlSumTree::Insert(int val) {

    AvlSumTree::Node* node = Find(val) ;

    if ( node != nullptr) {
        return node ;
    }


    if (root == nullptr) {

        root = new Node(val);

        ++size;

        return root;
    }


    Node* currentNode = root;

    while ( true ) {

        currentNode->sum += val;

        if (currentNode->value == val) {

            return currentNode;
        }

        else if (currentNode->value < val) {


            if (currentNode->right == nullptr) {

                Node* newNode = new Node(val);

                currentNode->right = newNode;
                newNode->parent = currentNode;
                ++size;

                if ( !hasTwoChildren(newNode->parent) ) {

                    updateHeight(newNode->parent) ;

                }

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

                if ( !hasTwoChildren(newNode->parent) ) {

                    updateHeight(newNode->parent) ;

                }

                return newNode;
            }
            else {

                currentNode = currentNode->left;
            }
        }

    }
    
}



AvlSumTree::Node* AvlSumTree::Find(int val) const { 

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


AvlSumTree::Node* AvlSumTree::Erase(int val) {


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

AvlSumTree::Node* AvlSumTree::Min() const { 
    
    return minFromNode(root);
}

AvlSumTree::Node* AvlSumTree::Max() const { 
    
    return maxFromNode(root) ;
}


size_t AvlSumTree::Size() const {

    return size;
}

int AvlSumTree::Height() const {

    return height(root) ;
}

int AvlSumTree::height(Node* node) const {

    if (node == nullptr) {
        return 0;
    }
    else {
        return node->height;
    }
}

long long AvlSumTree::sum(Node* node) const {

    if (node == nullptr) {
        return 0;
    }
    else {
        return node->sum;
    }
};

void AvlSumTree::updateHeight(Node* node) {

    if (node == nullptr) {
        return ;
    }

    Node* current = node;

    while ( current != nullptr ) {

        current = updateAndRotateIfNeeded( current ) ;
    }
}

void AvlSumTree::updateSum(Node* node) {

    node->sum = node->value + sum(node->left) + sum(node->right) ;
}

AvlSumTree::Node* AvlSumTree::updateAndRotateIfNeeded(Node* node) {

    int newHeight = std::max( height(node->left), height( node->right) ) + 1 ;

    if ( isBalanced(node) ) {

        node->height = newHeight;

        node->sum = node->value + sum(node->left) + sum(node->right) ;

        return node->parent;
    }

    else {

        return balance(node) ;
    }
}

AvlSumTree::Node* AvlSumTree::balance(Node* node) {

    assert(!isBalanced(node)) ;

    if ( needRotateRight(node) ) {

        return rotateRight(node) ;
    }
    else if (needRotateLeft(node)) {
        return rotateLeft(node) ;
    }
    else if (needRotateLeftRight(node)) {
        return rotateLeftRight(node) ;
    }
    else if( needRotateRightLeft(node)) {
        return rotateRightLeft(node) ;
    }

    else {

        assert(false);
    }

    return nullptr;
}

bool AvlSumTree::needRotateRight(Node* node) {

    if ( height( node->left) - height( node->right ) > 1 && height(node->left->left) >= height(node->left->right) ) {

        return true;
    }
    else {
        return false;
    }
};

AvlSumTree::Node* AvlSumTree::rotateRight(Node* node) {

    Node* nodeA = node;
    Node* nodeB = nodeA->left;
    Node* nodeC = nodeB->left;
    Node* nodeD = nodeB->right;
    Node* nodeP = node->parent;

    if (nodeP == nullptr) {
        root = nodeB;
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
    updateSum(nodeA);

    nodeB->right = nodeA;
    nodeB->parent = nodeP;
    nodeB->height = std::max( height(nodeB->left), height(nodeB->right) ) + 1 ;
    updateSum(nodeB);

    if (nodeD != nullptr) {
        nodeD->parent = nodeA;
    }

    return nodeP;
}


bool AvlSumTree::needRotateLeftRight(Node* node) {

    if ( height( node->left) - height( node->right ) > 1 && height(node->left->left) < height(node->left->right) ) {

        return true;
    }
    else {
        return false;
    }

}

AvlSumTree::Node* AvlSumTree::rotateLeftRight(Node* node) {

    Node* nodeA = node;
    Node* nodeB = nodeA->left;
    Node* nodeD = nodeB->right;
    Node* nodeF = nodeD->left;
    Node* nodeG = nodeD->right;
    Node* nodeP = nodeA->parent;


    if (nodeP == nullptr) {
        root = nodeD;
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
    updateSum(nodeA);

    if (nodeG != nullptr) {
        nodeG->parent = nodeA;
    }


    nodeB->right = nodeF;
    nodeB->parent = nodeD;
    nodeB->height = std::max( height(nodeB->left), height(nodeB->right) ) + 1 ;
    updateSum(nodeB);

    if (nodeF != nullptr) {
        nodeF->parent = nodeB;
    }

    nodeD->parent = nodeP;
    nodeD->left = nodeB;
    nodeD->right = nodeA;
    nodeD->height = std::max( height(nodeD->left), height(nodeD->right) ) + 1 ;    
    updateSum(nodeD);

    return nodeP;

}


bool AvlSumTree::needRotateLeft(Node* node) {

    if ( height( node->left) - height( node->right ) < -1 && height(node->right->right) >= height(node->right->left) ) {

        return true;
    }
    else {
        return false;
    }
}

AvlSumTree::Node* AvlSumTree::rotateLeft(Node* node) {

    Node* nodeA = node;
    Node* nodeB = nodeA->right;
    Node* nodeC = nodeB->right;
    Node* nodeD = nodeB->left;
    Node* nodeP = node->parent;

    if (nodeP == nullptr) {
        root = nodeB;
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
    updateSum(nodeA);

    nodeB->left = nodeA;
    nodeB->parent = nodeP;
    nodeB->height = std::max( height(nodeB->left), height(nodeB->right) ) + 1 ;
    updateSum(nodeB);

    if (nodeD != nullptr) {
        nodeD->parent = nodeA;
    }

    return nodeP;
}


bool AvlSumTree::needRotateRightLeft(Node* node) {

    if ( height( node->left ) - height( node->right ) < -1 && height(node->right->left) > height(node->right->right) ) {

        return true;
    }
    else {
        return false;
    }

}

AvlSumTree::Node* AvlSumTree::rotateRightLeft(Node* node) {

    Node* nodeA = node;
    Node* nodeB = nodeA->right;
    Node* nodeD = nodeB->left;
    Node* nodeF = nodeD->right;
    Node* nodeG = nodeD->left;
    Node* nodeP = nodeA->parent;


    if (nodeP == nullptr) {
        root = nodeD;
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
    updateSum(nodeA);

    if (nodeG != nullptr) {
        nodeG->parent = nodeA;
    }

    nodeB->left = nodeF;
    nodeB->parent = nodeD;
    nodeB->height = std::max( height(nodeB->left), height(nodeB->right) ) + 1 ;
    updateSum(nodeB);

    if (nodeF != nullptr) {
        nodeF->parent = nodeB;
    }

    nodeD->parent = nodeP;
    nodeD->left = nodeA;
    nodeD->right = nodeB;
    nodeD->height = std::max( height(nodeD->left), height(nodeD->right) ) + 1 ;    
    updateSum(nodeD);

    return nodeP;

}


bool AvlSumTree::isBalanced(Node* node) const {

    if (node == nullptr ) {
        return true;
    }

    int heightDiff = height(node->left) - height(node->right) ;

    return heightDiff < 2 && heightDiff > -2 ;
}


bool AvlSumTree::IsHeightCorrect() const {

    return isHeightCorrect(root);
}

bool AvlSumTree::isHeightCorrect(Node* node) const {

    if (node == nullptr) {

        return true;
    }

    else {

        if (!isBalanced(node)) {
            std::cout << node->value << std::endl;
        }

        return isBalanced(node) && node->height == std::max( height(node->left) , height(node->right) ) + 1 && isHeightCorrect(node->left) && isHeightCorrect(node->right) && isBalanced(node);
    }

}

bool AvlSumTree::IsSumCorrect() const {

    return isSumCorrect(root);
}


bool AvlSumTree::isSumCorrect(Node* node) const {

    if (node == nullptr) {
        
        return true;
    }
    else {

        return node->sum == node->value + sum(node->left) + sum(node->right) && isSumCorrect(node->left) && isSumCorrect(node->right) ;
    }
}

AvlSumTree::Node* AvlSumTree::beginNode() const {

    if (root == nullptr) {
        
        return nullptr;
    }

    Node* current = root;

    while (current->left != nullptr) {

        current = current->left;
    }
    
    return current;

}


AvlSumTree::Node* AvlSumTree::nextNode(Node* node) const {

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


bool AvlSumTree::IsCorrect() const {

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

bool AvlSumTree::IsCorrect2() const {

    return isNodeCorrectByMinMax(root, INT_MIN, INT_MAX) ;
}

bool AvlSumTree::isNodeCorrectByMinMax(Node* node, int min, int max) const {

    if (node == nullptr) {
        return true;
    }

    if (node->value < min || node->value > max) {
        return false;
    }

    return isNodeCorrectByMinMax(node->left, min, node->value-1) && isNodeCorrectByMinMax(node->right, node->value + 1, max );
}


std::vector<int> AvlSumTree::Print() const {

    std::vector<int> result;

    Node* current = beginNode() ;

    while ( current != nullptr ) {

        result.push_back(current->value );

        current = nextNode(current) ;
    }

    return result;
}


bool AvlSumTree::isNodeLeftChild(Node* node) const {

    return node->parent->left == node;
}


AvlSumTree::Node* AvlSumTree::minFromNode(Node* node) const {
    
    if (node == nullptr) {

        return nullptr;
    }

    Node* current = node;

    while ( current->left != nullptr) {

        current = current->left;
    }

    return current;

}

AvlSumTree::Node* AvlSumTree::maxFromNode(Node* node) const {
    
    if (node == nullptr) {

        return nullptr;
    }

    Node* current = node;

    while ( current->right != nullptr) {

        current = current->right;
    }

    return current;

}

bool AvlSumTree::hasTwoChildren(Node* node) const {
    
    return node->left != nullptr && node->right != nullptr;
}

std::vector<std::vector<int>> AvlSumTree::PrintByLevels() {
     
        
    std::vector< std::vector<int> > result;
    
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

long long AvlSumTree::SumLessEqual(int val) const {

    long long result = 0;

    Node* current = root;


    while (current != nullptr) {

        if (current->value == val) {

            result += current->value + sum(current->left);

            return result;
        }

        else if (current->value < val) {

            result += current->value + sum(current->left);
            current = current->right;
        }
        else if (current->value > val) {
            
            

            current = current->left;
        }
    }


    return result;
}

long long f( long long i, long long s) {

    return (i + s) % 1000000001;
}

int main() {

    AvlSumTree  sumTree;
    long long s = 0;

    int n ;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {

        std::string command;
        std::cin >> command;

        if (command == "+") {

            int number;
            std::cin >> number;

            sumTree.Insert( f(number, s ) );
        }
        else if (command == "-") {

            int number;
            std::cin >> number;

            sumTree.Erase( f(number, s ) );
        }
        else if (command == "?") {

            int number;
            std::cin >> number;

            if (sumTree.Find( f(number, s )) != nullptr ) {
                std::cout << "Found" << std::endl;
            }
            else {
                std::cout << "Not found" << std::endl;
            }

        }
        else if (command == "s") {

            int l, r;

            std::cin >> l >> r;
            
            int left = f(l, s);
            int right = f(r, s);
            
            if (left > right ) {
                s = 0;
            }
           
            else {
              s =  sumTree.SumLessEqual( right ) - sumTree.SumLessEqual(  left - 1) ;
            }

            

            std::cout << s << std::endl;
        }


    }

    return 0;
}