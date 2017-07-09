//
// Created by Eddie Hoyle on 15/06/17.
//
#include <gtest/gtest.h>
#include <streaker/Range.hh>

TEST( TestRange, constructor ) {

    FrameRange range;

    EXPECT_EQ( range.frames(), FrameSet() ) << "Wrong frames";
    EXPECT_EQ( range.getCount(), 0 ) << "Wrong frame count";
    EXPECT_EQ( range.getFirst(), 0 ) << "Wrong first";
    EXPECT_EQ( range.getLast(), 0 ) << "Wrong last";
}

TEST( TestRange, explict_constructor ) {

    FrameRange range( 0, 5 );

    unsigned int expectedCount = ( unsigned int )std::abs( 0 - 5 );
    unsigned int expectedFirst = 0;
    unsigned int expectedLast = 4;

    FrameSet expectedFrames;
    for ( unsigned int frame = expectedFirst; frame < expectedLast + 1; ++frame ) {
        expectedFrames.insert( expectedFrames.end(), frame );
    }

    EXPECT_EQ( range.frames(), expectedFrames ) << "Wrong frames";
    EXPECT_EQ( range.getCount(), expectedCount ) << "Wrong frame count";
    EXPECT_EQ( range.getFirst(), expectedFirst ) << "Wrong first";
    EXPECT_EQ( range.getLast(), expectedLast ) << "Wrong last";
}
