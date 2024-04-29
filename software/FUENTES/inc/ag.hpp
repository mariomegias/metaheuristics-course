#ifndef AG_HPP
#define AG_HPP

#include "crossing.hpp"
#include "metaheuristics.hpp"
#include "random.hpp"

using Random = effolkronium::random_static;


//struct Population
//{
//    vector<vector<double>> chromosomes;
//    vector
//};


class AG : public Metaheuristics
{
private:
    static const int POPULATION_SIZE;
    static const double PROB_MUTATION_CHROMOSOME;

    static const double MEAN;
    static const double VARIANCE;
    static const double MAX_EVALUATIONS;

    double prob_mutation_gen;
    vector<vector<double>> population;

    normal_distribution<double> normal;

    void ini_population();
    void mutation(vector<double> & chromosome, unsigned gene);
    virtual vector<vector<double>> select() = 0;
    void mutate(vector<vector<double>> & intermediate_population);
    virtual void cross(vector<vector<double>> & parents_population) = 0;
    virtual void replace(vector<vector<double>> & children_population) = 0;
    void compute_weights() override;

public:
    AG(const string & name, const Data * training, long seed);
};


#endif // ifndef AG_HPP