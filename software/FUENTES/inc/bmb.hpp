#ifndef BMB_HPP
#define BMB_HPP

#include "local_search.hpp"
#include "metaheuristics.hpp"
#include "random.hpp"

using Random = effolkronium::random_static;

class BMB : public Metaheuristics
{
private:
    static const unsigned MAX_EVALUATIONS_LS;
    static const unsigned MAX_ITERATIONS;
    Local_search local_search;

    void compute_weights() override;

public:
    BMB(const string & name, const Data * training, long seed);
};

#endif // ifndef BMB_HPP
