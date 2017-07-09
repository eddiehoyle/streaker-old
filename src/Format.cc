//
// Created by Eddie Hoyle on 8/07/17.
//

#include <streaker/file/SequenceFile.hh>
#include <streaker/file/FrameFile.hh>
#include <streaker/Streak.hh>

#include <iomanip>
#include <sstream>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace streaker {

std::string format( const FrameFile& frame, const std::string& delimeter ) {

    std::ostringstream stream;
    stream << frame.name();
    stream << delimeter;
    stream << std::setfill( '0' ) << std::setw( frame.padding() ) << frame.frame();
    stream << delimeter;

    // Add '.' before extension
    if ( delimeter.empty() ) {
        stream << ".";
    } else {
        if ( delimeter.back() != '.' ) {
            stream << ".";
        }
    }

    stream << frame.extension();
    return stream.str();
}

std::string format( const SequenceFile& sequence,
                    unsigned int frame,
                    const std::string& delimiter ) {

    std::ostringstream stream;
    stream << sequence.name();
    stream << delimiter;
    stream << std::setfill( '0' ) << std::setw( sequence.padding() ) << frame;
    stream << delimiter;

    // Add '.' before extension
    if ( delimiter.empty() ) {
        stream << ".";
    } else {
        if ( delimiter.back() != '.' ) {
            stream << ".";
        }
    }

    stream << sequence.extension();
    return stream.str();
}

fs::path normalize( const fs::path& path ) {
    fs::path normalized;
    for ( const fs::path& segment : path ) {
        if ( segment.string() == ".." ) {
            normalized = normalized.parent_path();
            continue;
        }
        normalized /= segment;
    }
    return normalized;
}

void print( const SequenceFile& sequence ) {
    printf( "SequenceFile(name='%s', padding=%d, extension='%s')\n",
            sequence.name().c_str(),
            sequence.padding(),
            sequence.extension().c_str() );
}

void print( const FrameFile& frame ) {
    printf( "FrameFile(name='%s', frame=%d, padding=%d, extension='%s')\n",
            frame.name().c_str(),
            frame.frame(),
            frame.padding(),
            frame.extension().c_str() );
}

void print( const Streak& streak ) {
    printf( "Streak(name='%s', range=(%d, %d), frames=%lu, padding=%d, extension='%s')\n",
            streak.name().c_str(),
            streak.range().getFirst(),
            streak.range().getLast(),
            streak.range().frames().size(),
            streak.padding(),
            streak.extension().c_str() );
}

} // namespace streaker