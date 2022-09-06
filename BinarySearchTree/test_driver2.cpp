#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <set>

#include "bst.h"

int main(int argc, char *argv[]) {

    int n = std::atoi(argv[1]) ;
    int seed = std::atoi(argv[2]) ;
    std::string type(argv[3]) ;
    std::string mode(argv[4]) ;

    std::cout << n << " " << seed << " " << type << std::endl;

    if (type == "bst") {

        BinarySearchTree bst;

        srand(seed);

        for (int i = 0; i < n; ++i) {

            int newValue = mode == "random" ? rand() % n : i;
        
            BinarySearchTree::Node* newNode = bst.Insert(newValue);

        }

        std::vector<int> bstVector = bst.Print();

        for (int item : bstVector ) {

            BinarySearchTree::Node* nextNode = bst.Erase( item );

        }
    }

    else {

        std::set<int> set;

        srand(seed);

        for (int i = 0; i < n; ++i) {

            int newValue = mode == "random" ? rand() % n : i;
            set.insert(newValue);

        }

        std::vector<int> setVector(set.begin(), set.end() );

        for (int item : setVector ) {

            set.erase( item );
        }

    }

    return 0;
}