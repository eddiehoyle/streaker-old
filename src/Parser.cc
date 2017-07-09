//
// Created by Eddie Hoyle on 21/06/17.
//

#include <streaker/Parser.hh>

#include <boost/lexical_cast.hpp>
#include <boost/xpressive/xpressive.hpp>


/// # or @ sequence
/// TODO:
/// Write a smarter capture pattern to extract delimeters
static const char* SEQUENCE = "(?P<name>\\w+)[\\.|_](?P<padding>[@|#]+)[\\.](?P<extension>\\w+)$";

/// Numbered frame
/// TODO:
/// Write a smarter capture pattern to extract delimeters
static const char* FRAME = "(?P<name>\\w+)[\\.|_](?P<frame>[0-9]+)[\\.](?P<extension>\\w+)$";

namespace xp = boost::xpressive;

bool parseFrame( const std::string& filename,
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