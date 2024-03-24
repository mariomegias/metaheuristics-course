#include "../inc/classifier_1NN.hpp"

Classifier_1NN::Classifier_1NN(const string & name, const Data * training)
: Metaheuristics(name, training) {}

void Classifier_1NN::compute_weights()
{
    weights = vector<double>(num_attributes, 1.0);
}