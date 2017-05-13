//
// Created by Eddie Hoyle on 7/05/17.
//

#ifndef STREAKER_RANGE_HH
#define STREAKER_RANGE_HH

#include <vector>
#include <algorithm>

typedef std::vector< int > Frames;

class FrameRange;

class FrameRange {

    /*
     * Represents a frame range for a sequence of paths
     *
     * Notes:
     * 1. may contain skipped frames, eg: evens, odds, every 5th
     * */

public:
    FrameRange();
    explicit FrameRange( int first, int last );
    ~FrameRange();

    void addFrame( int frame );

    void setFrames( const Frames& frames );

    // Sorted frames
    Frames getFrames() const;

    std::size_t getFrameCount() const;

    int getFirst() const;
    int getLast() const;

    bool operator==( const FrameRange& rhs ) {
        return std::equal( this->getFrames().begin(),
                           this->getFrames().begin() + this->getFrameCount(),
                           rhs.getFrames().begin() );
    }

private:
    void setDirty( bool state );
    bool isDirty() const;
    void update();

private:

    // Frames vector
    Frames m_frames;

    // Cache important frames
    int m_first;
    int m_last;

    // Frames vector updated state
    bool m_isDirty;

};

#endif //STREAKER_RANGE_HH
