
#include <streaker/Streaker.hh>
#include <streaker/Range.hh>
#include <streaker/Format.hh>

#include <streaker/file/SequenceFile.hh>
#include <streaker/file/FrameFile.hh>

#include <iostream>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace streaker {

typedef std::vector< fs::path > Paths;

static Paths listDirectory( const fs::path directory ) {

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

static FrameRange match( Paths::iterator begin,
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
        const FrameFile frame( begin->filename().string() );
        if ( frame && frame.match( sequence ) ) {
            frames.insert( frame.frame() );
        }
        ++begin;
    }

    // Collect frames
    FrameRange range;
    range.setFrames( frames );

    return range;
}

Streaker::Streaker( const std::string& directory )
        : m_directory( directory ) {
}

void Streaker::setDirectory( const std::string& directory ) {
    m_directory = directory;
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

} // namespace streaker;