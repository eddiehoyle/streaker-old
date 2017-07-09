//
// Created by Eddie Hoyle on 7/05/17.
//

#ifndef STREAKER_STREAKER_HH_HH
#define STREAKER_STREAKER_HH_HH

//#include <streaker/file/SequenceFile.hh>
#include <streaker/Streak.hh>

class SquenceFile;

class Streaker {

public:
    explicit Streaker( const std::string& directory );
    void setDirectory( const std::string& directory );
    Streak find( const SequenceFile& sequence );

private:
    std::string m_directory;
};

#endif //STREAKER_STREAKER_HH_HH
