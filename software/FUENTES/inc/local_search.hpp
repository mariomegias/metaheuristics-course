#ifndef LOCAL_SEARCH_HPP
#define LOCAL_SEARCH_HPP

#include "metaheuristics.hpp"
#include "random.hpp"
#include <cmath>

class Local_search : public Metaheuristics
{
private:
    static const double MEAN;
    static const double VARIANCE;
    static const unsigned MAX_EVALUATIONS;

    normal_distribution<double> normal;

    void gen_neighbour(const vector<double> & actual_solution, vector<double> & neighbor, unsigned pos);
    void compute_weights() override;

public:
    Local_search(const string & name, const Data * training, long seed);
    unsigned do_local_search(vector<double> & actual_solution, double & fitness_act_sol, unsigned max_neighbors_gen, unsigned evaluations_limit);
};

#endif // ifndef LOCAL_SEARCH_HPP