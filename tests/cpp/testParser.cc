//
// Created by Eddie Hoyle on 23/06/17.
//

#include <gtest/gtest.h>
#include <parser.hh>

TEST( TestPadding, parseFilename ) {

    // Simple filename
    const std::string filenameA = "image.1.png";
    std::string nameA, extensionA;
    unsigned int frameA, paddingA;
    bool resultA = parseFilename( filenameA,
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
    bool resultB = parseFilename( filenameB,
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
    bool resultC = parseFilename( filenameC,
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
    bool resultD = parseFilename( filenameD,
                                  nameD,
                                  frameD,
                                  paddingD,
                                  extensionD );
    EXPECT_FALSE( resultD ) << "Filename returned true when parsed: " << filenameD;

    // Directory as path
    const std::string filenameE = "/path/to/frame";
    std::string nameE, extensionE;
    unsigned int frameE, paddingE;
    bool resultE = parseFilename( filenameE,
                                  nameE,
                                  frameE,
                                  paddingE,
                                  extensionE );
    EXPECT_FALSE( resultE ) << "Directory was considered a filename: " << filenameE;

    // Sequence instead of frame number
    const std::string filenameF = "image.#.png";
    std::string nameF, extensionF;
    unsigned int frameF, paddingF;
    bool resultF = parseFilename( filenameF,
                                  nameF,
                                  frameF,
                                  paddingF,
                                  extensionF );
    EXPECT_FALSE( resultF ) << "Filename did not return true when parsed: " << filenameF;
}

TEST( TestPadding, parseSequence ) {

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