#ifndef CLASSIFIER_1NN_HPP
#define CLASSIFIER_1NN_HPP

#include "metaheuristics.hpp"

class Classifier_1NN : public Metaheuristics
{
private:
    void compute_weights() override;

public:
    Classifier_1NN(const string & name, const Data * training);
};

#endif // ifndef CLASSIFIER_1NN_HPP