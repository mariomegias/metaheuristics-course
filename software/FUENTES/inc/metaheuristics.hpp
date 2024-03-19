#ifndef METAHEURISTICS_HPP
#define METAHEURISTICS_HPP

#include "data.hpp"
#include <cfloat>
#include <cmath>
#include <vector>

class Metaheuristics 
{
protected:
    string name;
    double fit_parameter;
    const Data * training;
    unsigned int num_attributes;
    vector<double> weights;
    double tasa_red;
    bool trained;

    virtual void compute_weights() = 0;
    Metrics compute_fitness(const Data & data, const vector<double> & w);
    
public:
    Metaheuristics(string name, const Data * training, double fit_parameter);
    Result train();
    Result test(const Data & testing);


private:
    string classify(const vector<double> & example, const vector<double> & w) const;
    double distance(const vector<double> & a, const vector<double> & b, const vector<double> & w) const;
    double compute_tasa_red(const vector<double> & w) const;
    double compute_tasa_clas(const Data & data, const vector<double> & w);
};

#endif // ifndef METAHEURISTICS_HPP