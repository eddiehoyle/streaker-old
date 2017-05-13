//
// Created by Eddie Hoyle on 7/05/17.
//

#ifndef STREAKER_STREAKER_HH_HH
#define STREAKER_STREAKER_HH_HH

#include <boost/filesystem.hpp>
#include "defs.hh"
#include "streak.hh"
#include "range.hh"

/// Find a streak on disk
Streak findStreak( const std::string& pattern );

/// Find streaks in a directory
//Streaks findStreaks( const std::string& directory );

/// Extract sequence id, extension from path
bool parse( const std::string& pattern, std::string& id, std::string& extension );

class Streaker {

    /*
     * Streaker class design
     * - Does it need to be stateful? Do I even need a class?
     *      I probably do, threads need to fill a vector in an
     *      object somewhere.
     */

public:

    void setDirectory( const std::string& directory );

    /// Scan a directory for a named streak
    Streak  find( const std::string& name,
                  const std::string& extension );

private:
    boost::filesystem::path m_directory;

};

#endif //STREAKER_STREAKER_HH_HH
