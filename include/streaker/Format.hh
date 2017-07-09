#ifndef STREAKER_FORMATTER_HH
#define STREAKER_FORMATTER_HH

#include <set>
#include <vector>
#include <string>

namespace streaker {

class SequenceFile;
class FrameFile;
class Streak;
class FrameRange;

void print( const SequenceFile& sequence );
void print( const FrameFile& frame );
void print( const Streak& streak );
void print( const FrameRange& range );

std::string format( const FrameFile& frame, const std::string& delimeter );
std::string format( const SequenceFile& sequence,
                    unsigned int frame,
                    const std::string& delimeter );

} // namespace streaker

#endif // STREAKER_FORMATTER_HH
