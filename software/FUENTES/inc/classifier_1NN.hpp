#ifndef CLASSIFYING_1NN_HPP
#define CLASSIFYING_1NN_HPP

#include "metaheuristics.hpp"

class Classifier_1NN : public Metaheuristics
{
private:
    void compute_weights();
    // double Classifying_1NN::distance(const vector<double> &a, const vector<double> &b) const

public:
    Classifier_1NN(string name, const Data * training, double fit_parameter);
};

#endif // ifndef CLASSIFYING_1NN_HPP