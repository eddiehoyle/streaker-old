#ifndef STREAKER_FRAMEFILE_HH
#define STREAKER_FRAMEFILE_HH

#include "AbstractFile.hh"

#include <vector>

namespace streaker {

class FrameFile;
class SequenceFile;

typedef std::vector< FrameFile > FrameFiles;

class FrameFile : public AbstractFile {

public:
    explicit FrameFile( const std::string& name,
                        unsigned int frame,
                        unsigned int padding,
                        const std::string& extension );
    explicit FrameFile( const std::string& path );
    bool operator<( const FrameFile& rhs ) const;
    bool operator>( const FrameFile& rhs ) const;
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

} // namespace streaker

#endif // STREAKER_FRAMEFILE_HH
