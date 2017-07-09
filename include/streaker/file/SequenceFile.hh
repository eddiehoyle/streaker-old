#ifndef STREAKER_SEQUENCEFILE_HH
#define STREAKER_SEQUENCEFILE_HH

#include "AbstractFile.hh"

#include <vector>

namespace streaker {

class SequenceFile;

typedef std::vector< SequenceFile > SequenceFiles;

class SequenceFile : public AbstractFile {

public:
    explicit SequenceFile( const std::string& name,
                           unsigned int padding,
                           const std::string& extension );
    explicit SequenceFile( const std::string& path );
    bool operator<( const SequenceFile& rhs ) const;
    bool operator>( const SequenceFile& rhs ) const;
    bool operator==( const SequenceFile& rhs ) const;
    bool operator!=( const SequenceFile& rhs ) const;
    unsigned int padding() const;

private:
    unsigned int m_padding;
};

} // namespace streaker

#endif // STREAKER_SEQUENCEFILE_HHw
