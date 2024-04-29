#include "../inc/crossing.hpp"

Crossing::Crossing(int probability)
{
    this->crossing_prob = probability;
}

void Crossing::BLX(vector<vector<double>> & population) const   // PASAR EL ALFA COMO PARAMETRO
{
    const double ALPHA = 0.3;

    const unsigned POPULATION_SIZE = population.size();
    const unsigned N_GENES = population[0].size();

    const auto N_EXPECTED_CROSSINGS = (unsigned)(round(crossing_prob * (POPULATION_SIZE)/2));

    vector<double> child_one, child_two;
    double c_max, c_min, I;

    for (unsigned i = 0; i < N_EXPECTED_CROSSINGS; i+=2) {

        for (unsigned j = 0; j < N_GENES; j++) {

            c_max = max(population[i][j], population[i+1][j]);
            c_min = max(population[i][j], population[i+1][j]);
            I = c_max - c_min;

            child_one.push_back(Random::get<double>(c_min - I * ALPHA, c_max + I * ALPHA));
            child_two.push_back(Random::get<double>(c_min - I * ALPHA, c_max + I * ALPHA));
        }

        population[i] = child_one;
        population[i+1] = child_two;

        child_one.clear();
        child_two.clear();
    }
}

void Crossing::CA(vector<vector<double>> & population)
{
    const double ALPHA = Random::get<double>(0.0, 1.0);
    const double ONE_LESS_ALPHA = 1.0 - ALPHA;

    const unsigned POPULATION_SIZE = population.size();
    const unsigned N_GENES = population[0].size();

    const auto N_EXPECTED_CROSSINGS = (unsigned)(round(crossing_prob * (POPULATION_SIZE)/2));

    vector<double> child_one, child_two;

    for (unsigned i = 0; i < N_EXPECTED_CROSSINGS; i+=2) {

        for (unsigned j = 0; j < N_GENES; j++) {
            child_one.push_back( ALPHA * population[i][j] + ONE_LESS_ALPHA * population[i+1][j] );
            child_two.push_back( ALPHA * population[i+1][j] + ONE_LESS_ALPHA * population[i][j] );
        }

        population[i] = child_one;
        population[i+1] = child_two;

        child_one.clear();
        child_two.clear();
    }
}

