//
// Created by Eddie Hoyle on 7/05/17.
//

#include <range.hh>
#include <numeric>
#include <sstream>

void print( const FrameRange& range ) {

    // Example:
    // 1, 2, 3, 5
    // 1-3, 5

    std::ostringstream stream;

//    const FrameSet frames = range.frames();
//    for ( FrameSet::const_iterator iter = frames.begin();
//          iter != frames.end();
//          ++iter ) {
//
//        unsigned int frame = *iter;
//        stream << frame;
//
//        ++iter;

//        if ( iter != frames.end() ) {
//
//            unsigned int next = *iter;
//            if ( ( next - frame ) == 1 ) {
//                continue;
//            }
//        }
//    }

    printf( "%s\n", stream.str().c_str() );

}

FrameRange::FrameRange()
        : m_frames() {}

FrameRange::FrameRange( unsigned int first, unsigned int last )
        : m_frames() {

    if ( first > last ) {
        return;
    }

    for ( unsigned int frame = first; frame < last; ++frame )
        m_frames.insert( m_frames.end(), frame );
}

FrameRange::~FrameRange() {}

void FrameRange::addFrame( unsigned int frame ) {
    m_frames.insert( frame );
}

void FrameRange::addFrames( const FrameSet& frames ) {
    m_frames.insert( frames.begin(), frames.end() );
}

void FrameRange::setFrames( const FrameSet& frames ) {
    m_frames = frames;
}

FrameSet FrameRange::frames() const {
    return m_frames;
}

std::size_t FrameRange::getCount() const {
    return m_frames.size();
}

unsigned int FrameRange::getFirst() const {
    return !m_frames.empty() ? *m_frames.begin() : 0;
}

unsigned int FrameRange::getLast() const {
    return !m_frames.empty() ? *m_frames.rbegin() : 0;
}

bool FrameRange::operator==( const FrameRange& rhs ) const {
    return frames() == rhs.frames();
}