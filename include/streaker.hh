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

    void setDirectory( const std::string& directory );

    /// Scan a directory for a named streak
    Streak find( const std::string& name,
                 const std::string& padding,
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

void process( Paths::iterator iterBegin,
              Paths::iterator iterLast,
              Streaks targets,
              StreakDispatcher* dispatch ) {
}

class StreakDispatcher {

    StreakDispatcher( const std::string& directory, const Streaks& targets )
            : m_threads(),
              m_streaks(),
              m_mutex() {

        Paths paths;
        std::thread thread = std::thread( &process, paths.begin(), paths.end(),  targets, this );
    }

    void add( const Streak& streak ) {
        m_mutex.lock();
        m_streaks.push_back( streak );
        m_mutex.unlock();
    }

private:
    std::vector< std::thread > m_threads;
    Streaks m_streaks;
    std::mutex m_mutex;
};


#endif //STREAKER_STREAKER_HH_HH
