//
// Created by Eddie Hoyle on 7/05/17.
//

#include <defs.hh>
#include <streak.hh>

#include <boost/xpressive/xpressive.hpp>
#include <boost/filesystem.hpp>

namespace xp = boost::xpressive;

Streak::Streak( const std::string& directory,
                const std::string& name,
                const FrameRange& range,
                const std::string& extension ) {
}

std::string Streak::getDirectory() const {
    return m_directory;
}

std::string Streak::getName() const {
    return m_name;
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

void Streak::setRange( const FrameRange& range ) {
    m_range = range;
}

void Streak::setExtension( const std::string& extension ) {
    m_extension = extension;
}

std::string Streak::getFrame( const std::string& frame ) {
    return std::string();
}

std::string Streak::getFrame( int frame ) {
    return std::string();
}