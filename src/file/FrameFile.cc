//
// Created by Eddie Hoyle on 8/07/17.
//

#include <streaker/file/FrameFile.hh>
#include <streaker/file/SequenceFile.hh>
#include <streaker/Padding.hh>
#include <streaker/Parser.hh>

FrameFile::FrameFile( const std::string& name,
                      unsigned int frame,
                      unsigned int padding,
                      const std::string& extension )
        : m_frame( frame ),
          m_padding( padding ) {
    m_name = name;
    m_extension = extension;
    m_valid = true;
}

FrameFile::FrameFile( const std::string& path )
        : AbstractFile(),
          m_frame() {
    m_valid = parseFrame( path, m_name, m_frame, m_padding, m_extension );
}

unsigned int FrameFile::frame() const {
    return m_frame;
}

unsigned int FrameFile::padding() const {
    return m_padding;
}

bool FrameFile::match( const SequenceFile& sequence ) const {
    return ( padding() == sequence.padding() ||
             isAmbiguous( frame(), sequence.padding() ) ) &&
           ( name() == sequence.name() ) &&
           ( extension() == sequence.extension() );
}

bool FrameFile::operator==( const FrameFile& rhs ) const {
    return AbstractFile::operator==( rhs ) &&
           ( frame() == rhs.frame() ) &&
           ( padding() == rhs.padding() );
}

bool FrameFile::operator!=( const FrameFile& rhs ) const {
    return AbstractFile::operator!=( rhs ) &&
           ( frame() == rhs.frame() ) &&
           ( padding() == rhs.padding() );
}