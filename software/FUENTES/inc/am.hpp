#ifndef AM_HPP
#define AM_HPP

#include "agg.hpp"
#include "local_search.hpp"

class AM : public AGG
{
private:
    void evaluate(Population & population, unsigned & num_evaluations) override;
    void compute_weights() override;

protected:
    unsigned max_neighbors_gen;
    Local_search local_search;
    vector<bool> evaluated_by_ls;

    virtual void exploitation(Population &population, unsigned &num_evaluations) = 0;

public:
    AM(const string & name, const Data * training, long seed, CrossingType crossing_type);
};

#endif // ifndef AM_HPP