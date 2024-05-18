#ifndef ES_HPP
#define ES_HPP

#include "metaheuristics.hpp"
#include "random.hpp"
#include <cmath>

using Random = effolkronium::random_static;

class ES : public Metaheuristics
{
private:
    static const unsigned MAX_EVALUATIONS;
    static const double MEAN;
    static const double VARIANCE;
    static const double PHI;
    static const double MU;
    static const double FIN_TEMP;

    normal_distribution<double> normal;

    void gen_neighbour(const vector<double> & act_sol, vector<double> & neighbor, unsigned pos);
    void compute_weights() override;

public:
    ES(const string & name, const Data * training, long seed);
};

#endif // ifndef ES_HPP
