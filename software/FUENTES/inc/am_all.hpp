#ifndef AM_ALL_HPP
#define AM_ALL_HPP

#include "am.hpp"

class AM_All : public AM
{
private:
    void exploitation(Population & population) override;

public:
    AM_All(const string & name, const Data * training, long seed, CrossingType crossing_type);
};

#endif // ifndef AM_ALL_HPP