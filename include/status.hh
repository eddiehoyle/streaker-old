//
// Created by Eddie Hoyle on 21/05/17.
//

#ifndef STREAKER_STATUS_HH_HH
#define STREAKER_STATUS_HH_HH


enum StatusCode {
    kFailure,
    kSuccess
};

class Status {

public:
    explicit Status( StatusCode status )
        : m_code( status ) {}

    bool operator==( const Status& rhs ) {
        return m_code == rhs.m_code;
    }

private:
    StatusCode m_code;

};

#endif //STREAKER_STATUS_HH_HH
