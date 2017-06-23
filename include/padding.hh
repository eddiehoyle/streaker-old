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

inline unsigned int countDigits( unsigned int frame ) {
    unsigned int length = 1;
    while ( frame /= 10 ) {
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

inline bool isAmbiguous( unsigned int frame, unsigned int padding ) {
    return countDigits( frame ) >= padding;
}

#endif //STREAKER_PADDING_HH
