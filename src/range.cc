//
// Created by Eddie Hoyle on 7/05/17.
//

#include <range.hh>
#include <numeric>
#include <vector>

FrameRange::FrameRange()
        : m_frames() {
}

FrameRange::FrameRange( int first, int last, const Padding& padding )
        : m_frames() {

    if ( first > last ) {
        return;
    }

    int frame = first;
    while ( frame < last ) {
        m_frames[ first ] = padding;
        frame++;
    }
}

FrameRange::FrameRange( const FrameSet& frames )
        : m_frames() {
    for ( const FramePair& pair : frames ) {
        m_frames[ pair.first ] = pair.second;
    }
}

void FrameRange::addFrame( int frame, const Padding& padding ) {
    m_frames[ frame ] = padding;
}

void FrameRange::setFrames( const FrameSet& frames ) {
    for ( const FramePair& pair : frames ) {
        m_frames[ pair.first ] = pair.second;
    }
}

FrameSet FrameRange::getFrames() const {
    FrameSet frames;
    for ( const FramePair& pair : m_frames ) {
        frames.insert( pair );
    }
    return frames;
}

std::size_t FrameRange::getCount() const {
    return m_frames.size();
}

int FrameRange::getFirst() const {
    return m_frames.begin()->first;
}

int FrameRange::getLast() const {
    return m_frames.rbegin()->first;
}