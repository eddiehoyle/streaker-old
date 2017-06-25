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

Paths listDirectory( const fs::path directory );

/// TODO
Streak findStreak( const SequencePath& sequence ) {

    if ( !sequence ) {
        return Streak();
    }

    Streaker streaker;
    return streaker.find( sequence );
}
Streak findStreak( const FramePath& path ) {
    return Streak();
}

Streak Streaker::find( const SequencePath& sequence ) {

    if ( !sequence ) {
        std::cerr << "Invalid sequence." << std::endl;
        return Streak();
    }
    // Does the directory exist?
    if ( !fs::exists( sequence.directory() ) ) {
        std::cerr << "Directory does not exist: " << sequence.directory() << std::endl;
        return Streak();
    }

    // List all paths in directory
    Paths paths = listDirectory( sequence.directory() );

    // Data set
    FrameSet frames;

    // Loop through paths, extract frames
    for ( const fs::path& path: paths ) {

        FramePath frame( path.string() );
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

    Streak streak( sequence, range );
//
//    print( streak );
    return streak;
}


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