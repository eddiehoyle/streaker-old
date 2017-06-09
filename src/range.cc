//
// Created by Eddie Hoyle on 7/05/17.
//

#include <range.hh>
#include <numeric>


FrameRange::FrameRange( const Frames& frames )
        : m_first( 0 ),
          m_last( 0 ),
          m_isDirty( true ),
          m_frames( frames ) {
}

FrameRange::FrameRange()
        : m_first( 0 ),
          m_last( 0 ),
          m_isDirty( true ),
          m_frames() {
}

FrameRange::FrameRange( int first, int last, unsigned int padding )
        : m_first( first ),
          m_last( last ),
          m_isDirty( true ),
          m_frames() {

    if ( first > last ) {
        m_first = 0;
        m_last = 0;
    } else {
        while ( first < last ) {
            m_frames.push_back( Frame( first, padding ) );
            first++;
        }
    }
}

void FrameRange::setFrames( const Frames& frames ) {
    m_frames = frames;
    setDirty( true );
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

    // Update
    std::sort( m_frames.begin(), m_frames.end(),
               []( const Frame& a, const Frame& b ){
                   return a.getFrame() < b.getFrame();
               } );
    m_first = m_frames.front().getFrame();
    m_last = m_frames.back().getFrame();
}

void FrameRange::addFrame( int frame ) {

//    if ( getFrameCount() == 0 ) {
//        m_frames.push_back( frame );
//        setDirty( true );
//        return;
//    }
//
//    if ( std::find( m_frames.begin(), m_frames.end(), frame ) == m_frames.end() ) {
//        m_frames.push_back( frame );
//        setDirty( true );
//        return;
//    }
}

Frames FrameRange::getFrames() const {
    return m_frames;
}

std::size_t FrameRange::getFrameCount() const {
    return m_frames.size();
}

int FrameRange::getFirst() {
    if ( isDirty() ) {
        update();
    }
    return m_first;
}

int FrameRange::getLast() {
    if ( isDirty() ) {
        update();
    }
    return m_last;
}

FrameRange::~FrameRange() {

}