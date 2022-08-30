
#include <iostream>
#include <cassert>
#include <stdexcept>

#include "bst.h"

#include <stdlib.h> 
#include <set>
#include <algorithm>

int main() {

    {

        std::cout << "\nStarting Test 1 \n" << std::endl;

        // Test 1

        BST bst;


        // Test empty min

        bool caught_exception_0 = false;

        try {

            int bst_min = bst.min();
        }
        catch (const std::logic_error& e) {

            std::cout << "Caught exception fetching min" << std::endl ;
            std::cout << e.what() << std::endl ;
            
            caught_exception_0 = true;
        }

        assert(caught_exception_0);


        // Test empty max

        bool caught_exception_1 = false;

        try {

            int bst_max = bst.max();
        }
        catch (const std::logic_error& e) {

            std::cout << "Caught exception fetching max" << std::endl ;
            std::cout << e.what() << std::endl ;
            
            caught_exception_1 = true;
        }

        assert(caught_exception_1);

        assert(bst.size() == 0) ;

        bst.insert(8);
        bst.insert(4);
        bst.insert(5);
        bst.insert(8);

        assert(bst.size() == 3) ;

        bst.insert(19);
        bst.insert(15);
        bst.insert(21);

        bst.insert(15);

        assert(bst.size() == 6) ;


        assert(bst.find(15));
        assert(bst.find(5));

        assert(! bst.find(0)) ;

        assert(bst.min() == 4);
        assert(bst.max() == 21);

        std::cout << "\nTest 1 OK\n" << std::endl;
    }

    {
        // Test 2

        std::cout << "\nStarting Test 2 \n" << std::endl;

        BST bst;
        assert( bst.max_height() == 0) ;

        bst.insert(8);
        assert( bst.max_height() == 1) ;


        bst.insert(5);
        bst.insert(12);
        bst.insert(12);
        assert( bst.max_height() == 2) ;
        
        bst.insert(1);
        bst.insert(3);
        bst.insert(2);
        bst.insert(2);
        assert( bst.max_height() == 5) ;

        bst.insert(10);
        bst.insert(9);
        bst.insert(11);
        bst.insert(11);

        bst.insert(15);
        bst.insert(14);
        bst.insert(17);
        bst.insert(17);

        assert( bst.max_height() == 5) ;

        assert( bst.size() == 12) ;

        assert(bst.is_correct() ) ;


        bst.erase(2) ;
        assert(bst.max_height() == 4) ;
        assert(bst.size() == 11) ;
        assert(bst.is_correct() ) ;

        bst.erase(5) ;
        assert(bst.max_height() == 4) ;
        assert(bst.size() == 10) ;
        assert(bst.is_correct() ) ;

        bst.erase(12) ;
        assert(bst.max_height() == 4) ;
        assert(bst.size() == 9) ;
        assert(bst.is_correct() ) ;

        bst.erase(15) ;
        assert(bst.max_height() == 4) ;
        assert(bst.size() == 8) ;
        assert(bst.is_correct() ) ;

        bst.erase(8) ;
        assert(bst.max_height() == 4) ;
        assert(bst.size() == 7) ;
        assert(bst.is_correct() ) ;

        std::vector<int> test_vector{1,3,9,10,11,14,17} ;

        assert( bst.size() == test_vector.size() ) ;

        std::vector<int> bst_vector = bst.print();

        assert( std::equal(bst_vector.begin(), bst_vector.end(), test_vector.begin()  )) ;


        std::cout << "\nTest 2 OK\n" << std::endl;

    }


    {

        std::cout << "\nStarting Test 3 \n" << std::endl;

        BST bst;

        std::set<int> test_set;

        srand(1845);

        for (int i = 0; i < 100; ++i) {

            int temp = rand() % 100 ;

            bst.insert(temp);
            test_set.insert(temp);
        }


        std::vector<int> bst_vector = bst.print();
        std::vector<int> test_vector(test_set.begin(), test_set.end() ) ;

        assert( bst.is_correct() ) ;
        assert( bst_vector.size() == test_vector.size() ) ;
        assert( std::equal(bst_vector.begin(), bst_vector.end(), test_vector.begin()  )) ;


        for (int i = 0; i < 100; ++i) {

            int temp = rand() % 100 ;

            bst.erase(temp);
            test_set.erase(temp);
        }

        std::vector<int> bst_vector1 = bst.print();
        std::vector<int> test_vector1(test_set.begin(), test_set.end() ) ;

        assert( bst.is_correct() ) ;
        assert( bst_vector1.size() == test_vector1.size() ) ;
        assert( std::equal(bst_vector1.begin(), bst_vector1.end(), test_vector1.begin()  )) ;



        std::cout << "\nTest 3 OK\n" << std::endl;
    }

    return 0;
}