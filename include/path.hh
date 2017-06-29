//
// Created by Eddie Hoyle on 24/06/17.
//

#ifndef STREAKER_PATH_HH
#define STREAKER_PATH_HH

#include <string>
#include <parser.hh>
#include <vector>
#include <set>

//#include <memory>

class SequenceFile;
class FrameFile;

typedef std::vector< SequenceFile > SequenceFiles;
typedef std::vector< FrameFile > FrameFiles;

typedef std::set< SequenceFile > SequenceFileSet;
typedef std::set< FrameFile > FrameFileSet;

void print( const SequenceFile& sequence );
void print( const FrameFile& frame );


std::string format( const FrameFile& frame, const std::string& delimeter );
std::string format( const SequenceFile& sequence,
                    unsigned int frame,
                    const std::string& delimeter );

//typedef std::shared_ptr< SequenceFile > SequenceFilePtr;

/*
 * Design notes:
 *  A sequence path is an object that given a path, represents
 *  a name, padding value and extension. This object includes
 *  public methods to retrieve this data.
 */

class AbstractFile {

public:
    AbstractFile();
    explicit AbstractFile( const std::string& path );
    operator bool() const;
    bool operator==( const AbstractFile& rhs ) const;
    bool operator!=( const AbstractFile& rhs ) const;
//    std::string filename() const;
    std::string name() const;
    std::string extension() const;

protected:
    bool m_valid;
    std::string m_name;
    std::string m_extension;
};

class SequenceFile : public AbstractFile {

public:
    explicit SequenceFile( const std::string& name,
                           unsigned int padding,
                           const std::string& extension );
    explicit SequenceFile( const std::string& path );
    bool operator==( const SequenceFile& rhs ) const;
    bool operator!=( const SequenceFile& rhs ) const;
    unsigned int padding() const;

private:
    unsigned int m_padding;
};


class FrameFile : public AbstractFile {

public:
    explicit FrameFile( const std::string& name,
                        unsigned int frame,
                        unsigned int padding,
                        const std::string& extension );
    explicit FrameFile( const std::string& path );
    bool operator==( const FrameFile& rhs ) const;
    bool operator!=( const FrameFile& rhs ) const;
    unsigned int frame() const;
    unsigned int padding() const;
    bool match( const SequenceFile& sequence ) const;
    SequenceFile sequence() const;

private:
    unsigned int m_frame;
    unsigned int m_padding;
};

#endif //STREAKER_PATH_HH
