//
// Created by Eddie Hoyle on 8/05/17.
//

#ifndef STREAKER_PADDING_HH
#define STREAKER_PADDING_HH

#include <string>

enum PaddingType {
    kAmbiguous,
    kFilled
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

inline unsigned int extract( const std::string& frame ) {
    unsigned int padding = 0;
    if ( isNumber( frame ) ) {
        if ( strncmp( frame.c_str(), "0", 1 ) == 0 ) {
            padding = ( unsigned int )frame.size();
        }
    } else if ( isHash( frame ) ) {
        padding = ( unsigned int )( frame.size() * 4 );
    } else if ( isAt( frame ) ) {
        padding = ( unsigned int )( frame.size() );
    }
    return padding;
}

#endif //STREAKER_PADDING_HH
