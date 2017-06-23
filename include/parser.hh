//
// Created by Eddie Hoyle on 21/06/17.
//

#ifndef STREAKER_PARSER_HH
#define STREAKER_PARSER_HH

#include <iostream>

/// Parse a frame number filename, eg: "test.1001.exr"
bool parseFilename( const std::string& filename,
                    std::string& name,
                    unsigned int& frame,
                    unsigned int& padding,
                    std::string& extension );

/// Parse a sequence filename, eg: "test.#.exr"
bool parseSequence( const std::string& filename,
                    std::string& name,
                    unsigned int& padding,
                    std::string& extension );

#endif //STREAKER_PARSER_HH
