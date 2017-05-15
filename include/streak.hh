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
typedef std::vector< Streak > Streaks;

class Streak {

    /* Represents a file path with a frame range */

public:

    Streak() {}
    ~Streak() {}
    explicit Streak( const std::string& directory,
                     const std::string& name,
                     const Padding& padding,
                     const FrameRange& range,
                     const std::string& extension );

    std::string getDirectory() const;
    std::string getName() const;
    Padding getPadding() const;
    FrameRange getRange() const;
    std::string getExtension() const;

    void setDirectory( const std::string& directory );
    void setName( const std::string& name );
    void setPadding( const Padding& padding );
    void setRange( const FrameRange& range );
    void setExtension( const std::string& extension );

    std::string getFrame( const std::string& frame );
    std::string getFrame( int frame );

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

    void print() const {
        printf( "Streak(name='%s', range=(%d, %d), extension='%s')\n",
                getName().c_str(),
                getRange().getFirst(),
                getRange().getLast(),
                getExtension().c_str() );
    }

private:
    void initialise( const boost::filesystem::path& path );

private:

    std::string m_directory;
    std::string m_name;
    Padding m_padding;
    FrameRange m_range;
    std::string m_extension;



};

#endif //STREAKER_STREAK_HH
