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
Streak findStreak( const std::string& directory, const SequenceFile& path );

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
    Streak find( const SequenceFile& sequence );

private:

    /// Match
    Streaks match( Paths::iterator begin, Paths::iterator end, SequenceFileSet sequences );
    Streaks match( Paths::iterator begin, Paths::iterator end );

    /// Find frames from files
    FrameRange match( Paths::iterator begin, Paths::iterator end, SequenceFile sequence );


private:
    std::string m_directory;
};

#endif //STREAKER_STREAKER_HH_HH
