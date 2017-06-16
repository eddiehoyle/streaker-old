////
//// Created by Eddie Hoyle on 25/05/17.
////

#ifndef STREAKER_FRAME_HH
#define STREAKER_FRAME_HH

#include <iostream>
#include <iomanip>
#include <sstream>

#include <padding.hh>

typedef std::pair< int, Padding > FramePair;

bool operator==( const FramePair& lhs, const FramePair& rhs );
bool operator!=( const FramePair& lhs, const FramePair& rhs );
bool operator<( const FramePair& lhs, const FramePair& rhs );
bool operator<=( const FramePair& lhs, const FramePair& rhs );
bool operator>( const FramePair& lhs, const FramePair& rhs );
bool operator>=( const FramePair& lhs, const FramePair& rhs );

#endif //STREAKER_FRAME_HH








//
//class Frame;
//
//void print( const Frame& frame );
//
//std::string toString( const Frame& frame );




//class Frame {
//
//public:
//
//    explicit Frame( int number, const Padding& padding );
//
//    int getNumber() const;
//    Padding getPadding() const;
//
//    void setNumber( int number );
//    void setPadding( const Padding& padding );
//
//    bool operator==( const Frame& rhs ) const;
//    bool operator!=( const Frame& rhs ) const;
////    bool operator<( const Frame& rhs ) const;
////    bool operator>( const Frame& rhs ) const;
//
//private:
//
//    int m_number;
//    Padding m_padding;
//};
//
