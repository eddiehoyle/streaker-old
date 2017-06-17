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

unsigned int getNumberOfDigits( unsigned int i ) {
    return i > 0 ? ( int )log10( ( double )i ) + 1 : 1;
}

bool parse( const std::string& filepath,
            const std::string& pattern,
            std::string& name,
            std::string& padding,
            std::string& extension ) {

    xp::sregex rx = xp::sregex::compile( pattern );
    xp::smatch match;

    fs::path path( filepath );

    bool result = false;
    if ( xp::regex_search( path.filename().string(), match, rx ) ) {
        name = match["name"];
        padding = match["padding"];
        extension = match["extension"];
        result = true;
    }
    return result;
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


Streak findStreak( const std::string& filepath ) {

    fs::path path( filepath );
    if ( fs::is_directory( filepath ) ) {
        std::cerr << "Expected file path, got directory: " << filepath << std::endl;
        return Streak();
    }

    // Check pattern
    std::string name, padding, extension;
    if ( !parse( path.filename().string(), SEQUENCE, name, padding, extension ) ) {
        std::cerr << "Invalid pattern: " << path << std::endl;
        return Streak();
    }

    Streaker streaker( path.parent_path().string() );
    Streak streak = streaker.find( name, padding, extension );
    return streak;
}

Streaker::Streaker( const std::string& directory )
        : m_directory( directory ) {
}

void Streaker::setDirectory( const std::string& directory ) {

    if ( !fs::is_directory( fs::path( directory ) ) ) {
        std::cerr << "Invalid directory: " << directory << std::endl;
        return;
    }
    m_directory = fs::path( directory );
}

Streak Streaker::find( const std::string& seekName,
                       const std::string& seekPadding,
                       const std::string& seekExtension ) {
    return find( seekName, extract( seekPadding ), seekExtension );
}

Streak Streaker::find( const std::string& seekName,
                       unsigned int padding,
                       const std::string& seekExtension ) {

    // Is name and extension valid?
    if ( seekName.empty() || seekExtension.empty() ) {
        std::cerr << "Streak name and extension invalid: name="
                  << seekName << ", extension="
                  << seekExtension << std::endl;
    }

    // Is the directory valid?
    if ( m_directory.empty() ) {
        std::cerr << "Directory not set." << std::endl;
        return Streak();
    }

    // Does the directory exist?
    if ( !fs::exists( m_directory ) ) {
        std::cerr << "Directory does not exist: " << m_directory.string() << std::endl;
        return Streak();
    }

    // List all paths in directory
    Paths paths = listDirectory( m_directory );
    std::sort( paths.begin(), paths.end() );

    /*
     * Loop through filenames
     * Need to check padding values
     * Does 0001 == 01?
     * What is min/max padding found for streak?
     *
     */

//    typedef std::pair< int, unsigned int > PaddedFrame;
//    std::vector< Frame > frames;
    FrameSet frames;

    // Loop through paths, extract frames
    for ( const fs::path& path: paths ) {

        // Read filename
        std::string checkName, checkFrame, checkExtension;
        if ( !parse( path.filename().string(),
                     SIMPLE,
                     checkName,
                     checkFrame,
                     checkExtension ) ) {
            continue;
        }

        unsigned int fill = extract( checkFrame );

//        print( checkPadding );
//        print( padding );
        bool result = ( padding == fill );
//        printf( "Padding match: fill=%d, state=%d, result=%d\n",
//                parsedPadding.getFill(),
//                parsedPadding.getState(),
//                result );

        // Match names
        if ( seekName == checkName &&
             padding == fill &&
             seekExtension == checkExtension ) {
            int frame = boost::lexical_cast< int >( checkFrame );
//            frames.insert( FramePair( frame, padding ) );
        }
    }

    printf( "Frames: %lu\n", frames.size() );

    // Collect frames
    FrameRange range;
//    range.setFrames( frames );

    Streak streak( m_directory.string(),
                   seekName,
                   range,
                   0,
                   seekExtension );

    print( streak );
    return streak;
}

//void Streaker::run( Paths::iterator iterBegin,
//                    Paths::iterator iterLast,
//                    StreakProxy target ) {
//
//    /* TODO
//     *
//     */
//
//    // Make sure the iterators are sequential
//    const long length = std::distance( iterBegin, iterLast );
//    if ( length <= 0 ) {
//        return;
//    }
//
//    Frames frames;
//
//    const std::string& name = target.getName();
//    const Padding& padding = target.getPadding();
//    const std::string& extension = target.getExtension();
//
//    while ( iterBegin != iterLast ) {
//
//        // Found a file
//        if ( fs::is_regular_file( *iterBegin ) ) {
//
//            // Read filename
//            std::string checkName, checkPadding, checkExtension;
//            if ( !parse( iterBegin->filename().string(),
//                         SIMPLE,
//                         checkName,
//                         checkPadding,
//                         checkExtension ) ) {
//                ++iterBegin;
//                continue;
//            }

//            printf( "Matching: %s == %s, %s == %s, %s == %s\n",
//                    checkExtension.c_str(),
//                    extension.c_str(),
//                    checkName.c_str(),
//                    name.c_str(),
//                    checkPadding.c_str(),
//                    checkPadding.c_str()
//            );
// Check target
//            if ( checkExtension != extension ||
//                 checkName != name ||
//                 Padding::fromPattern( checkPadding ) != Padding::fromPattern( padding ) ) {
//                ++iterBegin;
//                continue;
//            }

//            int frame = std::stoi( checkPadding.c_str() );
//            frames.push_back( frame );
//
//            // Increment
//            ++iterBegin;
//        }
//    }
//
//    // Update streak
//    FrameRange range;
//    for ( auto& frame: frames ) {
//        range.addFrame( frame );
//    }
//
//    m_streak.setDirectory( target.getDirectory() );
//    m_streak.setName( target.getName() );
//    m_streak.setPadding( target.getPadding() );
//    m_streak.setRange( range );
//    m_streak.setExtension( target.getExtension() );
//
//}