//
// Created by Eddie Hoyle on 21/06/17.
//

#ifndef STREAKER_FRAME_HH
#define STREAKER_FRAME_HH

#include <padding.hh>

class Frame;

void fromFilename( const std::string& filepath, Frame& frame );

class Frame {

    explicit Frame( unsigned int frame, unsigned int padding );
    unsigned int getFrame() const;
    unsigned int getPadding() const;

    bool operator==( const Frame& rhs ) const {
        return getFrame() == rhs.getFrame() &&
               getPadding() == rhs.getPadding();
    }
    operator bool() const {
        return !( m_frame == 0 && m_padding == 0 );
    }

private:
    unsigned int m_frame;
    unsigned int m_padding;
};

class Sequence {
    explicit Sequence( unsigned int padding );
};

#endif //STREAKER_FRAME_HH
