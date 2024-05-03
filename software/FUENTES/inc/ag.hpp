#ifndef AG_HPP
#define AG_HPP

#include "metaheuristics.hpp"
#include "random.hpp"

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

    unsigned get_pos_best(const Population & population);
    unsigned get_pos_worst(const Population & population);

    void ini_current_population();
    void evaluate(Population & population, unsigned & num_evaluations);

    void mutation_operator(vector<double> & chromosome, unsigned pos_gene);

    virtual Population select() = 0;
    virtual void mutate(Population & intermediate) = 0;
    virtual void cross(Population & parents) = 0;
    virtual void replace(Population & children) = 0;

    void compute_weights() override;

public:
    AG(const string & name, const Data * training, long seed);
};


#endif // ifndef AG_HPP