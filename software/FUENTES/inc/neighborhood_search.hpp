#ifndef NEIGHBORHOOD_SEARCH_HPP
#define NEIGHBORHOOD_SEARCH_HPP

#include <vector>

using namespace std;

class Neighborhood_search
{
public:
    virtual unsigned do_search(vector<double> & act_sol, double & fitness_act_sol, unsigned max_neighbors, unsigned eval_limit) = 0;
};

#endif // ifndef NEIGHBORHOOD_SEARCH_HPP
