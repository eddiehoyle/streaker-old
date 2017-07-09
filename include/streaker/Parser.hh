#ifndef STREAKER_PARSER_HH
#define STREAKER_PARSER_HH

#include <string>
#include <algorithm>

namespace streaker {

/// Parse a frame number filename, eg: "test.1001.exr"
bool parseFrame( const std::string& filename,
                 std::string& name,
                 unsigned int& frame,
                 unsigned int& padding,
                 std::string& extension );

/// Parse a sequence filename, eg: "test.#.exr"
bool parseSequence( const std::string& filename,
                    std::string& name,
                    unsigned int& padding,
                    std::string& extension );

inline bool isNumber( const std::string& pattern ) {
    return std::all_of( pattern.begin(),
                        pattern.end(),
                        isdigit );
}

inline bool isHash( const std::string& pattern ) {
    return std::all_of( pattern.begin(),
                        pattern.end(),
                        []( char c ) { return c == '#'; } );
}

inline bool isAt( const std::string& pattern ) {
    return std::all_of( pattern.begin(),
                        pattern.end(),
                        []( char c ) { return c == '@'; } );
}

} // namespace streaker;

#endif // STREAKER_PARSER_HH
