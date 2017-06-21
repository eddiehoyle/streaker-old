//
// Created by Eddie Hoyle on 21/06/17.
//

#ifndef STREAKER_FRAME_HH
#define STREAKER_FRAME_HH

#include <padding.hh>

class Frame;

bool parseFrame( const std::string& frameStr,
                 unsigned int* frame,
                 unsigned int* padding );

bool parseFilename( const std::string& filename,
                    std::string& name,
                    std::string& padding,
                    std::string& extension );

bool fromFilename( const std::string& filepath, Frame& frame );

class Frame {

    explicit Frame( unsigned int frame, unsigned int padding );
    unsigned int getFrame() const;
    unsigned int getPadding() const;
    PaddingType getType() const;

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

#endif //STREAKER_FRAME_HH
