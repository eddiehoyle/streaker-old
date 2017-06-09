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

typedef std::vector< boost::filesystem::path > Paths;

/// Find a streak on disk
Streak findStreak( const std::string& pattern );

/// Find streaks in a directory
//Streaks findStreaks( const std::string& directory );

/// Extract sequence id, extension from path
bool parse( const std::string& string,
            const std::string& pattern,
            std::string& name,
            std::string& padding,
            std::string& extension );

class Streaker {

    /*
     * Streaker class design
     * - Does it need to be stateful? Do I even need a class?
     *      I probably do, threads need to fill a vector in an
     *      object somewhere.
     */

public:

    explicit Streaker( const std::string& directory );

    void setDirectory( const std::string& directory );

    /// Scan a directory for a named streak
    Streak find( const std::string& name,
                 const std::string& padding,
                 const std::string& extension );

    Streak find( const std::string& name,
                 unsigned int padding,
                 const std::string& extension );

    Streak find( const std::string& name,
                 const Padding& padding,
                 const std::string& extension );


    // Scan a directory iterator for a streak type
    void run( Paths::iterator iterBegin,
              Paths::iterator iterLast,
              Streak target );

private:

    boost::filesystem::path m_directory;

    // Temp
    Streak m_streak;
    Streaks m_streaks;

    std::vector< std::thread > m_threads;

};

class StreakDispatcher;

class StreakWorker {

public:
    StreakWorker( StreakDispatcher& dispatcher );
};

class StreakDispatcher {

    friend class StreakWorker;

public:

    StreakDispatcher( const std::string& directory, const Streaks& targets );

private:
    std::vector< std::thread > m_threads;
    Streaks m_streaks;
    std::mutex m_mutex;
};


#endif //STREAKER_STREAKER_HH_HH
