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

Streak findStreak( const std::string& filepath ) {

    fs::path path( filepath );
    if ( fs::is_directory( filepath ) ) {
        std::cerr << "Expected file path, got directory: " << filepath << std::endl;
        return Streak();
    }

    // Check pattern
    std::string name, frame, extension;
    if ( !parse( path.filename().string(), SEQUENCE, name, frame, extension ) ) {
        std::cerr << "Invalid pattern: " << path << std::endl;
        return Streak();
    }

    unsigned int padding;
    extractPadding( frame, padding );

    const std::string directory = path.parent_path().string();
    Streaker streaker( directory );
    Streak streak = streaker.find( name, padding, extension );
    return streak;
}

Streaker::Streaker( const std::string& directory )
        : m_directory( directory ) {
}

void Streaker::setDirectory( const std::string& directory ) {
    m_directory = fs::path( directory );
}

Streak Streaker::find( const std::string& name,
                       unsigned int padding,
                       const std::string& extension ) {

    printf( "Looking for padding: %d\n\n", padding );

    // Is name and extension valid?
    if ( name.empty() || extension.empty() ) {
        std::cerr << "Streak name or extension invalid: name="
                  << name << ", extension="
                  << extension << std::endl;
    }

    // Is the directory valid?
    if ( !fs::is_directory( m_directory ) ) {
        std::cerr << "Invalid directory: " << m_directory.string() << std::endl;
        return Streak();
    }

    // Does the directory exist?
    if ( !fs::exists( m_directory ) ) {
        std::cerr << "Directory does not exist: " << m_directory.string() << std::endl;
        return Streak();
    }

    // List all paths in directory
    Paths paths = listDirectory( m_directory );

    // TODO
    //  Do I need to sort paths?
//    std::sort( paths.begin(), paths.end() );

    /*
     * Loop through filenames
     * Need to check padding values
     * Does 0001 == 01?
     * What is min/max padding found for streak?
     */

    FrameSet frames;

    // Loop through paths, extract frames
    for ( const fs::path& path: paths ) {

        // Read filename
        std::string parseName, parseFrame, parseExtension;
        if ( !parse( path.filename().string(),
                     FRAME,
                     parseName,
                     parseFrame,
                     parseExtension ) ) {
            continue;
        }

        unsigned int frame = boost::lexical_cast< unsigned int >( parseFrame );

        unsigned int parsePadding;
        extractPadding( parseFrame, parsePadding );

        PaddingType type = getPaddingType( frame, parsePadding );

//        printf( "%s == %s: %d\n", seekName.c_str(), checkName.c_str(), ( seekName == checkName ) );
//        printf( "%d == %d: %d\n", padding, checkPadding, ( padding == checkPadding ) );
//        printf( "%s == %s: %d\n", seekExtension.c_str(), checkExtension.c_str(), ( seekExtension == checkExtension ) );
//        printf( "Frame=%d, checkPadding=%d, PaddingType=%d\n", frame, checkPadding, type );

        // Match names
        if ( name == parseName &&
                ( ( padding == parsePadding && type == kFilled ) ||
                ( padding <= parsePadding && type == kAmbiguous ) ) &&
             extension == parseExtension ) {

            // Store frame
            frames.insert( frame );
        }
    }

    // Collect frames
    FrameRange range;
    range.addFrames( frames );

    Streak streak( m_directory.string(),
                   name,
                   range,
                   padding,
                   extension );

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

bool parse( const std::string& path,
            const std::string& pattern,
            std::string& name,
            std::string& frame,
            std::string& extension ) {

    const fs::path filepath( path );

    xp::sregex rx = xp::sregex::compile( pattern );
    xp::smatch match;

    // TODO
    //  This is silly. We're expecting named captures on an input pattern
    //  that could be anything. Fix this.
    bool result = false;
    if ( xp::regex_search( filepath.filename().string(), match, rx ) ) {
        name = match["name"];
        frame = match["frame"];
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