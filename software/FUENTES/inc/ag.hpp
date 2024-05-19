#ifndef AG_HPP
#define AG_HPP

#include "blx.hpp"
#include "ca.hpp"
#include "metaheuristics.hpp"
#include "random.hpp"
#include "tournament.hpp"

using Random = effolkronium::random_static;

class AG : public Metaheuristics
{
private:
    static const double MEAN;
    static const double VARIANCE;

    normal_distribution<double> normal;

protected:
    static const double PROB_MUTATION_CHROMOSOME;
    static const unsigned MAX_EVALUATIONS;
    static const unsigned POPULATION_SIZE;

    Population current_population;
    unsigned n_chromosomes_select;
    unsigned n_expected_crossings;

    CrossingType crossing_type;
    Crossing * crossing;
    Tournament tournament;

    unsigned get_pos_best(const Population & population);
    unsigned get_pos_worst(const Population & population);

    void ini_current_population();
    void mutation_operator(vector<double> & chromosome, unsigned pos_gene);
    void evaluate(Population & population, unsigned & num_evaluations);
    Population select();
    void cross(Population & parents);

    virtual void mutate(Population & intermediate) = 0;
    virtual void replace(Population & children) = 0;

    void compute_weights() override;

public:
    AG(const string & name, const Data * training, CrossingType crossing_type);
};


#endif // ifndef AG_HPP