#ifndef STREAKER_STREAKER_HH
#define STREAKER_STREAKER_HH

#include <streaker/Streak.hh>

#include <string>

namespace streaker {

class SquenceFile;

class Streaker {

public:
    explicit Streaker( const std::string& directory );
    void setDirectory( const std::string& directory );
    Streak find( const SequenceFile& sequence );

private:
    std::string m_directory;
};

} // namespace streaker

#endif // STREAKER_STREAKER_HH
