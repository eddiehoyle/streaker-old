//
// Created by Eddie Hoyle on 8/05/17.
//

#ifndef STREAKER_PADDING_HH
#define STREAKER_PADDING_HH

#include <string>

enum PaddingType {
    eHash,
    eNuke
};

class Padding {

    /*
     * Represents padding fill value
     */

public:
    Padding();
    ~Padding();
    explicit Padding( const std::string& pattern );
    explicit Padding( int fill );

    operator bool() const {
        return m_fill > 0;
    }

    bool operator==( const Padding& rhs ) const {
        return this->getFill() >= rhs.getFill();
    }

    int getFill() const;

private:
    int m_fill;

};

#endif //STREAKER_PADDING_HH
