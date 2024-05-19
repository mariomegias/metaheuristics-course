#ifndef ILS_HPP
#define ILS_HPP

#include "local_search.hpp"
#include "es.hpp"
#include "metaheuristics.hpp"
#include "random.hpp"

using Random = effolkronium::random_static;

class ILS : public Metaheuristics
{
private:
    static const unsigned MAX_EVALUATIONS;
    static const unsigned MAX_ITERATIONS;

    NeighborhoodSearchType neighborhood_search_type;
    Neighborhood_search * neighborhood_search;

    vector<double> mutation_operator(const vector<double> & best_sol, unsigned n_attributes_to_change);
    void compute_weights() override;

public:
    ILS(const string & name, const Data * training, NeighborhoodSearchType type);
};

#endif // ifndef ILS_HPP
