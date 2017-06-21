//
// Created by Eddie Hoyle on 21/06/17.
//

#include <defs.hh>
#include <frame.hh>

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/xpressive/xpressive.hpp>

namespace xp = boost::xpressive;
namespace fs = boost::filesystem;


bool fromFilename( const std::string& filepath, Frame& frame ) {

    fs::path path( filepath );
    if ( !fs::is_regular_file( path ) ) {
        return false;
    }
    return true;
}

Frame::Frame( unsigned int frame, unsigned int padding )
        : m_frame( frame ),
          m_padding( padding ) {}

unsigned int Frame::getFrame() const {
    return m_frame;
}

unsigned int Frame::getPadding() const {
    return m_padding;
}

PaddingType Frame::getType() const {
    return getPaddingType( m_frame, m_padding );
}
