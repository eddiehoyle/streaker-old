////
//// Created by Eddie Hoyle on 25/05/17.
////
//

#include <frame.hh>

bool operator==( const FramePair& lhs, const FramePair& rhs ) {
    return lhs.first == rhs.first && lhs.second <= rhs.second;
};

bool operator!=( const FramePair& lhs, const FramePair& rhs ) {
    return true;
};

bool operator<( const FramePair& lhs, const FramePair& rhs ) {
    return true;
};

bool operator<=( const FramePair& lhs, const FramePair& rhs ) {
    return true;
};

bool operator>( const FramePair& lhs, const FramePair& rhs ) {
    return true;
};

bool operator>=( const FramePair& lhs, const FramePair& rhs ) {
    return true;
};






//
//void print( const Frame& frame ) {
//    printf( "Frame( frame=%d, padding=%d )\n", frame.getNumber(), frame.getPadding().getFill() );
//}
//
//std::string toString( const Frame& frame ) {
//    std::ostringstream stream;
//
//    // TODO:
//    // Fix this. This is pad count + number, meaning
//    // eg: pad = 4, results in '00001' (4 zeros + number)
//    stream << std::setw( frame.getPadding().getFill() )
//           << std::setfill( '0' )
//           << frame.getNumber();
//    return stream.str();
//}
//
//Frame::Frame( int number, const Padding& padding )
//        : m_number( number ),
//          m_padding( padding ) {
//}
//
//int Frame::getNumber() const {
//    return m_number;
//}
//
//Padding Frame::getPadding() const {
//    return m_padding;
//}
//
//void Frame::setNumber( int number ) {
//    m_number = number;
//}
//
//void Frame::setPadding( const Padding& padding ) {
//    m_padding = padding;
//}
//
//bool Frame::operator==( const Frame& rhs ) const {
//    return getNumber() == rhs.getNumber();
//}
//
//bool Frame::operator!=( const Frame& rhs ) const {
//    return getNumber() != rhs.getNumber();
//}
//
////bool Frame::operator<( const Frame& rhs ) const {
////    return getNumber() < rhs.getNumber();
////}
////
////bool Frame::operator>( const Frame& rhs ) const {
////    return getNumber() > rhs.getNumber();
////}
