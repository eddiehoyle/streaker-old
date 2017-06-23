//
// Created by Eddie Hoyle on 21/06/17.
//

#include <defs.hh>
#include <parser.hh>
#include <padding.hh>

#include <boost/lexical_cast.hpp>
#include <boost/xpressive/xpressive.hpp>

namespace xp = boost::xpressive;

bool parseFilename( const std::string& filename,
                    std::string& name,
                    unsigned int& frame,
                    unsigned int& padding,
                    std::string& extension ) {

    xp::sregex rx( xp::sregex::compile( FRAME ) );
    xp::smatch match;

    bool result = false;
    if ( xp::regex_search( filename, match, rx ) ) {

        // File name and extension
        name = match["name"];
        extension = match["extension"];

        // Extract frame and padding
        const std::string frameStr = match["frame"];
        if ( isNumber( frameStr ) ) {
            try {
                frame = boost::lexical_cast< unsigned int >( frameStr );
                padding = static_cast< unsigned int >( frameStr.size() );
                result = true;
            } catch ( boost::bad_lexical_cast& e ) {
            } catch ( ... ) {}
        }
    }
    return result;
}


bool parseSequence( const std::string& filename,
                    std::string& name,
                    unsigned int& padding,
                    std::string& extension ) {

    xp::sregex rx( xp::sregex::compile( SEQUENCE ) );
    xp::smatch match;

    bool result = false;
    if ( xp::regex_search( filename, match, rx ) ) {

        // File name and extension
        name = match["name"];
        extension = match["extension"];

        // Extract frame and padding
        const std::string frameStr = match["padding"];
        if ( isHash( frameStr ) ) {
            padding = static_cast< unsigned int >( frameStr.size() * 4 );
            result = true;
        } else if ( isAt( frameStr ) ) {
            padding = static_cast< unsigned int >( frameStr.size() );
            result = true;
        }
    }
    return result;
}
