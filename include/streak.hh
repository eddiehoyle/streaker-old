//
// Created by Eddie Hoyle on 7/05/17.
//

#ifndef STREAKER_STREAK_HH
#define STREAKER_STREAK_HH

#include <boost/filesystem.hpp>
#include <iostream>

#include "range.hh"
#include "padding.hh"


class Streak;
class StreakProxy;

typedef std::vector< Streak > Streaks;

void print( const Streak& streak );

class Streak {

    /* Represents a file path with a frame range */

public:

    // TODO
    Streak() {}
    ~Streak() {}
    explicit Streak( const std::string& directory,
                     const std::string& name,
                     const FrameRange& range,
                     unsigned int padding,
                     const std::string& extension );

    Streak( const Streak& streak );

    std::string getDirectory() const;
    std::string getName() const;
    FrameRange getRange() const;
    unsigned int getPadding() const;
    std::string getExtension() const;

    void setDirectory( const std::string& directory );
    void setName( const std::string& name );
    void setPadding( unsigned int padding );
    void setRange( const FrameRange& range );
    void setExtension( const std::string& extension );

    operator bool() const {
        return !( m_name.empty() || m_extension.empty() );
    }

    bool operator==( const Streak& rhs ) {
        return bool( *this ) &&
                ( this->getExtension() == rhs.getExtension() ) &&
                ( this->getRange() == rhs.getRange() ) &&
                ( this->getName() == rhs.getName() );
    }

    bool operator!=( const Streak& rhs ) {
        return !( *this == rhs );
    }

private:
    void initialise( const boost::filesystem::path& path );

private:

    std::string m_directory;
    std::string m_name;
    FrameRange m_range;
    unsigned int m_padding;
    std::string m_extension;
};

#endif //STREAKER_STREAK_HH
