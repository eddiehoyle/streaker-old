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

TEST( TestPadding, getNumberOfDigits ) {

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

    unsigned int negativeAigit1 = getNumberOfDigits( -1 );
    unsigned int negativeAigit2 = getNumberOfDigits( -10 );
    unsigned int negativeAigit3 = getNumberOfDigits( -100 );
    unsigned int negativeAigit4 = getNumberOfDigits( -1000 );
    unsigned int negativeAigit5 = getNumberOfDigits( -10000 );
    unsigned int negativeAigit6 = getNumberOfDigits( -100000 );
    unsigned int negativeAigit7 = getNumberOfDigits( -1000000 );
    unsigned int negativeAigit8 = getNumberOfDigits( -10000000 );
    unsigned int negativeAigit9 = getNumberOfDigits( -100000000 );

    EXPECT_EQ( negativeAigit1, 1 ) << "Wrong number of digits";
    EXPECT_EQ( negativeAigit2, 2 ) << "Wrong number of digits";
    EXPECT_EQ( negativeAigit3, 3 ) << "Wrong number of digits";
    EXPECT_EQ( negativeAigit4, 4 ) << "Wrong number of digits";
    EXPECT_EQ( negativeAigit5, 5 ) << "Wrong number of digits";
    EXPECT_EQ( negativeAigit6, 6 ) << "Wrong number of digits";
    EXPECT_EQ( negativeAigit7, 7 ) << "Wrong number of digits";
    EXPECT_EQ( negativeAigit8, 8 ) << "Wrong number of digits";
    EXPECT_EQ( negativeAigit9, 9 ) << "Wrong number of digits";
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


TEST( TestPadding, extractPadding ) {

    // An ambiguous padded frame
    const std::string ambiguousA = "1";
    unsigned int paddingAmbiguousA = 0;
    bool resultAmbiguousA = extractPadding( ambiguousA, paddingAmbiguousA );
    unsigned int expectedAmbiguousA = 1;
    EXPECT_EQ( paddingAmbiguousA, expectedAmbiguousA )
                        << "Extracted wrong value from ambiguous frame. Got="
                        << paddingAmbiguousA << ", expected=" << expectedAmbiguousA;
    EXPECT_TRUE( resultAmbiguousA ) << "Expected ambiguous padding result "
                                    << ambiguousA << " to be True.";

    // An ambiguous padded frame
    const std::string ambiguousB = "1001";
    unsigned int paddingAmbiguousB = 0;
    bool resultAmbiguousB = extractPadding( ambiguousB, paddingAmbiguousB );
    unsigned int expectedAmbiguousB = 4;
    EXPECT_EQ( paddingAmbiguousB, expectedAmbiguousB )
                        << "Extracted wrong value from ambiguous frame. Got="
                        << paddingAmbiguousB << ", expected=" << expectedAmbiguousB;
    EXPECT_TRUE( resultAmbiguousB ) << "Expected ambiguous padding result "
                                    << ambiguousB << " to be True.";

    // A filled frame
    const std::string filledA = "0";
    unsigned int paddingFilledA = 0;
    bool resultFilledA = extractPadding( filledA, paddingFilledA );
    unsigned int expectedFilledA = 1;
    EXPECT_EQ( paddingFilledA, expectedFilledA )
                        << "Extracted wrong value from filled frame. Got="
                        << paddingFilledA << ", expected=" << expectedFilledA;
    EXPECT_TRUE( resultFilledA ) << "Expected filled padding result "
                                 << filledA << " to be True.";

    // A filled frame
    const std::string filledB = "00001";
    unsigned int paddingFilledB = 0;
    bool resultFilledB = extractPadding( filledB, paddingFilledB );
    unsigned int expectedFilledB = 5;
    EXPECT_EQ( paddingFilledB, expectedFilledB )
                        << "Extracted wrong value from filled frame. Got="
                        << paddingFilledB << ", expected=" << expectedFilledB;
    EXPECT_TRUE( resultFilledB ) << "Expected filled padding result "
                                 << filledB << " to be True.";

    // A #
    const std::string hashA = "#";
    unsigned int paddingHashA = 0;
    bool resultHashA = extractPadding( hashA, paddingHashA );
    unsigned int expectedHashA = 4;
    EXPECT_EQ( paddingHashA, expectedHashA )
                        << "Extracted wrong value from hash frame. Got="
                        << paddingHashA << ", expected=" << expectedHashA;
    EXPECT_TRUE( resultHashA ) << "Expected hash padding result "
                               << hashA << " to be True.";

    // Multi #
    const std::string hashB = "##";
    unsigned int paddingHashB = 0;
    bool resultHashB = extractPadding( hashB, paddingHashB );
    unsigned int expectedHashB = 8;
    EXPECT_EQ( paddingHashB, expectedHashB )
                        << "Extracted wrong value from hash frame. Got="
                        << paddingHashB << ", expected=" << expectedHashB;
    EXPECT_TRUE( resultHashB ) << "Expected hash padding result "
                               << hashB << " to be True.";

    // An @
    const std::string atA = "@";
    unsigned int paddingAtA = 0;
    bool resultAtA = extractPadding( atA, paddingAtA );
    unsigned int expectedAtA = 1;
    EXPECT_EQ( paddingAtA, expectedAtA )
                        << "Extracted wrong value from at frame. Got="
                        << paddingAtA << ", expected=" << expectedAtA;
    EXPECT_TRUE( resultAtA ) << "Expected at padding result "
                             << atA << " to be True.";

    // Multi @
    const std::string atB = "@@@";
    unsigned int paddingAtB = 0;
    bool resultAtB = extractPadding( atB, paddingAtB );
    unsigned int expectedAtB = 3;
    EXPECT_EQ( paddingAtB, expectedAtB )
                        << "Extracted wrong value from at frame. Got="
                        << paddingAtB << ", expected=" << expectedAtB;
    EXPECT_TRUE( resultAtB ) << "Expected at padding result "
                             << atB << " to be True.";

    // An empty frame
    const std::string emptyA = "";
    unsigned int paddingEmptyA = 0;
    bool resultEmptyA = extractPadding( emptyA, paddingEmptyA );
    unsigned int expectedEmptyA = 0;
    EXPECT_EQ( paddingEmptyA, expectedEmptyA )
                        << "Extracted wrong value from empty frame. Got="
                        << paddingEmptyA << ", expected=" << expectedEmptyA;
    EXPECT_FALSE( resultEmptyA ) << "Expected empty padding result "
                                 << emptyA << " to be False.";

    // A negative frame
    const std::string negativeA = "-1";
    unsigned int paddingNegativeA = 0;
    bool resultNegativeA = extractPadding( negativeA, paddingNegativeA );
    unsigned int expectedNegativeA = 0;
    EXPECT_EQ( paddingNegativeA, expectedNegativeA )
                        << "Extracted wrong value from negative frame. Got="
                        << paddingNegativeA << ", expected=" << expectedNegativeA;
    EXPECT_FALSE( resultNegativeA ) << "Expected negative padding result "
                                   << negativeA << " to be False.";

    // A non-numeric frame
    const std::string alphaA = "abcdef";
    unsigned int paddingAlphaA = 0;
    bool resultAlphaA = extractPadding( alphaA, paddingAlphaA );
    unsigned int expectedAlphaA = 0;
    EXPECT_EQ( paddingAlphaA, expectedAlphaA )
                        << "Extracted wrong value from alpha frame. Got="
                        << paddingAlphaA << ", expected=" << expectedAlphaA;
    EXPECT_FALSE( resultAlphaA ) << "Expected alpha padding result "
                                << alphaA << " to be False.";
}

TEST( TestPadding, getPaddingType ) {

    // Eg: "1"
    int frameA = 1;
    unsigned int paddingA = 1;
    PaddingType resultA = getPaddingType( frameA, paddingA );
    EXPECT_EQ( resultA, kAmbiguous );

    // Eg: "1001"
    int frameB = 1001;
    unsigned int paddingB = 4;
    PaddingType resultB = getPaddingType( frameB, paddingB );
    EXPECT_EQ( resultB, kAmbiguous );

    // Eg: "0001"
    int frameC = 1;
    unsigned int paddingC = 4;
    PaddingType resultC = getPaddingType( frameC, paddingC );
    EXPECT_EQ( resultC, kFilled);
}