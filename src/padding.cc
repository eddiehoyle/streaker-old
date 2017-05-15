//
// Created by Eddie Hoyle on 14/05/17.
//

#include <iostream>
#include <padding.hh>
#include <algorithm>

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
        // TODO
        //  Shield from INT_MAX overflow
        m_fill = pattern.size();
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

