//
// Created by Eddie Hoyle on 21/06/17.
//

#ifndef STREAKER_PARSER_HH_HH
#define STREAKER_PARSER_HH_HH

#include <iostream>

bool parseFrame( const std::string& frameStr,
                 unsigned int* frame,
                 unsigned int* padding );

bool parseFilename( const std::string& filename,
                    std::string& name,
                    unsigned int* frame,
                    unsigned int* padding,
                    std::string& extension );

#endif //STREAKER_PARSER_HH_HH
