#include "../inc/blx.hpp"

BLX::BLX(double alpha)
{
    this->alpha = alpha;
}

void BLX::cross(vector<double> & chromosome_1, vector<double> & chromosome_2)
{
    const unsigned N_GENES = chromosome_1.size();
    double c_max, c_min, I;

    for (unsigned j = 0; j < N_GENES; j++)
    {
        c_max = max(chromosome_1[j], chromosome_2[j]);
        c_min = min(chromosome_1[j], chromosome_2[j]);
        I = c_max - c_min;

        chromosome_1[j] = Random::get<double>(c_min - I * alpha, c_max + I * alpha);
        chromosome_2[j] = Random::get<double>(c_min - I * alpha, c_max + I * alpha);
    }
}

