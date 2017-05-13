//
// Created by Eddie Hoyle on 7/05/17.
//

#include "range.hh"

FrameRange::FrameRange()
        : m_first( 0 ),
          m_last( 0 ),
          m_isDirty( true ),
          m_frames() {
}

FrameRange::FrameRange( int first, int last )
        : m_first( first ),
          m_last( last ),
          m_isDirty( true ),
          m_frames() {

    // Generate frames
}

void FrameRange::setDirty( bool state ) {
    m_isDirty = state;
}

bool FrameRange::isDirty() const {
    return m_isDirty;
}

void FrameRange::update() {

    if ( !isDirty() ) {
        return;
    }

    if ( getFrameCount() == 0 ) {
        return;
    }

    std::sort( m_frames.begin(), m_frames.end() );
    m_first = m_frames.front();
    m_last = m_frames.back();
}

void FrameRange::addFrame( int frame ) {

    if ( getFrameCount() == 0 ) {
        m_frames.push_back( frame );
        setDirty( true );
        return;
    }

    if ( std::find( m_frames.begin(), m_frames.end(), frame ) != m_frames.end() ) {
        m_frames.push_back( frame );
        setDirty( true );
        return;
    }
}

std::size_t FrameRange::getFrameCount() const {
    return m_frames.size();
}

int FrameRange::getFirst() const {
    return m_first;
}

int FrameRange::getLast() const {
    return m_last;
}

FrameRange::~FrameRange() {

}