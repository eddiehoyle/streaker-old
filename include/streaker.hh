//
// Created by Eddie Hoyle on 7/05/17.
//

#ifndef STREAKER_STREAKER_HH_HH
#define STREAKER_STREAKER_HH_HH

#include <boost/filesystem.hpp>
#include <thread>
#include <mutex>

#include "defs.hh"
#include "streak.hh"
#include "range.hh"
#include <path.hh>


typedef std::vector< boost::filesystem::path > Paths;

/// Look for all streaks in directory
Streaks findStreaks( const std::string& directory );
Streak findStreak( const std::string& directory, const SequenceFile& path );
Streaks findStreaks( const std::string& directory, const SequenceFiles& paths );

class Streaker {

    /*
     * Streaker class design
     * - Does it need to be stateful? Do I even need a class?
     *      I probably do, threads need to fill a vector in an
     *      object somewhere.
     */

public:


    explicit Streaker( const std::string& directory );

//    void setDirectory( const std::string& directory );

    /// Scan a directory for a named streak
    Streaks find();
    Streak find( const SequenceFile& sequence );
    Streaks find( const SequenceFiles& sequences );

private:
    std::string m_directory;
};

#endif //STREAKER_STREAKER_HH_HH
