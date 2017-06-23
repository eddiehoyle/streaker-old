#include <cstdio>
#include <iostream>
#include "streaker.hh"
#include <parser.hh>

int main( int argc, char** argv ) {

//    const std::string hello = "/Users/eddiehoyle/Code/cpp/streaker/resources/hello.####.png";
//    findStreak( hello );

//    const std::string test = "/Users/eddiehoyle/Code/cpp/streaker/resources/test.@.txt";
//    const std::string test = "/Users/eddiehoyle/Code/cpp/streaker/resources/test.@@@.txt";
//    findStreak( test );

    std::string single = "test.@@@@@@@.txt";
    std::string name, ext;
    unsigned int padding;
    parseSequence( single, name, padding, ext );
    printf( "%s, %d, %s", name.c_str(), padding, ext.c_str() );

//    int* x = nullptr;
//    *x = 10;

//    printf( "%s, %d, %d, %s", name.c_str(), frame, padding, ext.c_str() );
//    const std::string blah = "/Users/eddiehoyle/Code/cpp/streaker/resources/blah.####.txt";
//    findStreak( blah );

    return 0;
}