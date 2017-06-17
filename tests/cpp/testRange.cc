//
// Created by Eddie Hoyle on 15/06/17.
//
#include <gtest/gtest.h>
#include <range.hh>

TEST( TestRange, constructor ) {

    FrameRange range;

    EXPECT_EQ( range.getFrames(), FrameSet() ) << "Wrong frames";
    EXPECT_EQ( range.getCount(), 0 ) << "Wrong frame count";
    EXPECT_EQ( range.getFirst(), 0 ) << "Wrong first";
    EXPECT_EQ( range.getLast(), 0 ) << "Wrong last";
}

TEST( TestRange, explict_constructor ) {

    FrameRange range( -5, 5 );

    unsigned int expectedCount = ( unsigned int )std::abs( -5 - 5 );
    int expectedFirst = -5;
    int expectedLast = 4;

    FrameSet expectedFrames;
    for ( int frame = expectedFirst; frame < expectedLast + 1; ++frame )
        expectedFrames.insert( expectedFrames.end(), frame );

    EXPECT_EQ( range.getFrames(), expectedFrames ) << "Wrong frames";
    EXPECT_EQ( range.getCount(), expectedCount ) << "Wrong frame count";
    EXPECT_EQ( range.getFirst(), expectedFirst ) << "Wrong first";
    EXPECT_EQ( range.getLast(), expectedLast ) << "Wrong last";
}
