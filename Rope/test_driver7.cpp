
#include <iostream>
#include <cassert>
#include <set>
#include <algorithm>

#include "rope.h"


std::ostream& operator<<( std::ostream& os, const std::vector<char>& v )
{

    os << "[ ";

    for( int i = 0; i < v.size(); ++i ) {

        os << " " << v[i] << " ";
    }

    os << "]";

    return os;
}


void printvv( const std::vector< std::vector<char> > & vv) {

    for (auto& v : vv) {

        std::cout << v << std::endl;
    }

}


int main() {

    {

        std::cout << "\nStarting Test 1 \n" << std::endl;

        AvlSMTree avl;

        std::string s = "helloworldprogrammers" ;


        for (int j = 0; j < s.size() + 1; ++j) {

    
            for (char c : s) {

                AvlSMTree prevTree = std::move( avl );

                AvlSMTree nextTree(c);

                AvlSMTree mergedTree = AvlSMTree::Merge(prevTree, nextTree);

                avl = std::move(mergedTree) ;

            }


            assert( avl.IsSizeCorrect() ) ;
            assert( avl.IsHeightCorrect() ) ;
            assert( avl.IsBalanced() ) ;


            std::vector<char> v = avl.Print();

            //std::cout << v << std::endl;


            for (int i = 0; i < s.size() ; ++i ) {

                assert( avl.OrderStatistics(i+1)->value == s[i] ) ;
            }


            auto [T1, T2] = AvlSMTree::SplitAVL(avl, j) ;

            assert( T1.IsSizeCorrect() ) ;
            assert( T1.IsHeightCorrect() ) ;
            assert( T1.IsBalanced() ) ;

            std::vector<char> v1 = T1.Print();
            std::cout << v1 << " " ;


            assert( T2.IsSizeCorrect() ) ;
            assert( T2.IsHeightCorrect() ) ;
            assert( T2.IsBalanced() ) ;

            std::vector<char> v2 = T2.Print();
            std::cout << v2 << std::endl;

        }


        std::cout << "\nTest 1 OK\n" << std::endl;

    }




    
    return 0;
}