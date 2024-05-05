#include "../inc/ca.hpp"

void CA::cross(vector<double> & chromosome_1, vector<double> & chromosome_2)
{
    const double ALPHA = Random::get<double>(0.0, 1.0);
    const double ONE_LESS_ALPHA = 1 - ALPHA;

    vector<double> child_1, child_2;

    const unsigned N_GENES = chromosome_1.size();
    for (unsigned j = 0; j < N_GENES; j++) {
        child_1.push_back(ALPHA * chromosome_1[j] + ONE_LESS_ALPHA * chromosome_2[j]);
        child_2.push_back(ALPHA * chromosome_2[j] + ONE_LESS_ALPHA * chromosome_1[j]);
    }

    chromosome_1 = child_1;
    chromosome_2 = child_2;
}