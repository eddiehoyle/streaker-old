//
// Created by Eddie Hoyle on 14/05/17.
//

#include <iostream>
#include <padding.hh>
#include <algorithm>

#include <boost/algorithm/string/predicate.hpp>


bool is_number( const std::string& pattern ) {
    std::string::const_iterator iter = pattern.begin();
    while ( iter != pattern.end() && std::isdigit( *iter ) ) {
        ++iter;
    }
    return !pattern.empty() && iter == pattern.end();
}

bool is_hash( const std::string& pattern ) {
    return pattern.size() == std::count( pattern.begin(), pattern.end(), '#');
}

Padding::Padding() {
}

Padding::~Padding() {
}

Padding::Padding( const std::string& pattern ) {

    if ( is_number( pattern ) || is_hash( pattern ) ) {

        // If string starts with 0, we know the padding size
        if ( strncmp( pattern.c_str(), "0", 1 ) == 0 ) {
            m_fill = ( int )pattern.size();
        }
    } else {
        m_fill = -1;
    }
}

Padding::Padding( int fill ) {
    m_fill = fill;
}

int Padding::getFill() const {
    return m_fill;
}

