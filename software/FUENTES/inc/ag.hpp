#ifndef AG_HPP
#define AG_HPP

#include "metaheuristics.hpp"
#include "random.hpp"

using Random = effolkronium::random_static;


class AG : public Metaheuristics
{
private:
    static const double PROB_MUTATION_CHROMOSOME;
    static const double MEAN;
    static const double VARIANCE;
    static const double MAX_EVALUATIONS;

    double prob_mutation_gen;
    normal_distribution<double> normal;

    void ini_population();
    void mutation_operator(vector<double> & chromosome, unsigned pos_gene);
    void mutate(Population & intermediate);

    virtual Population select() = 0;
    virtual void cross(Population & parents) = 0;
    virtual void replace(Population & children) = 0;

    void compute_weights() override;

protected:
    static const unsigned POPULATION_SIZE;
    Population actual;

    unsigned get_pos_best(const Population & population);
    unsigned get_pos_worst(const Population & population);

public:
    AG(const string & name, const Data * training, long seed);
};


#endif // ifndef AG_HPP