//
// Created by Eddie Hoyle on 8/05/17.
//

#ifndef STREAKER_PADDING_HH
#define STREAKER_PADDING_HH

#include <string>

// New
enum PaddingType {
    kAmbiguous,
    kFilled
};

class Padding;

Padding extract( const std::string& frame );



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

void print( const Padding& padding );

class Padding {

    /*
     * Represents padding fill value
     */

public:
    Padding();
    explicit Padding( unsigned int fill, PaddingType state = kAmbiguous );

    ~Padding();

    void setFill( unsigned int fill );
    void setState( PaddingType state );

    unsigned int getFill() const;
    PaddingType getState() const;

    bool operator==( const Padding& rhs ) const {
        return getFill() == rhs.getFill() &&
               getState() == rhs.getState();
    }
    bool operator!=( const Padding& rhs ) const {
        return getFill() != rhs.getFill() &&
               getState() != rhs.getState();
    }
    bool operator<( const Padding& rhs ) const {
        return getFill() < rhs.getFill();
    }
    bool operator<=( const Padding& rhs ) const {
        return getFill() <= rhs.getFill();
    }
    bool operator>( const Padding& rhs ) const {
        return getFill() > rhs.getFill();
    }
    bool operator>=( const Padding& rhs ) const {
        return getFill() >= rhs.getFill();
    }

//    // Examples:
//    // 1   == 101 // false
//    // 101 == 003 // true
//    bool operator==( const Padding& rhs ) const {
//        const PaddingType lhsState = getState();
//        const PaddingType rhsState = rhs.getState();
//
//        // Eg: 1, 101
//        if ( lhsState == kRaw || lhsState == kAmbiguous ) {
//
//            // Eg: 2, 102
//            if ( rhsState == kRaw || rhsState == kAmbiguous ) {
//                return true;
//            }
//
//            // Eg: 101, 101
//            if ( rhsState == kZeroFilled ) {
//                return getFill() == rhs.getFill();
//            }
//        }
//
//        // Eg: 001
//        if ( lhsState == kZeroFilled ) {
//
//            // Eg: 001, 101
//            if ( rhsState == kAmbiguous ) {
//                return getFill() <= rhs.getFill();
//            }
//
//            // Eg: 001, 101;
//            if ( rhsState == kZeroFilled ) {
//                return getFill() == rhs.getFill();
//            }
//        }
//        return false;
//    }

private:
    unsigned int m_fill;
    PaddingType m_state;
};

#endif //STREAKER_PADDING_HH
