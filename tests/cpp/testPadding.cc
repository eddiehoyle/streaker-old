//
// Created by Eddie Hoyle on 18/06/17.
//
#include <gtest/gtest.h>
#include <padding.hh>

TEST( TestPadding, countDigits ) {

    unsigned int digit1 = countDigits( 1 );
    unsigned int digit2 = countDigits( 10 );
    unsigned int digit3 = countDigits( 100 );
    unsigned int digit4 = countDigits( 1000 );
    unsigned int digit5 = countDigits( 10000 );
    unsigned int digit6 = countDigits( 100000 );
    unsigned int digit7 = countDigits( 1000000 );
    unsigned int digit8 = countDigits( 10000000 );
    unsigned int digit9 = countDigits( 100000000 );

    EXPECT_EQ( digit1, 1 ) << "Wrong number of digits";
    EXPECT_EQ( digit2, 2 ) << "Wrong number of digits";
    EXPECT_EQ( digit3, 3 ) << "Wrong number of digits";
    EXPECT_EQ( digit4, 4 ) << "Wrong number of digits";
    EXPECT_EQ( digit5, 5 ) << "Wrong number of digits";
    EXPECT_EQ( digit6, 6 ) << "Wrong number of digits";
    EXPECT_EQ( digit7, 7 ) << "Wrong number of digits";
    EXPECT_EQ( digit8, 8 ) << "Wrong number of digits";
    EXPECT_EQ( digit9, 9 ) << "Wrong number of digits";
}

TEST( TestPadding, isAmbiguous ) {

    // Eg: "1"
    unsigned int frameA = 1;
    unsigned int paddingA = 1;
    bool resultA = isAmbiguous( frameA, paddingA );
    EXPECT_TRUE( resultA ) << frameA << "/" << paddingA << " is not considered ambiguous";

    // Eg: "1001"
    unsigned int frameB = 1001;
    unsigned int paddingB = 4;
    bool resultB = isAmbiguous( frameB, paddingB );
    EXPECT_TRUE( resultB )  << frameB << "/" << paddingB << " is not considered ambiguous";

    // Eg: "0001"
    unsigned int frameC = 1;
    unsigned int paddingC = 4;
    bool resultC = isAmbiguous( frameC, paddingC );
    EXPECT_FALSE( resultC )  << frameC << "/" << paddingC << " is considered ambiguous";
}