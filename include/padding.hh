//
// Created by Eddie Hoyle on 8/05/17.
//

#ifndef STREAKER_PADDING_HH
#define STREAKER_PADDING_HH

#include <string>

inline unsigned int countDigits( unsigned int frame ) {
    unsigned int length = 1;
    while ( frame /= 10 ) {
        length++;
    }
    return length;
}

inline bool isAmbiguous( unsigned int frame, unsigned int padding ) {
    return countDigits( frame ) >= padding;
}

#endif //STREAKER_PADDING_HH
