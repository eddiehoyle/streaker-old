#include <iostream>
#include "streaker.hh"

#include <boost/regex.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

namespace xp = boost::xpressive;
namespace fs = boost::filesystem;

typedef std::vector< boost::filesystem::directory_entry > Paths;

bool parse( const std::string& pattern, std::string& id, std::string& extension ) {

    xp::sregex rx = xp::sregex::compile( SEQUENCE );
    xp::smatch match;

    fs::path path( pattern );

    bool result = false;
    if( xp::regex_search( path.filename().string(), match, rx ) ) {
        id = match["name"];
        extension = match["extension"];
        result = true;
    }
    return result;
}



Streak findStreak( const std::string& pattern_path ) {


    fs::path path( pattern_path );
    if ( fs::is_directory( pattern_path ) ) {
        std::cerr << "Expected file path, got directory: " << pattern_path << std::endl;
        return Streak();
    }

    // Check pattern
    std::string id;
    std::string ext;
    if ( !parse( path.filename().string(), id, ext ) ) {
        std::cerr << "Invalid pattern: " << path << std::endl;
        return Streak();
    }

    std::cerr << "Extracted: id=" << id << ", ext=" << ext << std::endl;

    Streaker streaker;
    streaker.setDirectory( path.parent_path().string() );
    Streak streak = streaker.find( id, ext );
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
    Paths matches;
    fs::directory_iterator iter( m_directory );
    fs::directory_iterator iterEnd;
    while ( iter != iterEnd ) {

        // Found a file
        if ( fs::is_regular_file( *iter ) ) {
            if ( ( iter->path().extension().string() == extension ) &&
                 boost::starts_with( iter->path().filename().string(), name ) ) {

                // Found match
                matches.push_back( *iter );

                // Get name, number, extension



            }
        }
        ++iter;
    }

    if ( matches.empty() ) {
        std::cerr << "No matches found for pattern: name="
        << name << ", extension="
        << extension << std::endl;
        return Streak();
    }

    std::cerr << "Found matches: " << matches.size() << std::endl;

    return Streak();
}

//Streaker::Streaker( const std::string& pattern ) {
//
//    std::string id, ext;
//    if ( !parse( pattern, id, ext ) ) {
//        std::cerr << "Invalid pattern: " << pattern << std::endl;
//        return;
//    }
//
//    fs::path path( pattern );
//
//    Paths paths;
//    if ( boost::filesystem::is_directory( path.parent_path() ) ) {
//        std::copy( boost::filesystem::directory_iterator( path.parent_path() ),
//                   boost::filesystem::directory_iterator(),
//                   std::back_inserter( paths ) );
//    }
//
//    printf( "About to scan %lu file(s)\n", paths.size() );
//
//    for ( Paths::iterator pathIter = paths.begin();
//          pathIter != paths.end();
//          ++pathIter ) {
//    }
//}