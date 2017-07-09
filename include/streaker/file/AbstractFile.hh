//
// Created by Eddie Hoyle on 8/07/17.
//

#ifndef STREAKER_ABSTRACTFILE_HH
#define STREAKER_ABSTRACTFILE_HH

#include <string>

class AbstractFile {

public:
    AbstractFile();
    explicit AbstractFile( const std::string& path );
    operator bool() const;
    bool operator==( const AbstractFile& rhs ) const;
    bool operator!=( const AbstractFile& rhs ) const;
    std::string name() const;
    std::string extension() const;

protected:
    bool m_valid;
    std::string m_name;
    std::string m_extension;
};

#endif //STREAKER_ABSTRACTFILE_HH
