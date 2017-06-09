//
// Created by Eddie Hoyle on 25/05/17.
//

#ifndef STREAKER_FRAME_HH
#define STREAKER_FRAME_HH

#include <iostream>
#include <iomanip>
#include <sstream>

#include <padding.hh>

class Frame;

void print( const Frame& frame );

class Frame {

public:

    explicit Frame( int frame, unsigned int padding = 0 );
    explicit Frame( int frame, const Padding& padding );

    int getFrame() const;
    Padding getPadding() const;

    int toInt() const;
    std::string toString() const;

    bool operator==( const Frame& rhs ) const;


private:

    int m_frame;
    Padding m_padding;
};

#endif //STREAKER_FRAME_HH
