//
// Created by Eddie Hoyle on 21/05/17.
//

#ifndef STREAKER_STATUS_HH
#define STREAKER_STATUS_HH

namespace streaker {

enum StatusCode {
    kFailure,
    kSuccess
};

class Status {

public:
    explicit Status( StatusCode status );
    bool operator==( const Status& rhs );
private:
    StatusCode m_code;

};

} // namespace streaker

#endif // STREAKER_STATUS_HH
