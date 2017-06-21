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

typedef std::set< unsigned int > FrameSet;

class FrameRange {

    /// Represents a range of numbers that share a padding fill value
    /// 1, 2, 3 ... 1001, 1002
    /// 001, 002, 003 ... 1001, 1002

public:

    // TODO
    FrameRange();
    ~FrameRange();
    explicit FrameRange( unsigned int first, unsigned int last );

    void addFrame( unsigned int frame );
    void addFrames( const FrameSet& frames );
    FrameSet getFrames() const;

    std::size_t getCount() const;

    unsigned int getFirst() const;
    unsigned int getLast() const;

    bool operator==( const FrameRange& rhs ) const;

private:

    FrameSet m_frames;

};







//
//
//class FrameRange {
//
//public:
//    FrameRange();
//    explicit FrameRange( int first, int last, const Padding& padding );
//    explicit FrameRange( const FrameSet& frames );
//
//    void addFrame( int frame, const Padding& padding );
//    void addFrame( const FramePair& frame );
//
//    void setFrames( const FrameSet& frames );
//    FrameSet getFrames() const;
//
//    std::size_t getCount() const;
//
//    int getFirst() const;
//    int getLast() const;
//
//    bool operator==( const FrameRange& range ) const {
//        return true;
//    }
//
//private:
//
//    // Frames vector
//    FrameMap m_frames;
//
//};

#endif //STREAKER_RANGE_HH
