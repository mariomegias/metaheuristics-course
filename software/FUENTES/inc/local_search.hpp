#ifndef LOCAL_SEARCH_HPP
#define LOCAL_SEARCH_HPP

#include "metaheuristics.hpp"
#include "random.hpp"

class Local_search : public Metaheuristics
{
private:
    static const double MEAN;
    static const double VARIANCE;
    static const double MAX_EVALUATIONS;

    unsigned max_neighbors_to_generate;

    void gen_neighbour(const vector<double> & actual_solution, vector<double> & neighbour, unsigned int pos, normal_distribution<double> & normal) const;
    void compute_weights() override;

public:
    Local_search(const string & name, const Data * training, long seed);
    void do_local_search(vector<double> & actual_solution, unsigned & num_evaluations, unsigned max_neighbors_gen);
};

#endif // ifndef LOCAL_SEARCH_HPP