//
// Created by Eddie Hoyle on 24/06/17.
//

#ifndef STREAKER_PATH_HH
#define STREAKER_PATH_HH

#include <string>
#include <parser.hh>

#include <boost/shared_ptr.hpp>

class SequencePath;
class FramePath;

void print( const SequencePath& sequence );
void print( const FramePath& frame );

typedef boost::shared_ptr< SequencePath > SequencePathPtr;

/*
 * Design notes:
 *  A sequence path is an object that given a path, represents
 *  a name, padding value and extension. This object includes
 *  public methods to retrieve this data.
 */

class AbstractPath {

public:
    explicit AbstractPath( const std::string& path );
    operator bool() const;
    bool operator==( const AbstractPath& rhs ) const;
    bool operator!=( const AbstractPath& rhs ) const;
    std::string directory() const;
    std::string name() const;
    std::string extension() const;

protected:
    bool m_valid;
    std::string m_name;
    std::string m_extension;
    std::string m_directory;
};

class SequencePath : public AbstractPath {

public:
    explicit SequencePath( const std::string& path );
    bool operator==( const SequencePath& rhs ) const;
    bool operator!=( const SequencePath& rhs ) const;
    unsigned int padding() const;

private:
    unsigned int m_padding;
};


class FramePath : public AbstractPath {

public:
    explicit FramePath( const std::string& path );
    bool operator==( const FramePath& rhs ) const;
    bool operator!=( const FramePath& rhs ) const;
    unsigned int frame() const;
    unsigned int padding() const;
    bool match( const SequencePath& sequence ) const;

private:
    unsigned int m_frame;
    unsigned int m_padding;
};

#endif //STREAKER_PATH_HH
