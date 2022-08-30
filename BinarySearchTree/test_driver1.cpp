
#include <iostream>
#include <cassert>
#include <set>
#include <algorithm>

#include "bst.h"

int main() {

    {

        std::cout << "\nStarting Test 1 \n" << std::endl;

        BinarySearchTree bst;

        std::vector<int> items = {10, 1, -2, 3, 2, 4, 5};


        for (int item : items) {

            BinarySearchTree::Node* newNode = bst.Insert(item);

            assert( newNode->value == item) ;

            assert( bst.IsCorrect() ) ;
            assert( bst.IsCorrect2() ) ;
        }


        for (int item : items) {

            assert( bst.Find(item) != nullptr) ;
        }

        assert( bst.Size() == items.size() ) ;


        std::sort( items.begin(), items.end() ) ;


        for (int i = 0; i < items.size() ; ++i) {


            BinarySearchTree::Node* node = bst.Erase( items[i] ) ;
            assert( bst.IsCorrect() ) ;
            assert( bst.IsCorrect2() ) ;

            if ( i != items.size() - 1) {

                assert(node != nullptr) ;
                assert( node->value == items[i+1] ) ;
                 
            }
            else {
                assert(node == nullptr) ;
            }

            assert( bst.Size() ==  items.size() - 1 );

            assert( bst.Find( items[i]) == nullptr ) ;

            BinarySearchTree::Node* newNode = bst.Insert( items[i] ) ;

            assert(newNode->value == items[i]) ;

            assert( bst.IsCorrect() ) ;
            assert( bst.IsCorrect2() ) ;

            assert( bst.Size() ==  items.size() );
        }

        assert(bst.Min()->value == items[0]);
        assert(bst.Max()->value == items.back() );

        std::cout << "\nTest 1 OK\n" << std::endl;

    }

    
    return 0;
}