#include "../inc/classifier_1NN.hpp"

Classifier_1NN::Classifier_1NN(string name, const Data * training, double fit_parameter)
: Metaheuristics(name, training, fit_parameter) {}

// double Classifier_1NN::distance(const vector<double> &a, const vector<double> &b) const
// {
//     return euclidean_distance(a, b);
// }

void Classifier_1NN::compute_weights()
{
    weights = vector<double>(num_attributes, 1.0);
}