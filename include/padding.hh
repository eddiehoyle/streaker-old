//
// Created by Eddie Hoyle on 8/05/17.
//

#ifndef STREAKER_PADDING_HH
#define STREAKER_PADDING_HH

#include <string>

enum PaddingType {
    kAmbiguous = 0,
    kFilled    = 1
};

inline unsigned int getNumberOfDigits( int number ) {
    unsigned int length = 1;
    while ( number /= 10 ) {
        length++;
    }
    return length;
}

inline bool isNumber( const std::string& pattern ) {
    return std::all_of( pattern.begin(),
                        pattern.end(),
                        ::isdigit );
}

inline bool isHash( const std::string& pattern ) {
    return std::all_of( pattern.begin(),
                        pattern.end(),
                        []( char c ){ return c == '#'; } );
}

inline bool isAt( const std::string& pattern ) {
    return std::all_of( pattern.begin(),
                        pattern.end(),
                        []( char c ){ return c == '@'; } );
}

inline bool extractPadding( const std::string& frame, unsigned int& padding ) {

    if ( frame.empty() ) {
        return false;
    }

    if ( isNumber( frame ) ) {
        padding = ( unsigned int )frame.size();
    } else if ( isHash( frame ) ) {
        padding = ( unsigned int )( frame.size() * 4 );
    } else if ( isAt( frame ) ) {
        padding = ( unsigned int )( frame.size() );
    } else {
        return false;
    }
    return true;
}

inline PaddingType getPaddingType( int frame, unsigned int padding ) {

    PaddingType type;
    unsigned int digits = getNumberOfDigits( frame );
    if ( padding <= digits ) {
        type = kAmbiguous;
    } else {
        type = kFilled;
    }
    return type;
}

#endif //STREAKER_PADDING_HH
