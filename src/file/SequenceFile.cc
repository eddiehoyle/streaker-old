//
// Created by Eddie Hoyle on 8/07/17.
//

#include <streaker/file/SequenceFile.hh>

#include <streaker/Parser.hh>

SequenceFile::SequenceFile( const std::string& path )
        : AbstractFile() {
    m_valid = parseSequence( path, m_name, m_padding, m_extension );
}

SequenceFile::SequenceFile( const std::string& name,
                            unsigned int padding,
                            const std::string& extension )
        : m_padding( padding ) {
    m_name = name;
    m_extension = extension;
    m_valid = true;
}

unsigned int SequenceFile::padding() const {
    return m_padding;
}

bool SequenceFile::operator<( const SequenceFile& rhs ) const {
    return padding() < rhs.padding();
}
bool SequenceFile::operator>( const SequenceFile& rhs ) const {
    return padding() < rhs.padding();
}

bool SequenceFile::operator==( const SequenceFile& rhs ) const {
    return AbstractFile::operator==( rhs ) &&
           ( padding() == rhs.padding() );
}

bool SequenceFile::operator!=( const SequenceFile& rhs ) const {
    return AbstractFile::operator!=( rhs ) &&
           ( padding() == rhs.padding() );
}
