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

/// TODO
Streak findStreak( const SequencePath& path );
Streak findStreak( const FramePath& path );

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


//    explicit Streaker();

//    void setDirectory( const std::string& directory );

    /// Scan a directory for a named streak
//    Streak find( const std::string& name,
//                 unsigned int padding,
//                 const std::string& extension );

    Streak find( const SequencePath& sequence );

//    // Scan a directory iterator for a streak type
//    void run( Paths::iterator iterBegin,
//              Paths::iterator iterLast,
//              Streak target );

private:
    boost::filesystem::path m_directory;
};

//class StreakDispatcher;
//
//class StreakWorker {
//
//public:
//    StreakWorker( StreakDispatcher& dispatcher );
//};
//
//class StreakDispatcher {
//
//    friend class StreakWorker;
//
//public:
//
//    StreakDispatcher( const std::string& directory, const Streaks& targets );
//
//private:
//    std::vector< std::thread > m_threads;
//    Streaks m_streaks;
//    std::mutex m_mutex;
//};


#endif //STREAKER_STREAKER_HH_HH
