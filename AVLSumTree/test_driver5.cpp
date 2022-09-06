
#include <iostream>
#include <cassert>
#include <set>
#include <algorithm>

#include "avlsum.h"


std::ostream& operator<<( std::ostream& os, const std::vector<int>& v )
{

    os << "[ ";

    for( int i = 0; i < v.size(); ++i ) {

        os << " " << v[i] << " ";
    }

    os << "]";

    return os;
}


void printvv( const std::vector< std::vector<int> > & vv) {

    for (auto& v : vv) {

        std::cout << v << std::endl;
    }

}


int main() {

    {

        std::cout << "\nStarting Test 1 \n" << std::endl;

        AvlSumTree avl;

        std::vector<int> items = {10, 1, -2, 3, 2, 4, 5};

        


        for (int item : items) {

            AvlSumTree::Node* newNode = avl.Insert(item);

            assert( newNode->value == item) ;

            assert( avl.IsCorrect() ) ;
            assert( avl.IsCorrect2() ) ;
            assert( avl.IsHeightCorrect() ) ;
            assert( avl.IsSumCorrect() ) ;
            
        }


        for (int item : items) {

            assert( avl.Find(item) != nullptr) ;
        }

        assert( avl.Size() == items.size() ) ;


        std::sort( items.begin(), items.end() ) ;

        std::vector<int> sums;
        sums.push_back(items[0]);

        for (int i = 1; i < items.size() ; ++i) {

            sums.push_back( sums.back() + items[i] ) ;
        }


        for (int i = 0; i < items.size() ; ++i ) {

            assert( avl.SumLessEqual(items[i]) == sums[i]) ;
        }


        for (int i = 0; i < items.size() ; ++i) {


            AvlSumTree::Node* node = avl.Erase( items[i] ) ;

            if (i == 0) {

                assert( avl.SumLessEqual(items[i]) == 0) ;
            }
            else {
                assert( avl.SumLessEqual(items[i]) == sums[i-1]) ;
            }

            assert( avl.IsCorrect() ) ;
            assert( avl.IsCorrect2() ) ;
            assert( avl.IsHeightCorrect() ) ;
            assert( avl.IsSumCorrect() ) ;

            if ( i != items.size() - 1) {

                assert(node != nullptr) ;
                assert( node->value == items[i+1] ) ;
                 
            }
            else {
                assert(node == nullptr) ;
            }

            assert( avl.Size() ==  items.size() - 1 );

            assert( avl.Find( items[i]) == nullptr ) ;

            AvlSumTree::Node* newNode = avl.Insert( items[i] ) ;

            assert(newNode->value == items[i]) ;

            assert( avl.IsCorrect() ) ;
            assert( avl.IsCorrect2() ) ;
            assert( avl.IsHeightCorrect() ) ;
            assert( avl.IsSumCorrect() ) ;

            assert( avl.SumLessEqual(items[i]) == sums[i]) ;

            assert( avl.Size() ==  items.size() );
        }

        assert(avl.Min()->value == items[0]);
        assert(avl.Max()->value == items.back() );



        for (int i = 0; i < items.size() ; ++i) {


            AvlSumTree::Node* node = avl.Erase( items[i] ) ;

            assert( avl.IsCorrect() ) ;
            assert( avl.IsCorrect2() ) ;
            assert( avl.IsHeightCorrect() ) ;
            assert( avl.IsSumCorrect() ) ;

            if ( i != items.size() - 1) {

                assert(node != nullptr) ;
                assert( node->value == items[i+1] ) ;
                 
            }
            else {
                assert(node == nullptr) ;
            }

            assert( avl.Size() ==  items.size() - 1 - i);

            assert( avl.Find( items[i]) == nullptr ) ;

        }

        assert( avl.Size() == 0) ;

        std::cout << "\nTest 1 OK\n" << std::endl;

    }

    {
        std::cout << "\nStarting Test 2 \n" << std::endl;

        AvlSumTree avl;

        std::set<int> testSet;

        srand(1666978);

        for (int i = 0; i < 10000; ++i) {

            int newValue = rand() % 10000 ;

            AvlSumTree::Node* newNode = avl.Insert(newValue);

            assert( newNode->value == newValue );
            
            assert( avl.IsCorrect() ) ;
            assert( avl.IsCorrect2() ) ;
            assert( avl.IsHeightCorrect() ) ;
            assert( avl.IsSumCorrect() ) ;

            assert( avl.SumLessEqual(newValue) - avl.SumLessEqual(newValue - 1) == newValue ) ;

            testSet.insert( newValue );
        }


        std::vector<int> avlVector = avl.Print();
        std::vector<int> testVector(testSet.begin(), testSet.end() ) ;

        assert( avl.IsCorrect() ) ;
        assert( avl.IsCorrect2() ) ;
        assert( avl.IsHeightCorrect() ) ;
        assert( avl.IsSumCorrect() ) ;

        assert( avlVector.size() == testVector.size() ) ;
        assert( std::equal(avlVector.begin(), avlVector.end(), testVector.begin()  )) ;


        for (int item : avlVector ) {


            AvlSumTree::Node* nextNode = avl.Erase( item );

            assert( nextNode == nullptr || nextNode->value > item) ;

            assert( avl.IsCorrect() ) ;
            assert( avl.IsCorrect2() ) ;
            assert( avl.IsHeightCorrect() ) ;
            assert( avl.IsSumCorrect() ) ;

            auto it = testSet.upper_bound(item);

            if (it != testSet.end() ) {
                assert(*it == nextNode->value) ;
            }

            testSet.erase(item);

            assert(testSet.size() == avl.Size() ) ;

        }

        std::cout << "\nTest 2 OK\n" << std::endl;
    }

    {

        std::cout << "\nStarting Test 3 \n" << std::endl;

        AvlSumTree avl;


        int n = 1000;

        for (int i = 0; i < n; ++i) {

            AvlSumTree::Node* node = avl.Insert(i) ;

            assert( node->value == i ) ;

            assert( avl.IsCorrect() ) ;
            assert( avl.IsCorrect2() ) ;
            assert( avl.IsHeightCorrect() ) ;
            assert( avl.IsSumCorrect() ) ;

        }

        for (int i = 0; i < n-1; i += 5) {

            AvlSumTree::Node* node = avl.Erase(i) ;

            assert( node->value == i+1 ) ;

            assert( avl.IsCorrect() ) ;
            assert( avl.IsCorrect2() ) ;
            assert( avl.IsHeightCorrect() ) ;
            assert( avl.IsSumCorrect() ) ;

        }
        
        std::cout << "\nTest 3 OK\n" << std::endl;

    }

    
    return 0;
}