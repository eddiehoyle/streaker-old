//
// Created by Eddie Hoyle on 8/05/17.
//

#ifndef STREAKER_PADDING_HH
#define STREAKER_PADDING_HH

#include <string>

int add( int a, int b );

enum PaddingState {
    kAmbiguous,
    kRaw,
    kZeroFilled
};

unsigned int extractPadding( const std::string& frame, PaddingState& state );
bool isNumber( const std::string& string );
bool isHash( const std::string& pattern );
bool isAt( const std::string& pattern );

class Padding;

void print( const Padding& padding );

class Padding {

    /*
     * Represents padding fill value
     */

public:
    static Padding fromPattern( const std::string& pattern );

public:
    Padding() {}
    ~Padding() {}
    explicit Padding( unsigned int fill, PaddingState state = kAmbiguous );

    void setFill( unsigned int fill );
    void setState( PaddingState state );

    unsigned int getFill() const;
    PaddingState getState() const;

    operator bool() const {
        return m_fill > 0;
    }

    // Examples:
    // 1   == 101 // false
    // 101 == 003 // true
    bool operator==( const Padding& rhs ) const {
        const PaddingState lhsState = getState();
        const PaddingState rhsState = rhs.getState();

        // Eg: 1, 101
        if ( lhsState == kRaw || lhsState == kAmbiguous ) {

            // Eg: 2, 102
            if ( rhsState == kRaw || rhsState == kAmbiguous ) {
                return true;
            }

            // Eg: 101, 101
            if ( rhsState == kZeroFilled ) {
                return getFill() == rhs.getFill();
            }
        }

        // Eg: 001
        if ( lhsState == kZeroFilled ) {

            // Eg: 001, 101
            if ( rhsState == kAmbiguous ) {
                return getFill() <= rhs.getFill();
            }

            // Eg: 001, 101;
            if ( rhsState == kZeroFilled ) {
                return getFill() == rhs.getFill();
            }
        }
        return false;
    }

private:
    unsigned int m_fill;
    PaddingState m_state;

};



#endif //STREAKER_PADDING_HH
