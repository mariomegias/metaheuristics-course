#ifndef AM_HPP
#define AM_HPP

#include "agg.hpp"
#include "local_search.hpp"

class AM : public AGG
{
private:
    void compute_weights() override;

protected:
    Local_search local_search;

    virtual void exploitation(Population & population, unsigned & num_evaluations, unsigned max_neighbors_gen) = 0;

public:
    AM(const string & name, const Data * training, CrossingType crossing_type);
};

#endif // ifndef AM_HPP