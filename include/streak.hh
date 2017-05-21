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
void print( const StreakProxy& proxy );

class StreakProxy {

public:
    StreakProxy( const std::string& name,
                 const std::string& extension )
            : m_name( name ),
              m_extension( extension ) {
    }

    operator bool() const {
        return !( m_name.empty() && m_extension.empty() );
    }

    bool operator==( const StreakProxy& rhs ) const {
        return ( this->getName() == rhs.getName() &&
                 this->getExtension() == rhs.getExtension() );
    }

    const std::string& getName() const {
        return m_name;
    }

    const std::string& getExtension() const {
        return m_extension;
    }
private:
    std::string m_name;
    std::string m_extension;
};


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

    Streak( const Streak& streak );

    std::string getDirectory() const;
    std::string getName() const;
    Padding getPadding() const;
    FrameRange getRange() const;
    std::string getExtension() const;

    std::string getFrame( int frame );

    void setDirectory( const std::string& directory );
    void setName( const std::string& name );
    void setPadding( const Padding& padding );
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
    Padding m_padding;
    FrameRange m_range;
    std::string m_extension;
};

#endif //STREAKER_STREAK_HH
