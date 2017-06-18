//
// Created by Eddie Hoyle on 18/06/17.
//
#include <gtest/gtest.h>
#include <padding.hh>

TEST( TestPadding, PaddingType_enum ) {

    PaddingType ambiguous = kAmbiguous; // 0
    PaddingType filled = kFilled; // 1

    EXPECT_EQ( ambiguous, 0 ) << "Wrong 'ambiguous' enum value";
    EXPECT_EQ( filled, 1 ) << "Wrong 'filled' enum value";
}

TEST( TestPadding, getNumberOfDigits_positive ) {

    unsigned int digit1 = getNumberOfDigits( 1 );
    unsigned int digit2 = getNumberOfDigits( 10 );
    unsigned int digit3 = getNumberOfDigits( 100 );
    unsigned int digit4 = getNumberOfDigits( 1000 );
    unsigned int digit5 = getNumberOfDigits( 10000 );
    unsigned int digit6 = getNumberOfDigits( 100000 );
    unsigned int digit7 = getNumberOfDigits( 1000000 );
    unsigned int digit8 = getNumberOfDigits( 10000000 );
    unsigned int digit9 = getNumberOfDigits( 100000000 );

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

TEST( TestPadding, getNumberOfDigits_negative ) {

    unsigned int digit1 = getNumberOfDigits( -1 );
    unsigned int digit2 = getNumberOfDigits( -10 );
    unsigned int digit3 = getNumberOfDigits( -100 );
    unsigned int digit4 = getNumberOfDigits( -1000 );
    unsigned int digit5 = getNumberOfDigits( -10000 );
    unsigned int digit6 = getNumberOfDigits( -100000 );
    unsigned int digit7 = getNumberOfDigits( -1000000 );
    unsigned int digit8 = getNumberOfDigits( -10000000 );
    unsigned int digit9 = getNumberOfDigits( -100000000 );

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

TEST( TestPadding, isNumber ) {

    const std::string number1 = "1";
    bool result1 = isNumber( number1 );
    EXPECT_TRUE( result1 ) << "'" << number1 << "' is not considered a number.";

    const std::string number2 = "00001";
    bool result2 = isNumber( number2 );
    EXPECT_TRUE( result2 ) << "'" << number2 << "' is not considered a number.";

    const std::string number3 = "-1000001";
    bool result3 = isNumber( number3 );
    EXPECT_TRUE( result3 ) << "'" << number3 << "' is not considered a number.";
}