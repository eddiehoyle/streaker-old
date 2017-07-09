//
// Created by Eddie Hoyle on 7/05/17.
//

#include <streaker/Range.hh>
#include <numeric>
#include <sstream>

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
    return ( getCount() == rhs.getCount() ) &&
           ( frames() == rhs.frames() );
}