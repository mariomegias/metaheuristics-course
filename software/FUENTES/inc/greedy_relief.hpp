#ifndef GREEDY_RELIEF_HPP
#define GREEDY_RELIEF_HPP

#include "metaheuristics.hpp"

class Greedy_relief : public Metaheuristics
{
private:
    double euclidean_distance(const vector<double> & a, const vector<double> & b) const;
    void compute_nearest_friend(const vector<double> & example, const string & target, vector<double> & nearest_enemy);
    void compute_nearest_enemy(const vector<double> & example, const string & target, vector<double> & nearest_friend);
    void compute_weights();

public:
    Greedy_relief(string name, const Data * training, double fit_parameter);
};

#endif // ifndef GREEDY_RELIEF_HPP