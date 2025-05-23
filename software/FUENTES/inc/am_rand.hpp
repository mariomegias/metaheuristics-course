#ifndef AM_RAND_HPP
#define AM_RAND_HPP

#include "am.hpp"

class AM_Rand : public AM
{
private:
    static const double PROB_SELECT_CHROMOSOME;

    void exploitation(Population &population, unsigned &num_evaluations, unsigned max_neighbors_gen) override;

public:
    AM_Rand(const string & name, const Data * training, CrossingType crossing_type);
};

#endif // ifndef AM_RAND_HPP