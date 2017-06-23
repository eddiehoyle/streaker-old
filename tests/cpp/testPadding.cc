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

TEST( TestPadding, isNumber ) {

    const std::string number1 = "1";
    bool result1 = isNumber( number1 );
    EXPECT_TRUE( result1 ) << "'" << number1 << "' is not considered a number.";

    const std::string number2 = "00001";
    bool result2 = isNumber( number2 );
    EXPECT_TRUE( result2 ) << "'" << number2 << "' is not considered a number.";

    // Don't support negative frames
    const std::string number3 = "-1000001";
    bool result3 = isNumber( number3 );
    EXPECT_FALSE( result3 ) << "'" << number3 << "' was considered a number.";

    // An alphanumeric frame
    const std::string badNumber1 = "1001e";
    bool resultBadNumber1 = isNumber( badNumber1 );
    EXPECT_FALSE( resultBadNumber1 ) << "'" << badNumber1 << "' was considered a number.";
}

TEST( TestPadding, isHash ) {

    // Single #
    const std::string hashA = "#";
    bool result1 = isHash( hashA );
    EXPECT_TRUE( result1 ) << "'" << hashA << "' is not considered a hash string.";

    // Multi #
    const std::string hashB = "####";
    bool result2 = isHash( hashB );
    EXPECT_TRUE( result2 ) << "'" << hashB << "' is not considered a hash string.";

    // Mixed #
    const std::string mixedHash = "##@@";
    bool result3 = isHash( mixedHash );
    EXPECT_FALSE( result3 ) << "'" << mixedHash << "' is considered a hash string.";

    // Non #
    const std::string nonHash = "abcdef";
    bool result4 = isHash( nonHash );
    EXPECT_FALSE( result4 ) << "'" << nonHash << "' is considered a hash string.";
}

TEST( TestPadding, isAt ) {

    // Single @
    const std::string atA = "@";
    bool result1 = isAt( atA );
    EXPECT_TRUE( result1 ) << "'" << atA << "' is not considered an '@' string.";

    // Multi @
    const std::string atB = "@@@@";
    bool result2 = isAt( atB );
    EXPECT_TRUE( result2 ) << "'" << atB << "' is not considered an '@' string.";

    // Mixed @
    const std::string mixedAt = "##@@";
    bool result3 = isAt( mixedAt );
    EXPECT_FALSE( result3 ) << "'" << mixedAt << "' is considered an '@' string.";

    // Non @
    const std::string nonAt = "abcdef";
    bool result4 = isAt( nonAt );
    EXPECT_FALSE( result4 ) << "'" << nonAt << "' is considered an '@' string.";
}

TEST( TestPadding, isAmbiguous ) {

    // Eg: "1"
    unsigned int frameA = 1;
    unsigned int paddingA = 1;
    bool resultA = isAmbiguous( frameA, paddingA );
    EXPECT_TRUE( resultA );

    // Eg: "1001"
    unsigned int frameB = 1001;
    unsigned int paddingB = 4;
    bool resultB = isAmbiguous( frameB, paddingB );
    EXPECT_TRUE( resultB );

    // Eg: "0001"
    unsigned int frameC = 1;
    unsigned int paddingC = 4;
    bool resultC = isAmbiguous( frameC, paddingC );
    EXPECT_FALSE( resultC );
}