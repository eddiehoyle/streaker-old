//
// Created by Eddie Hoyle on 14/05/17.
//

#include <iostream>
#include <padding.hh>
#include <algorithm>

#include <boost/algorithm/string/predicate.hpp>


Padding extract( const std::string& frame ) {
    Padding padding;
    if ( isNumber( frame ) ) {
        if ( strncmp( frame.c_str(), "0", 1 ) == 0 ) {
            padding.setFill( ( unsigned int )frame.size() );
            padding.setState( kFilled );
        } else {
            padding.setFill( ( unsigned int )frame.size() );
            padding.setState( kAmbiguous );
        }
    } else if ( isHash( frame ) ) {
        padding.setFill( ( unsigned int )( frame.size() * 4 ) );
        padding.setState( kAmbiguous );
    } else if ( isAt( frame ) ) {
        padding.setFill( ( unsigned int )( frame.size() ) );
        padding.setState( kAmbiguous );
    }
    return padding;
}

void print( const Padding& padding ) {
    printf( "Padding(fill=%d)\n", padding.getFill() );
}

Padding::Padding()
        : m_fill( 0 ),
          m_state( kAmbiguous ) {}

Padding::Padding( unsigned int fill, PaddingType state )
        : m_fill( fill ),
          m_state( state ) {}

Padding::~Padding() {}

void Padding::setState( PaddingType state ) {
    m_state = state;
}

PaddingType Padding::getState() const {
    return m_state;
}

void Padding::setFill( unsigned int fill ) {
    m_fill = fill;
}

unsigned int Padding::getFill() const {
    return m_fill;
}

