//
// Created by Eddie Hoyle on 7/05/17.
//

#include <range.hh>
#include <numeric>
#include <vector>

FrameRange::FrameRange()
        : m_frames() {}

FrameRange::FrameRange( int first, int last )
        : m_frames() {

    if ( first > last ) {
        return;
    }

    for ( int frame = first; frame < last; ++frame )
        m_frames.insert( m_frames.end(), frame );
}

FrameRange::~FrameRange() {}

void FrameRange::addFrame( int frame ) {
    m_frames.insert( frame );
}

FrameSet FrameRange::getFrames() const {
    return m_frames;
}

std::size_t FrameRange::getCount() const {
    return m_frames.size();
}

int FrameRange::getFirst() const {
    return !m_frames.empty() ? *m_frames.begin() : 0;
}

int FrameRange::getLast() const {
    return !m_frames.empty() ? *m_frames.rbegin() : 0;
}

bool FrameRange::operator==( const FrameRange& rhs ) const {
    return getFrames() == rhs.getFrames();
}