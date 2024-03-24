#ifndef CLASSIFYING_1NN_HPP
#define CLASSIFYING_1NN_HPP

#include "metaheuristics.hpp"

class Classifier_1NN : public Metaheuristics
{
private:
    void compute_weights() override;

public:
    Classifier_1NN(const string & name, const Data * training);
};

#endif // ifndef CLASSIFYING_1NN_HPP