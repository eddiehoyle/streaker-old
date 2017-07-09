//
// Created by Eddie Hoyle on 8/07/17.
//

#ifndef STREAKER_FORMATTER_HH
#define STREAKER_FORMATTER_HH

#include <set>
#include <vector>
#include <string>

class SequenceFile;
class FrameFile;
class Streak;

void print( const SequenceFile& sequence );
void print( const FrameFile& frame );
void print( const Streak& streak );

std::string format( const FrameFile& frame, const std::string& delimeter );
std::string format( const SequenceFile& sequence,
                    unsigned int frame,
                    const std::string& delimeter );

#endif //STREAKER_FORMATTER_HH
