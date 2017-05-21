#include "streaker.hh"

#include <thread>
#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/regex.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

namespace xp = boost::xpressive;
namespace fs = boost::filesystem;

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


Streak findStreak( const std::string& pattern_path ) {

    fs::path path( pattern_path );
    if ( fs::is_directory( pattern_path ) ) {
        std::cerr << "Expected file path, got directory: " << pattern_path << std::endl;
        return Streak();
    }

    // Check pattern
    std::string name, padding, extension;
    if ( !parse( path.filename().string(), SEQUENCE, name, padding, extension ) ) {
        std::cerr << "Invalid pattern: " << path << std::endl;
        return Streak();
    }

//    std::cerr << "Extracted: name=" << name << ", padding=" << padding << ", ext=" << extension << std::endl;

    Streaker streaker;
    streaker.setDirectory( path.parent_path().string() );
    Streak streak = streaker.find( name, padding, extension );
    return streak;
}

void Streaker::setDirectory( const std::string& directory ) {

    if ( !fs::is_directory( fs::path( directory ) ) ) {
        std::cerr << "Invalid directory: " << directory << std::endl;
        return;
    }
    m_directory = fs::path( directory );
}

Streak Streaker::find( const std::string& name,
                       const std::string& padding,
                       const std::string& extension ) {

    // Is name and extension valid?
    if ( name.empty() || extension.empty() ) {
        std::cerr << "Streak name and extension invalid: name="
        << name << ", extension="
        << extension << std::endl;
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

    // Collect all paths that match
    fs::directory_iterator dirIterBegin( m_directory );
    fs::directory_iterator dirIterEnd;

    Paths paths;
    while ( dirIterBegin != dirIterEnd ) {
        paths.push_back( dirIterBegin->path() );
        ++dirIterBegin;
    }

    Streak target( m_directory.string(),
                  name,
                  Padding( padding ),
                  FrameRange(),
                  extension );

    std::thread worker = std::thread( &Streaker::run,
                                      this,
                                      paths.begin(),
                                      paths.end(),
                                      target );

    if ( worker.joinable() ) {
        worker.join();
    }

    print( m_streak );
    return Streak();
}

void Streaker::run( Paths::iterator iterBegin,
                    Paths::iterator iterLast,
                    Streak target ) {

    /* TODO
     *
     */

    // Make sure the iterators are sequential
    const long length = std::distance( iterBegin, iterLast );
    if ( length <= 0 ) {
        return;
    }

    Frames frames;

    const std::string& name = target.getName();
    const Padding& padding = target.getPadding();
    const std::string& extension = target.getExtension();

    while ( iterBegin != iterLast ) {

        // Found a file
        if ( fs::is_regular_file( *iterBegin ) ) {

            // Read filename
            std::string checkName, checkPadding, checkExtension;
            if ( !parse( iterBegin->filename().string(),
                         SIMPLE,
                         checkName,
                         checkPadding,
                         checkExtension ) ) {
                ++iterBegin;
                continue;
            }

//            printf( "Matching: %s == %s, %s == %s, %s == %s\n",
//                    checkExtension.c_str(),
//                    extension.c_str(),
//                    checkName.c_str(),
//                    name.c_str(),
//                    checkPadding.c_str(),
//                    checkPadding.c_str()
//            );
            // Check target
            if ( checkExtension != extension ||
                 checkName != name ||
                 Padding( checkPadding ) != Padding( padding ) ) {
                ++iterBegin;
                continue;
            }

            int frame = std::stoi( checkPadding.c_str() );
            frames.push_back( frame );

            // Increment
            ++iterBegin;
        }
    }

    // Update streak
    FrameRange range;
    for ( auto& frame: frames ) {
        range.addFrame( frame );
    }

    m_streak.setDirectory( target.getDirectory() );
    m_streak.setName( target.getName() );
    m_streak.setPadding( target.getPadding() );
    m_streak.setRange( range );
    m_streak.setExtension( target.getExtension() );

}