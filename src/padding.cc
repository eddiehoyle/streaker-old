//
// Created by Eddie Hoyle on 14/05/17.
//

#include <iostream>
#include <padding.hh>
#include <algorithm>

#include <boost/algorithm/string/predicate.hpp>

// Temp
int add( int a, int b ) {
    return a + b;
}

unsigned int extractPadding( const std::string& frame, PaddingState& state ) {
    unsigned int padding = 0;
    if ( isNumber( frame ) ) {
        if ( strncmp( frame.c_str(), "0", 1 ) == 0 ) {
            padding = ( unsigned int )frame.size();
            state = kZeroFilled;
        } else {
            padding = ( unsigned int )frame.size();
            state = kRaw;
        }
    } else if ( isHash( frame ) ) {
        padding = ( unsigned int )( frame.size() * 4 );
        state = kAmbiguous;
    } else if ( isAt( frame ) ) {
        padding = ( unsigned int )( frame.size() );
        state = kAmbiguous;
    }
    return padding;
}

bool isNumber( const std::string& string ) {
    return std::all_of( string.begin(),
                        string.end(),
                        ::isdigit );
}

bool isHash( const std::string& string ) {
    return std::all_of( string.begin(),
                        string.end(),
                        []( char c ){ return c == '#'; } );
}

bool isAt( const std::string& string ) {
    return std::all_of( string.begin(),
                        string.end(),
                        []( char c ){ return c == '@'; } );
}

void print( const Padding& padding ) {
    printf( "Padding(fill=%d)\n", padding.getFill() );
}

Padding Padding::fromPattern( const std::string& pattern ) {
    PaddingState state;
    unsigned int fill = extractPadding( pattern, state );
    return Padding( fill, state );
}

Padding::Padding( unsigned int fill, PaddingState state )
        : m_fill( fill ),
          m_state( state ) {
}

void Padding::setState( PaddingState state ) {
    switch( state ) {
        case kAmbiguous:
        case kRaw:
            m_state = state;
            m_fill = 1;
        case kZeroFilled:
            m_state = state;
        default:
            ;
    }
}

PaddingState Padding::getState() const {
    return m_state;
}

void Padding::setFill( unsigned int fill ) {
    m_fill = fill;
}

unsigned int Padding::getFill() const {
    return m_fill;
}

