//
// Created by Eddie Hoyle on 25/05/17.
//

#include <frame.hh>

void print( const Frame& frame ) {
    printf( "Frame( frame=%d, padding=%d )\n", frame.getFrame(), frame.getPadding().getFill() );
}

Frame::Frame( int frame, unsigned int padding )
        : m_frame( frame ),
          m_padding( padding ) {
}

Frame::Frame( int frame, const Padding& padding )
        : m_frame( frame ),
          m_padding( padding ) {
}

int Frame::getFrame() const {
    return m_frame;
}

Padding Frame::getPadding() const {
    return m_padding;
}

int Frame::toInt() const {
    return m_frame;
}

std::string Frame::toString() const {
    std::ostringstream stream;
    stream << std::setw( m_padding.getFill() )
           << std::setfill( '0' )
           << m_frame;
    return stream.str();
}

bool Frame::operator==( const Frame& rhs ) const {
    return getFrame() == rhs.getFrame() &&
           getPadding() == rhs.getPadding();
}
