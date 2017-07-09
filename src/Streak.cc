//
// Created by Eddie Hoyle on 7/05/17.
//

#include <streaker/Streak.hh>
#include <streaker/file/SequenceFile.hh>
#include <streaker/file/FrameFile.hh>

#include <boost/xpressive/xpressive.hpp>

namespace xp = boost::xpressive;

Streak::Streak()
        : m_directory(),
          m_name(),
          m_padding(),
          m_range(),
          m_extension() {
}

Streak::Streak( const std::string& directory,
                const std::string& name,
                const FrameRange& range,
                unsigned int padding,
                const std::string& extension )
        : m_directory( directory ),
          m_name( name ),
          m_padding( padding ),
          m_range( range ),
          m_extension( extension ) {
}

Streak::Streak( const std::string& directory,
                const SequenceFile& sequence,
                const FrameRange& range )
        : m_directory( directory ),
          m_name( sequence.name() ),
          m_padding( sequence.padding() ),
          m_range( range ),
          m_extension( sequence.extension() ) {
}

Streak::Streak( const Streak& streak )
        : m_directory( streak.directory() ),
          m_name( streak.name() ),
          m_padding( streak.padding() ),
          m_range( streak.range() ),
          m_extension( streak.extension() ) {
}

Streak::operator bool() const {
    return !m_range.frames().empty();
}

bool Streak::operator==( const Streak& rhs ) {
    return ( this->extension() == rhs.extension() ) &&
           ( this->range() == rhs.range() ) &&
           ( this->name() == rhs.name() );
}

bool Streak::operator!=( const Streak& rhs ) {
    return !( *this == rhs );
}

std::string Streak::directory() const {
    return m_directory;
}

std::string Streak::name() const {
    return m_name;
}

unsigned int Streak::padding() const {
    return m_padding;
}

FrameRange Streak::range() const {
    return m_range;
}

std::string Streak::extension() const {
    return m_extension;
}

void Streak::setDirectory( const std::string& directory ) {
    m_directory = directory;
}

void Streak::setName( const std::string& name ) {
    m_name = name;
}

void Streak::setPadding( unsigned int padding ) {
    m_padding = padding;
}

void Streak::setRange( const FrameRange& range ) {
    m_range = range;
}

void Streak::setExtension( const std::string& extension ) {
    m_extension = extension;
}
