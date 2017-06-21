//
// Created by Eddie Hoyle on 21/06/17.
//

#include <defs.hh>
#include <parser.hh>

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/xpressive/xpressive.hpp>

namespace xp = boost::xpressive;
namespace fs = boost::filesystem;

bool parseFrame( const std::string& frameStr,
                 unsigned int* frame,
                 unsigned int* padding ) {
    try {
        int extractedFrame = boost::lexical_cast< int >( frameStr );
        if ( extractedFrame >= 0 ) {
            *frame = static_cast< unsigned int >( extractedFrame );
            *padding = 0;
        }
    } catch ( boost::bad_lexical_cast& e ) {

    }
    return frame != nullptr && padding != nullptr;
}

bool parseFilename( const std::string& filename,
                    std::string& name,
                    unsigned int* frame,
                    unsigned int* padding,
                    std::string& extension ) {

    const fs::path path( filename );

    xp::sregex rx = xp::sregex::compile( FRAME );
    xp::smatch match;

    bool result = false;
    if ( xp::regex_search( path.filename().string(), match, rx ) ) {
        name = match["name"];
        extension = match["extension"];
        result = parseFrame( match["frame"], frame, padding );
    }
    return result;
}
