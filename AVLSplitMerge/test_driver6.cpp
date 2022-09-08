
#include <iostream>
#include <cassert>
#include <set>
#include <algorithm>

#include "avlsm.h"


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

        AvlSMTree avl;

        std::vector<int> items = {10, 1, -2, 3, 2, 4, 5};

        


        for (int item : items) {

            AvlSMTree::Node* newNode = avl.Insert(item);

            assert( newNode->value == item) ;

            assert( avl.IsCorrect() ) ;
            assert( avl.IsCorrect2() ) ;
            assert( avl.IsHeightCorrect() ) ;
            assert( avl.IsSizeCorrect() ) ;
            assert( avl.IsBalanced() ) ;
            
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

          //  assert( avl.SumLessEqual(items[i]) == sums[i]) ;
        }


        for (int i = 0; i < items.size() ; ++i) {


            AvlSMTree::Node* node = avl.Erase( items[i] ) ;

            if (i == 0) {

             //   assert( avl.SumLessEqual(items[i]) == 0) ;
            }
            else {
             //   assert( avl.SumLessEqual(items[i]) == sums[i-1]) ;
            }

            assert( avl.IsCorrect() ) ;
            assert( avl.IsCorrect2() ) ;
            assert( avl.IsHeightCorrect() ) ;
            assert( avl.IsSizeCorrect() ) ;
            assert( avl.IsBalanced() ) ;

            if ( i != items.size() - 1) {

                assert(node != nullptr) ;
                assert( node->value == items[i+1] ) ;
                 
            }
            else {
                assert(node == nullptr) ;
            }

            assert( avl.Size() ==  items.size() - 1 );

            assert( avl.Find( items[i]) == nullptr ) ;

            AvlSMTree::Node* newNode = avl.Insert( items[i] ) ;

            assert(newNode->value == items[i]) ;

            assert( avl.IsCorrect() ) ;
            assert( avl.IsCorrect2() ) ;
            assert( avl.IsHeightCorrect() ) ;
            assert( avl.IsSizeCorrect() ) ;
            assert( avl.IsBalanced() ) ;

            //assert( avl.SumLessEqual(items[i]) == sums[i]) ;

            assert( avl.Size() ==  items.size() );
        }

        assert(avl.Min()->value == items[0]);
        assert(avl.Max()->value == items.back() );



        for (int i = 0; i < items.size() ; ++i) {


            AvlSMTree::Node* node = avl.Erase( items[i] ) ;

            assert( avl.IsCorrect() ) ;
            assert( avl.IsCorrect2() ) ;
            assert( avl.IsHeightCorrect() ) ;
            assert( avl.IsSizeCorrect() ) ;
            assert( avl.IsBalanced() ) ;

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

        AvlSMTree avl;

        std::set<int> testSet;

        srand(1666978);

        for (int i = 0; i < 1000; ++i) {

            int newValue = rand() % 1000 ;

            AvlSMTree::Node* newNode = avl.Insert(newValue);

            assert( newNode->value == newValue );
            
            assert( avl.IsCorrect() ) ;
            assert( avl.IsCorrect2() ) ;
            assert( avl.IsHeightCorrect() ) ;
            assert( avl.IsSizeCorrect() ) ;
            assert( avl.IsBalanced() ) ;

           // assert( avl.SumLessEqual(newValue) - avl.SumLessEqual(newValue - 1) == newValue ) ;

            testSet.insert( newValue );
        }


        std::vector<int> avlVector = avl.Print();
        std::vector<int> testVector(testSet.begin(), testSet.end() ) ;

        assert( avl.IsCorrect() ) ;
        assert( avl.IsCorrect2() ) ;
        assert( avl.IsHeightCorrect() ) ;
        assert( avl.IsSizeCorrect() ) ;
        assert( avl.IsBalanced() ) ;

        assert( avlVector.size() == testVector.size() ) ;
        assert( std::equal(avlVector.begin(), avlVector.end(), testVector.begin()  )) ;


        for (int item : avlVector ) {


            AvlSMTree::Node* nextNode = avl.Erase( item );

            assert( nextNode == nullptr || nextNode->value > item) ;

            assert( avl.IsCorrect() ) ;
            assert( avl.IsCorrect2() ) ;
            assert( avl.IsHeightCorrect() ) ;
            assert( avl.IsSizeCorrect() ) ;
            assert( avl.IsBalanced() ) ;

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

        AvlSMTree avl;


        int n = 1000;

        for (int i = 0; i < n; ++i) {

            AvlSMTree::Node* node = avl.Insert(i) ;

            assert( node->value == i ) ;

            assert( avl.IsCorrect() ) ;
            assert( avl.IsCorrect2() ) ;
            assert( avl.IsHeightCorrect() ) ;
            assert( avl.IsSizeCorrect() ) ;
            assert( avl.IsBalanced() ) ;

        }

        for (int i = 0; i < n-1; i += 5) {

            AvlSMTree::Node* node = avl.Erase(i) ;

            assert( node->value == i+1 ) ;

            assert( avl.IsCorrect() ) ;
            assert( avl.IsCorrect2() ) ;
            assert( avl.IsHeightCorrect() ) ;
            assert( avl.IsSizeCorrect() ) ;
            assert( avl.IsBalanced() ) ;

        }
        
        std::cout << "\nTest 3 OK\n" << std::endl;

    }

    {

        std::cout << "\nStarting Test 4 \n" << std::endl;

        AvlSMTree T1, T2;



        std::vector<int> v1, v2;

        for (int i = 0; i < 100; ++i) {
            v1.push_back(i) ;
            T1.Insert(i);
        }

        for (int i = 200; i < 201; ++i) {

            v2.push_back(i);
            T2.Insert(i);
        }


        AvlSMTree T3 = AvlSMTree::Merge(T1, T2);

        assert( T3.IsCorrect() ) ;
        assert( T3.IsCorrect2() ) ;
        assert( T3.IsSizeCorrect() ) ;

        assert( T3.IsHeightCorrect() ) ;

        assert (T3.IsBalanced() ) ;

        assert( T3.Size() == v1.size() + v2.size() ) ;


        
        std::cout << "\nTest 4 OK\n" << std::endl;

    }


    {

    #define TEST_SIZE 1000    

        std::cout << "\nStarting Test 5 \n" << std::endl;


        for (int j = -1; j < TEST_SIZE + 1; ++j) {

            AvlSMTree avl;


            for (int i = 0; i < TEST_SIZE ; ++i) {

                avl.Insert(i) ;
            }

            auto [T1, T2] = AvlSMTree::SplitAVL(avl, j) ;

            assert( T1.IsCorrect() ) ;
            assert( T1.IsCorrect2() ) ;
            assert( T1.IsSizeCorrect() ) ;
            assert( T1.IsHeightCorrect() ) ;
            assert (T1.IsBalanced() ) ;

            
            if (j == -1) {
                
                assert(T1.Size() == 0) ;
            }
            else if (j == TEST_SIZE ) {

                assert(T1.Size() == TEST_SIZE ) ;
                T1.Max()->value = TEST_SIZE ;
            }
            else {
                
                assert( T1.Size() == j + 1) ;
                T1.Max()->value = j;
            }


            assert( T2.IsCorrect() ) ;
            assert( T2.IsCorrect2() ) ;
            assert( T2.IsSizeCorrect() ) ;
            assert( T2.IsHeightCorrect() ) ;
            assert (T2.IsBalanced() ) ;


            if (j == -1) {

                assert(T2.Size() == TEST_SIZE ) ;
                T2.Min()->value = 0;
            }
            else if (j == TEST_SIZE ) {
                
                assert(T2.Size() == 0) ;
            }
            else {
                
                assert( T2.Size() == TEST_SIZE - j - 1) ;

                if (T2.Size() != 0)  {

                    T2.Min()->value = j+1;
                }
            }

        }


        std::cout << "\nTest 5 OK\n" << std::endl;

    }


    
    return 0;
}