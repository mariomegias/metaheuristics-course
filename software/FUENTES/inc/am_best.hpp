#ifndef AM_BEST_HPP
#define AM_BEST_HPP

#include "am.hpp"
#include <queue>
#include <utility>

class Compare_AM
{
public:
    bool operator() (const pair<unsigned, double> & lhs, const pair<unsigned, double> & rhs) const {
        return lhs.second < rhs.second;
    }
};

class AM_Best : public AM
{
private:
    void exploitation(Population &population, unsigned &num_evaluations) override;

public:
    AM_Best(const string & name, const Data * training, long seed, CrossingType crossing_type);
};

#endif // ifndef AM_BEST_HPP
