#ifndef METAHEURISTICS_HPP
#define METAHEURISTICS_HPP

#include "structures.hpp"
#include <cfloat>
#include <cmath>

class Metaheuristics 
{
protected:
    string name;
    const Data * training;
    unsigned int num_attributes;
    vector<double> weights;
    bool trained;
    milliseconds training_time;

    static const double FIT_PARAMETER;
    static const double W_THRESHOLD;

    virtual void compute_weights() = 0;
    double compute_fitness(const Data & data, const vector<double> & w, Metrics & metrics);
    
public:
    Metaheuristics(const string & name, const Data * training);
    Result train();
    Result test(const Data & testing);

private:
    string classify(const vector<double> & example, const vector<double> & w) const;
    double distance(const vector<double> & a, const vector<double> & b, const vector<double> & w) const;
    double compute_tasa_red(const vector<double> & w) const;
    double compute_tasa_clas(const Data & data, const vector<double> & w);
};

#endif // ifndef METAHEURISTICS_HPP