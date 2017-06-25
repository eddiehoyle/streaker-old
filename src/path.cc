//
// Created by Eddie Hoyle on 24/06/17.
//

#include <path.hh>
#include <parser.hh>

#include <boost/filesystem.hpp>
#include <padding.hh>

namespace fs = boost::filesystem;

void print( const SequencePath& sequence ) {
    printf( "SequencePath(directory='%s', name='%s', padding=%d, extension='%s')\n",
            sequence.directory().c_str(),
            sequence.name().c_str(),
            sequence.padding(),
            sequence.extension().c_str() );
}

void print( const FramePath& frame ) {
    printf( "FramePath(directory='%s', name='%s', frame=%d, padding=%d, extension='%s')\n",
            frame.directory().c_str(),
            frame.name().c_str(),
            frame.frame(),
            frame.padding(),
            frame.extension().c_str() );
}

AbstractPath::AbstractPath( const std::string& path )
    : m_valid( false ),
      m_name(),
      m_extension(),
      m_directory() {

    fs::path filepath( path );
    if ( !fs::is_directory( path ) ) {
        m_directory = filepath.parent_path().string();
    }
}

std::string AbstractPath::directory() const {
    return m_directory;
}

std::string AbstractPath::name() const {
    return m_name;
}

std::string AbstractPath::extension() const {
    return m_extension;
}

AbstractPath::operator bool() const {
    return m_valid;
}

bool AbstractPath::operator==( const AbstractPath& rhs ) const {
    return m_valid &&
            ( directory() == rhs.directory() ) &&
            ( name() == rhs.name() ) &&
            ( extension() == rhs.extension() );
}

bool AbstractPath::operator!=( const AbstractPath& rhs ) const {
    return !m_valid &&
           ( name() != rhs.name() ) &&
           ( extension() != rhs.extension() );
}

SequencePath::SequencePath( const std::string& path )
        : AbstractPath( path ) {
    m_valid = parseSequence( path, m_name, m_padding, m_extension );
}

unsigned int SequencePath::padding() const {
    return m_padding;
}

bool SequencePath::operator==( const SequencePath& rhs ) const {
    return AbstractPath::operator==( rhs ) &&
            ( padding() == rhs.padding() );
}

bool SequencePath::operator!=( const SequencePath& rhs ) const {
    return AbstractPath::operator!=( rhs ) &&
            ( padding() == rhs.padding() );
}

FramePath::FramePath( const std::string& path )
        : AbstractPath( path ) {
    m_valid = parseFrame( path, m_name, m_frame, m_padding, m_extension );
}

unsigned int FramePath::frame() const {
    return m_frame;
}

unsigned int FramePath::padding() const {
    return m_padding;
}

bool FramePath::match( const SequencePath& sequence ) const {
    return padding() == sequence.padding() ||
            isAmbiguous( frame(), sequence.padding() );
}

bool FramePath::operator==( const FramePath& rhs ) const {
    return AbstractPath::operator==( rhs ) &&
            ( frame() == rhs.frame() ) &&
            ( padding() == rhs.padding() );
}

bool FramePath::operator!=( const FramePath& rhs ) const {
    return AbstractPath::operator!=( rhs ) &&
            ( frame() == rhs.frame() ) &&
            ( padding() == rhs.padding() );

}