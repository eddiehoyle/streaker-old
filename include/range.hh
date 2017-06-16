//
// Created by Eddie Hoyle on 7/05/17.
//

#ifndef STREAKER_RANGE_HH
#define STREAKER_RANGE_HH

#include <vector>
#include <algorithm>
#include <set>
#include <map>

#include <padding.hh>
#include <frame.hh>

class FrameRange;

typedef std::map< int, Padding > FrameMap;
typedef std::set< FramePair > FrameSet;

class FrameRange {

public:
    FrameRange();
    explicit FrameRange( int first, int last, const Padding& padding );
    explicit FrameRange( const FrameSet& frames );

    void addFrame( int frame, const Padding& padding );
    void addFrame( const FramePair& frame );

    void setFrames( const FrameSet& frames );
    FrameSet getFrames() const;

    std::size_t getCount() const;

    int getFirst() const;
    int getLast() const;

    bool operator==( const FrameRange& range ) const {
        return true;
    }

private:

    // Frames vector
    FrameMap m_frames;

};

#endif //STREAKER_RANGE_HH
