//
// Created by Eddie Hoyle on 7/05/17.
//

#ifndef STREAKER_STREAK_HH
#define STREAKER_STREAK_HH

#include <streaker/Range.hh>

#include <vector>
#include <string>

class Streak;
class SequenceFile;

typedef std::vector< Streak > Streaks;

class Streak {

public:
    Streak();
    explicit Streak( const std::string& directory,
                     const std::string& name,
                     const FrameRange& range,
                     unsigned int padding,
                     const std::string& extension );
    explicit Streak( const std::string& directory,
                     const SequenceFile& sequence,
                     const FrameRange& range );
    Streak( const Streak& streak );

    std::string directory() const;
    std::string name() const;
    FrameRange range() const;
    unsigned int padding() const;
    std::string extension() const;

    void setDirectory( const std::string& directory );
    void setName( const std::string& name );
    void setPadding( unsigned int padding );
    void setRange( const FrameRange& range );
    void setExtension( const std::string& extension );

    operator bool() const;
    bool operator==( const Streak& rhs );
    bool operator!=( const Streak& rhs );

public:
    std::string iterator;

private:
    std::string m_directory;
    std::string m_name;
    FrameRange m_range;
    unsigned int m_padding;
    std::string m_extension;
};

#endif //STREAKER_STREAK_HH
