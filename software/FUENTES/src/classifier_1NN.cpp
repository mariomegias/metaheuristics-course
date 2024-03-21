#include "../inc/classifier_1NN.hpp"

Classifier_1NN::Classifier_1NN(string name, const Data * training, double fit_parameter)
: Metaheuristics(name, training, fit_parameter) {}

void Classifier_1NN::compute_weights()
{
    weights = vector<double>(num_attributes, 1.0);
}