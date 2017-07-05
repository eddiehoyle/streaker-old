//
// Created by Eddie Hoyle on 24/06/17.
//

#include <path.hh>
#include <parser.hh>

#include <boost/filesystem.hpp>
#include <padding.hh>

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

namespace fs = boost::filesystem;

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
                    const std::string& delimeter ) {

    std::ostringstream stream;
    stream << sequence.name();
    stream << delimeter;
    stream << std::setfill( '0' ) << std::setw( sequence.padding() ) << frame;
    stream << delimeter;

    // Add '.' before extension
    if ( delimeter.empty() ) {
        stream << ".";
    } else {
        if ( delimeter.back() != '.' ) {
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

AbstractFile::AbstractFile()
        : m_valid( false ),
          m_name(),
          m_extension() {
}

std::string AbstractFile::name() const {
    return m_name;
}

std::string AbstractFile::extension() const {
    return m_extension;
}

AbstractFile::operator bool() const {
    return m_valid;
}

bool AbstractFile::operator==( const AbstractFile& rhs ) const {
    return m_valid &&
           ( name() == rhs.name() ) &&
           ( extension() == rhs.extension() );
}

bool AbstractFile::operator!=( const AbstractFile& rhs ) const {
    return !m_valid &&
           ( name() != rhs.name() ) &&
           ( extension() != rhs.extension() );
}

SequenceFile::SequenceFile( const std::string& path )
        : AbstractFile() {
    m_valid = parseSequence( path, m_name, m_padding, m_extension );
}

SequenceFile::SequenceFile( const std::string& name,
                            unsigned int padding,
                            const std::string& extension )
        : m_padding( padding ) {
    m_name = name;
    m_extension = extension;
    m_valid = true;
}

unsigned int SequenceFile::padding() const {
    return m_padding;
}

bool SequenceFile::operator<( const SequenceFile& rhs ) const {
    return padding() < rhs.padding();
}
bool SequenceFile::operator>( const SequenceFile& rhs ) const {
    return padding() < rhs.padding();
}

bool SequenceFile::operator==( const SequenceFile& rhs ) const {
    return AbstractFile::operator==( rhs ) &&
           ( padding() == rhs.padding() );
}

bool SequenceFile::operator!=( const SequenceFile& rhs ) const {
    return AbstractFile::operator!=( rhs ) &&
           ( padding() == rhs.padding() );
}


FrameFile::FrameFile( const std::string& name,
                      unsigned int frame,
                      unsigned int padding,
                      const std::string& extension )
        : m_frame( frame ),
          m_padding( padding ) {
    m_name = name;
    m_extension = extension;
    m_valid = true;
}

FrameFile::FrameFile( const std::string& path )
        : AbstractFile(),
          m_frame() {
    m_valid = parseFrame( path, m_name, m_frame, m_padding, m_extension );
}

unsigned int FrameFile::frame() const {
    return m_frame;
}

unsigned int FrameFile::padding() const {
    return m_padding;
}

bool FrameFile::match( const SequenceFile& sequence ) const {
    return ( padding() == sequence.padding() ||
             isAmbiguous( frame(), sequence.padding() ) ) &&
           ( name() == sequence.name() ) &&
           ( extension() == sequence.extension() );
}

bool FrameFile::operator==( const FrameFile& rhs ) const {
    return AbstractFile::operator==( rhs ) &&
           ( frame() == rhs.frame() ) &&
           ( padding() == rhs.padding() );
}

bool FrameFile::operator!=( const FrameFile& rhs ) const {
    return AbstractFile::operator!=( rhs ) &&
           ( frame() == rhs.frame() ) &&
           ( padding() == rhs.padding() );

}