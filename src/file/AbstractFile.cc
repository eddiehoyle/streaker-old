//
// Created by Eddie Hoyle on 8/07/17.
//

#include <streaker/file/AbstractFile.hh>
#include <streaker/file/SequenceFile.hh>
#include <streaker/file/FrameFile.hh>

namespace streaker {

AbstractFile::AbstractFile()
        : m_valid( false ),
          m_name(),
          m_extension() {
}

std::string AbstractFile::name() const {
    return m_name;
}

std::string AbstractFile::extension() const {
    return m_extension;
}

AbstractFile::operator bool() const {
    return m_valid;
}

bool AbstractFile::operator==( const AbstractFile& rhs ) const {
    return m_valid &&
           ( name() == rhs.name() ) &&
           ( extension() == rhs.extension() );
}

bool AbstractFile::operator!=( const AbstractFile& rhs ) const {
    return !m_valid &&
           ( name() != rhs.name() ) &&
           ( extension() != rhs.extension() );
}

} // namespace streaker