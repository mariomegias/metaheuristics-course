#include "../inc/am_best.hpp"

const unsigned AM_Best::N_EXPLOITATIONS = 5;

AM_Best::AM_Best(const string & name, const Data * training, long seed, CrossingType crossing_type)
: AM(name, training, seed, crossing_type) {}

void AM_Best::exploitation(Population &population, unsigned &num_evaluations)
{
    priority_queue<pair<unsigned, double>, vector<pair<unsigned, double>>, Compare_AM> ordering_pos_by_fit;

    for (unsigned i = 0; i < POPULATION_SIZE; i++) {
        ordering_pos_by_fit.emplace(i, population.fitness[i]);
    }

    unsigned count = 0;
    while (count < N_EXPLOITATIONS) {
        local_search.do_local_search(population.chromosomes[ordering_pos_by_fit.top().first], num_evaluations, max_neighbors_gen);
        ordering_pos_by_fit.pop();
        count++;
    }
}

