#include <cstdio>
#include <iostream>
#include "streaker.hh"

int main( int argc, char** argv ) {

    const std::string hello = "/Users/eddiehoyle/Code/cpp/streaker/resources/hello.#.png";
    findStreak( hello );
    const std::string test = "/Users/eddiehoyle/Code/cpp/streaker/resources/test.#.txt";
    findStreak( test );

    const std::string blah = "/Users/eddiehoyle/Code/cpp/streaker/resources/blah.#.txt";
    findStreak( blah );

    return 0;
}