
#include <iostream>
#include <cassert>
#include <set>
#include <algorithm>

#include "avl.h"


std::ostream& operator<<( std::ostream& os, const std::vector<int>& v )
{

    os << "[ ";

    for( int i = 0; i < v.size(); ++i ) {

        os << " " << v[i] << " ";
    }

    os << "]";

    return os;
}


void printvv( std::vector< std::vector<int> > && vv) {

    for (auto& v : vv) {

        std::cout << v << std::endl;
    }

}


int main() {

    {

        std::cout << "\nStarting Test 1 \n" << std::endl;

        AvlTree bst;

        std::vector<int> items = {10, 1, -2, 3, 2, 4, 5};


        for (int item : items) {

            AvlTree::Node* newNode = bst.Insert(item);

            assert( newNode->value == item) ;

            assert( bst.IsCorrect() ) ;
            assert( bst.IsCorrect2() ) ;
            assert( bst.IsHeightCorrect() ) ;
        }


        for (int item : items) {

            assert( bst.Find(item) != nullptr) ;
        }

        assert( bst.Size() == items.size() ) ;


        std::sort( items.begin(), items.end() ) ;


        for (int i = 0; i < items.size() ; ++i) {


            AvlTree::Node* node = bst.Erase( items[i] ) ;


            //printvv( bst.PrintByLevels() ) ;

            //std::cout << std::endl;

            assert( bst.IsCorrect() ) ;
            assert( bst.IsCorrect2() ) ;
            assert( bst.IsHeightCorrect() ) ;

            if ( i != items.size() - 1) {

                assert(node != nullptr) ;
                assert( node->value == items[i+1] ) ;
                 
            }
            else {
                assert(node == nullptr) ;
            }

            assert( bst.Size() ==  items.size() - 1 );

            assert( bst.Find( items[i]) == nullptr ) ;

            AvlTree::Node* newNode = bst.Insert( items[i] ) ;

            assert(newNode->value == items[i]) ;

            assert( bst.IsCorrect() ) ;
            assert( bst.IsCorrect2() ) ;
            assert( bst.IsHeightCorrect() ) ;

            assert( bst.Size() ==  items.size() );
        }

        assert(bst.Min()->value == items[0]);
        assert(bst.Max()->value == items.back() );



        for (int i = 0; i < items.size() ; ++i) {

            //std::cout << "Before erase " << items[i] << std::endl;


            //printvv( bst.PrintByLevels() ) ;


            AvlTree::Node* node = bst.Erase( items[i] ) ;

            //std::cout << "After erase " << items[i] << std::endl;

           // printvv( bst.PrintByLevels() ) ;
           // std::cout << std::endl;


            assert( bst.IsCorrect() ) ;
            assert( bst.IsCorrect2() ) ;
            assert( bst.IsHeightCorrect() ) ;

           // std::cout << "is correct after erase " << items[i] << std::endl;

            if ( i != items.size() - 1) {

                assert(node != nullptr) ;
                assert( node->value == items[i+1] ) ;
                 
            }
            else {
                assert(node == nullptr) ;
            }

            assert( bst.Size() ==  items.size() - 1 - i);

            assert( bst.Find( items[i]) == nullptr ) ;

        }

        assert( bst.Size() == 0) ;




        std::cout << "\nTest 1 OK\n" << std::endl;

    }




{

        std::cout << "\nStarting Test 2 \n" << std::endl;

        AvlTree bst;

        std::set<int> testSet;

        srand(6669);

        for (int i = 0; i < 10000; ++i) {

            int newValue = rand() % 10000 ;

            AvlTree::Node* newNode = bst.Insert(newValue);

            assert( newNode->value == newValue );
            
            assert( bst.IsCorrect() ) ;
            assert( bst.IsCorrect2() ) ;
            assert( bst.IsHeightCorrect() ) ;

            testSet.insert( newValue );
        }


        std::vector<int> bstVector = bst.Print();
        std::vector<int> testVector(testSet.begin(), testSet.end() ) ;

        assert( bst.IsCorrect() ) ;
        assert( bst.IsCorrect2() ) ;
        assert( bst.IsHeightCorrect() ) ;

        assert( bstVector.size() == testVector.size() ) ;
        assert( std::equal(bstVector.begin(), bstVector.end(), testVector.begin()  )) ;


        for (int item : bstVector ) {


            AvlTree::Node* nextNode = bst.Erase( item );

            assert( nextNode == nullptr || nextNode->value > item) ;

            assert( bst.IsCorrect() ) ;
            assert( bst.IsCorrect2() ) ;
            assert( bst.IsHeightCorrect() ) ;

            auto it = testSet.upper_bound(item);

            if (it != testSet.end() ) {
                assert(*it == nextNode->value) ;
            }

            testSet.erase(item);

            assert(testSet.size() == bst.Size() ) ;

        }

        



        std::cout << "\nTest 2 OK\n" << std::endl;
    }


    
    return 0;
}