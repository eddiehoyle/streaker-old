#ifndef STREAKER_RANGE_HH
#define STREAKER_RANGE_HH

#include <vector>
#include <algorithm>
#include <set>
#include <map>

#include <streaker/Padding.hh>

namespace streaker {

typedef std::set< unsigned int > FrameSet;

class FrameRange {

    /// Represents a range of numbers that share a padding fill value
    /// 1, 2, 3 ... 1001, 1002
    /// 001, 002, 003 ... 1001, 1002

    /// Ranges will need to support skipping
    /// "1-3,5-11x2,14,1001"

public:

    // TODO
    FrameRange();
    ~FrameRange();
    explicit FrameRange( unsigned int first, unsigned int last );

    void addFrame( unsigned int frame );
    void addFrames( const FrameSet& frames );
    void setFrames( const FrameSet& frames );

    /// TODO:
    /// Make this a const ref?
    FrameSet frames() const;

    std::size_t getCount() const;

    unsigned int getFirst() const;
    unsigned int getLast() const;

    bool operator==( const FrameRange& rhs ) const;

private:

    FrameSet m_frames;

};

} // namespace streaker

#endif // STREAKER_RANGE_HH
