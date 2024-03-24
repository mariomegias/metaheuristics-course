#ifndef LOCAL_SEARCH_HPP
#define LOCAL_SEARCH_HPP

#include "../inc/metaheuristics.hpp"
#include "../inc/random.hpp"

class Local_search : public Metaheuristics
{
private:
    static const double MEAN;
    static const double VARIANCE;
    static const double MAX_EVALUATIONS;

    void gen_neighbour(const vector<double> & actual_sol, vector<double> & neighbour, int pos, normal_distribution<double> & distribution) const;
    void compute_weights() override;

public:
    Local_search(const string & name, const Data * training, long seed);
};

#endif // ifndef LOCAL_SEARCH_HPP