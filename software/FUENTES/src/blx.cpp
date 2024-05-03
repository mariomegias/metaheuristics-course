#include "../inc/blx.hpp"

const double BLX::DEFAULT_ALPHA = 0.3;

BLX::BLX()
{
    this->alpha = DEFAULT_ALPHA;
}

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

        if (chromosome_1[j] < 0.0) {
            chromosome_1[j] = 0.0;
        } else if (chromosome_1[j] > 1.0) {
            chromosome_1[j] = 1.0;
        }

        if (chromosome_2[j] < 0.0) {
            chromosome_2[j] = 0.0;
        } else if (chromosome_2[j] > 1.0) {
            chromosome_2[j] = 1.0;
        }
    }
}

