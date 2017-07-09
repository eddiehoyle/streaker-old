//
// Created by Eddie Hoyle on 23/06/17.
//

#include <gtest/gtest.h>
#include <streaker/Parser.hh>

TEST( TestParser, parseFrame ) {

    // Simple filename
    const std::string filenameA = "image.1.png";
    std::string nameA, extensionA;
    unsigned int frameA, paddingA;
    bool resultA = parseFrame( filenameA,
                               nameA,
                               frameA,
                               paddingA,
                               extensionA );
    EXPECT_TRUE( resultA ) << "Filename did not return true when parsed: " << filenameA;
    EXPECT_EQ( nameA, "image" ) << nameA << " != image";
    EXPECT_EQ( frameA, 1 ) << frameA << " != 1";
    EXPECT_EQ( paddingA, 1 ) << paddingA << " != 1";
    EXPECT_EQ( extensionA, "png" ) << extensionA << " != png";

    // Padded filename
    const std::string filenameB = "image.0001.png";
    std::string nameB, extensionB;
    unsigned int frameB, paddingB;
    bool resultB = parseFrame( filenameB,
                               nameB,
                               frameB,
                               paddingB,
                               extensionB );
    EXPECT_TRUE( resultB ) << "Filename returned true when parsed: " << filenameB;
    EXPECT_EQ( nameB, "image" ) << nameB << " != image";
    EXPECT_EQ( frameB, 1 ) << frameB << " != 1";
    EXPECT_EQ( paddingB, 4 ) << paddingB << " != 4";
    EXPECT_EQ( extensionB, "png" ) << extensionB << " != png";

    // Longer frame number
    const std::string filenameC = "image.24017.png";
    std::string nameC, extensionC;
    unsigned int frameC, paddingC;
    bool resultC = parseFrame( filenameC,
                               nameC,
                               frameC,
                               paddingC,
                               extensionC );
    EXPECT_TRUE( resultC ) << "Filename returned true when parsed: " << filenameC;
    EXPECT_EQ( nameC, "image" ) << nameC << " != image";
    EXPECT_EQ( frameC, 24017 ) << frameC << " != 24017";
    EXPECT_EQ( paddingC, 5 ) << paddingC << " != 5";
    EXPECT_EQ( extensionC, "png" ) << extensionC << " != png";

    // Bad frame number
    const std::string filenameD = "image.213e10.png";
    std::string nameD, extensionD;
    unsigned int frameD, paddingD;
    bool resultD = parseFrame( filenameD,
                               nameD,
                               frameD,
                               paddingD,
                               extensionD );
    EXPECT_FALSE( resultD ) << "Filename returned true when parsed: " << filenameD;

    // Directory as file
    const std::string filenameE = "/file/to/frame";
    std::string nameE, extensionE;
    unsigned int frameE, paddingE;
    bool resultE = parseFrame( filenameE,
                               nameE,
                               frameE,
                               paddingE,
                               extensionE );
    EXPECT_FALSE( resultE ) << "Directory was considered a filename: " << filenameE;

    // Sequence instead of frame number
    const std::string filenameF = "image.#.png";
    std::string nameF, extensionF;
    unsigned int frameF, paddingF;
    bool resultF = parseFrame( filenameF,
                               nameF,
                               frameF,
                               paddingF,
                               extensionF );
    EXPECT_FALSE( resultF ) << "Filename did not return true when parsed: " << filenameF;
}

TEST( TestParser, parseSequence ) {

    // Hash sequence
    const std::string sequenceA = "image.#.png";
    std::string nameA, extensionA;
    unsigned int paddingA;
    bool resultA = parseSequence( sequenceA,
                                  nameA,
                                  paddingA,
                                  extensionA );
    EXPECT_TRUE( resultA ) << "Filename did not return true when parsed: " << sequenceA;
    EXPECT_EQ( nameA, "image" ) << nameA << " != image";
    EXPECT_EQ( paddingA, 4 ) << paddingA << " != 4";
    EXPECT_EQ( extensionA, "png" ) << extensionA << " != png";

    // Multi-hash sequence
    const std::string sequenceB = "image.##.png";
    std::string nameB, extensionB;
    unsigned int paddingB;
    bool resultB = parseSequence( sequenceB,
                                  nameB,
                                  paddingB,
                                  extensionB );
    EXPECT_TRUE( resultB ) << "Filename did not return true when parsed: " << sequenceB;
    EXPECT_EQ( nameB, "image" ) << nameB << " != image";
    EXPECT_EQ( paddingB, 8 ) << paddingB << " != 8";
    EXPECT_EQ( extensionB, "png" ) << extensionB << " != png";

    // Single @ sequence
    const std::string sequenceC = "image.@.png";
    std::string nameC, extensionC;
    unsigned int paddingC;
    bool resultC = parseSequence( sequenceC,
                                  nameC,
                                  paddingC,
                                  extensionC );
    EXPECT_TRUE( resultC ) << "Filename did not return true when parsed: " << sequenceC;
    EXPECT_EQ( nameC, "image" ) << nameC << " != image";
    EXPECT_EQ( paddingC, 1 ) << paddingC << " != 1";
    EXPECT_EQ( extensionC, "png" ) << extensionC << " != png";

    // Multi @ sequence
    const std::string sequenceD = "image.@@@.png";
    std::string nameD, extensionD;
    unsigned int paddingD;
    bool resultD = parseSequence( sequenceD,
                                  nameD,
                                  paddingD,
                                  extensionD );
    EXPECT_TRUE( resultD ) << "File name did not return true when parsed: " << sequenceD;
    EXPECT_EQ( nameD, "image" ) << nameD << " != image";
    EXPECT_EQ( paddingD, 3 ) << paddingD << " != 3";
    EXPECT_EQ( extensionD, "png" ) << extensionD << " != png";

    // Mixed sequence
    const std::string sequenceE = "image.#@.png";
    std::string nameE, extensionE;
    unsigned int paddingE;
    bool resultE = parseSequence( sequenceE,
                                  nameE,
                                  paddingE,
                                  extensionE );
    EXPECT_FALSE( resultE ) << "File name did not return false when parsed: " << sequenceE;

    // Numbered frame
    const std::string sequenceF = "image.1001.png";
    std::string nameF, extensionF;
    unsigned int paddingF;
    bool resultF = parseSequence( sequenceF,
                                  nameF,
                                  paddingF,
                                  extensionF );
    EXPECT_FALSE( resultF ) << "File name did not return false when parsed: " << sequenceF;
}


TEST( TestParser, isNumber ) {

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

TEST( TestParser, isHash ) {

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

TEST( TestParser, isAt ) {

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