////
//// Created by Eddie Hoyle on 12/06/17.
////
//
//#include <limits.h>
//#include <gtest/gtest.h>
//#include <gmock/gmock.h>
//#include <frame.hh>
//
//
//TEST( TestFrame, constructor ) {
//
//    Padding padding( 0, PaddingState::kAmbiguous );
//    Frame frame( 10, padding );
//
//    EXPECT_EQ( frame.getNumber(), 10 ) << "Wrong number";
//    EXPECT_EQ( frame.getPadding(), padding) << "Wrong padding";
//}
//
//TEST( TestFrame, getNumber ) {
//
//    Padding padding( 0, PaddingState::kAmbiguous );
//    Frame frame( 10, padding );
//
//    EXPECT_EQ( frame.getNumber(), 10 ) << "Wrong number";
//}
//
//TEST( TestFrame, getPadding ) {
//
//    int number = 10;
//    Padding padding( 0, PaddingState::kAmbiguous );
//    Frame frame( number, padding );
//
//    EXPECT_EQ( frame.getPadding(), padding ) << "Wrong padding";
//}
//
//TEST( TestFrame, setNumber ) {
//
//    Padding padding( 0, PaddingState::kAmbiguous );
//    Frame frame( 10, padding );
//
//    // Update
//    frame.setNumber( 5 );
//
//    EXPECT_EQ( frame.getNumber(), 5 ) << "Updated number was incorrect";
//}
//
//TEST( TestFrame, setPadding ) {
//
//    Padding padding( 0, PaddingState::kAmbiguous );
//    Frame frame( 10, padding );
//
//    // Update
//    Padding updatedPadding( 2, PaddingState::kZeroFilled );
//    frame.setPadding( updatedPadding );
//
//    EXPECT_EQ( frame.getPadding(), updatedPadding ) << "Updated padding was incorrect";
//}
//
//TEST( TestFrame, operatorEquals ) {
//
//    Padding paddingA( 0, PaddingState::kAmbiguous );
//    Frame frameA( 5, paddingA );
//    Frame frameB( 5, paddingA );
//
//    EXPECT_EQ( frameA, frameB ) << "Frame comparison unequal";
//}
//
//TEST( TestFrame, operatorNotEquals ) {
//
//    Padding paddingA( 0, PaddingState::kAmbiguous );
//    Frame frameA( 3, paddingA );
//    Frame frameB( 5, paddingA );
//
//    EXPECT_EQ( frameA, frameB ) << "Frame comparison unequal";
//}
