#ifndef LOCAL_SEARCH_HPP
#define LOCAL_SEARCH_HPP

#include "metaheuristics.hpp"
#include "neighborhood_search.hpp"
#include "random.hpp"
#include <cmath>

class Local_search : public Metaheuristics, public Neighborhood_search
{
private:
    static const double MEAN;
    static const double VARIANCE;
    static const unsigned MAX_EVALUATIONS;

    normal_distribution<double> normal;

    void gen_neighbour(const vector<double> & actual_solution, vector<double> & neighbor, unsigned pos);
    void compute_weights() override;

public:
    Local_search(const string & name, const Data * training);
    unsigned do_search(vector<double> & act_sol, double & fitness_act_sol, unsigned max_neighbors, unsigned eval_limit) override;
};

#endif // ifndef LOCAL_SEARCH_HPP