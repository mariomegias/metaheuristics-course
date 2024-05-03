#include "../inc/ca.hpp"

void CA::cross(vector<double> & chromosome_1, vector<double> & chromosome_2)
{
    const double ALPHA = Random::get<double>(0.0, 1.0);
    const double ONE_LESS_ALPHA = 1 - ALPHA;

    const unsigned N_GENES = chromosome_1.size();
    for (unsigned j = 0; j < N_GENES; j++) {
        chromosome_1[j] = ALPHA * chromosome_1[j] + ONE_LESS_ALPHA * chromosome_2[j];
        chromosome_2[j] = ALPHA * chromosome_2[j] + ONE_LESS_ALPHA * chromosome_1[j];
    }
}