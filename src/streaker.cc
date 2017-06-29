#include "streaker.hh"

#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#include <range.hh>

#include <boost/regex.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/lexical_cast.hpp>
#include <stdexcept>

namespace xp = boost::xpressive;
namespace fs = boost::filesystem;

Paths listDirectory( const fs::path directory ) {

    Paths paths;
    if ( !fs::is_directory( directory ) ) {
        std::cerr << "Invalid directory: " << directory << std::endl;
        return paths;
    }

    // File vector with paths
    fs::directory_iterator dirIterBegin( directory );
    fs::directory_iterator dirIterEnd;
    while ( dirIterBegin != dirIterEnd ) {
        paths.push_back( dirIterBegin->path() );
        ++dirIterBegin;
    }
    return paths;
}

/// TODO
Streaks findStreaks( const std::string& directory ) {

    Streaker streaker( directory );
    Streaks streaks = streaker.find();
    return streaks;
}

Streak findStreak( const std::string& directory, const SequenceFile& sequence ) {

    if ( !sequence ) {
        return Streak();
    }

    Streaker streaker( directory );
    return streaker.find( sequence );
}

Streaks findStreaks( const std::string& directory, const SequenceFiles& sequences ) {

    if ( sequences.empty() ) {
        return Streaks();
    }

    Streaks streaks;
    for ( const SequenceFile& sequence : sequences ) {

        Streaker streaker( directory );
        Streak streak = streaker.find( sequence );
        streaks.push_back( streak );
    }
    return streaks;
}

Streaker::Streaker( const std::string& directory )
    : m_directory( directory ) {
}

Streaks Streaker::find() {

    // Does the directory exist?
    if ( !fs::exists( m_directory ) ) {
        std::cerr << "Directory does not exist: " << m_directory << std::endl;
        return Streaks();
    }

    // List all paths in directory
    Paths paths = listDirectory( m_directory );

    SequenceFileSet sequences;
    for ( const fs::path& path : paths ) {
        if ( FrameFile frame = FrameFile( path.filename().string() ) ) {
            print( frame );
            SequenceFile sequence( frame.name(),
                                   frame.padding(),
                                   frame.extension() );
            sequences.insert( sequence );
        }
    }

    printf( "Found sequences: %lu\n", sequences.size() );

    Streaks streaks;
    for ( const SequenceFile& sequence : sequences ) {

        if ( !sequence ) {
            continue;
        }

        // Data set
        FrameSet frames;

        // Loop through paths, extract frames
        for ( const fs::path& path: paths ) {

            FrameFile frame( path.string() );
            if ( !frame ) {
                continue;
            }

            if ( frame.match( sequence ) ) {
                frames.insert( frame.frame() );
            }
        }

        // Collect frames
        FrameRange range;
        range.setFrames( frames );
        Streak streak( m_directory, sequence, range );

        // Cache
        streaks.push_back( streak );
    }
    return streaks;
}
Streak Streaker::find( const SequenceFile& sequence ) {

    if ( !sequence ) {
        std::cerr << "Invalid sequence." << std::endl;
        return Streak();
    }
    // Does the directory exist?
    if ( !fs::exists( m_directory ) ) {
        std::cerr << "Directory does not exist: " << m_directory << std::endl;
        return Streak();
    }

    // List all paths in directory
    Paths paths = listDirectory( m_directory );

    // Data set
    FrameSet frames;

    // Loop through paths, extract frames
    for ( const fs::path& path: paths ) {

        FrameFile frame( path.string() );
        if ( !frame ) {
            continue;
        }

        if ( frame.match( sequence ) ) {
            frames.insert( frame.frame() );
        }
    }

    // Collect frames
    FrameRange range;
    range.setFrames( frames );

    Streak streak( m_directory, sequence, range );
    return streak;
}


Streaks Streaker::find( const SequenceFiles& sequences ) {

    // Does the directory exist?
    if ( !fs::exists( m_directory ) ) {
        std::cerr << "Directory does not exist: " << m_directory << std::endl;
        return Streaks();
    }

    // List all paths in directory
    Paths paths = listDirectory( m_directory );

    Streaks streaks;
    for ( const SequenceFile& sequence : sequences ) {

        if ( !sequence ) {
            continue;
        }

        // Data set
        FrameSet frames;

        // Loop through paths, extract frames
        for ( const fs::path& path: paths ) {

            FrameFile frame( path.string() );
            if ( !frame ) {
                continue;
            }

            if ( frame.match( sequence ) ) {
                frames.insert( frame.frame() );
            }
        }

        // Collect frames
        FrameRange range;
        range.setFrames( frames );
        Streak streak( m_directory, sequence, range );

        // Cache
        streaks.push_back( streak );
    }
    return streaks;
}


