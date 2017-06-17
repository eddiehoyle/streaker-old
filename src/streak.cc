//
// Created by Eddie Hoyle on 7/05/17.
//

#include <defs.hh>
#include <streak.hh>

#include <boost/xpressive/xpressive.hpp>
#include <boost/filesystem.hpp>

namespace xp = boost::xpressive;

void print( const Streak& streak ) {
    printf( "Streak(name='%s', range=(%d, %d), frames=%lu, padding=%d, extension='%s')\n",
            streak.getName().c_str(),
            streak.getRange().getFirst(),
            streak.getRange().getLast(),
            streak.getRange().getFrames().size(),
            streak.getPadding(),
            streak.getExtension().c_str() );
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

Streak::Streak( const Streak& streak )
        : m_directory( streak.getDirectory() ),
          m_name( streak.getName() ),
          m_padding( streak.getPadding() ),
          m_range( streak.getRange() ),
          m_extension( streak.getExtension() ) {
}

std::string Streak::getDirectory() const {
    return m_directory;
}

std::string Streak::getName() const {
    return m_name;
}

unsigned int Streak::getPadding() const {
    return m_padding;
}

FrameRange Streak::getRange() const {
    return m_range;
}

std::string Streak::getExtension() const {
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
