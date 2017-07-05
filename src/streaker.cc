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

Streak findStreak( const std::string& directory, const SequenceFile& sequence ) {

    if ( !sequence ) {
        return Streak();
    }

    Streaker streaker( directory );
    return streaker.find( sequence );
}

Streaker::Streaker( const std::string& directory )
        : m_directory( directory ) {
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

    // Collect frames
    FrameRange range = match( paths.begin(), paths.end(), sequence );

    Streak streak( m_directory, sequence, range );
    return streak;
}

FrameRange Streaker::match( Paths::iterator begin,
                            Paths::iterator end,
                            SequenceFile sequence ) {

    print( sequence );

    if ( std::distance( begin, end ) <= 0 ) {
        return FrameRange();
    }

    // Data set
    FrameSet frames;

    // Loop
    while ( begin != end ) {
        if ( FrameFile frame = FrameFile( begin->filename().string() ) ) {
            if ( frame.match( sequence ) ) {
                frames.insert( frame.frame() );
            }
        }
        ++begin;
    }

    // Collect frames
    FrameRange range;
    range.setFrames( frames );

    return range;
}