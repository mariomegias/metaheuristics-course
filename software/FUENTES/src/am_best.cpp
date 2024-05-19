#include "../inc/am_best.hpp"

const unsigned AM_Best::N_EXPLOITATIONS = 5;

AM_Best::AM_Best(const string & name, const Data * training, long seed, CrossingType crossing_type)
: AM(name, training, seed, crossing_type) {}

void AM_Best::exploitation(Population &population, unsigned &num_evaluations, unsigned max_neighbors_gen)
{
    priority_queue<pair<unsigned, double>, vector<pair<unsigned, double>>, Compare_AM> ordering_pos_by_fit;

    for (unsigned i = 0; i < POPULATION_SIZE; i++) {
        ordering_pos_by_fit.emplace(i, population.fitness[i]);
    }

    unsigned evaluations_limit = MAX_EVALUATIONS - num_evaluations;
    unsigned position = ordering_pos_by_fit.top().first;
    unsigned count_exploitations = 0;

    while ((count_exploitations < N_EXPLOITATIONS) && (evaluations_limit > 0))
    {
        num_evaluations += local_search.do_search(population.chromosomes[position], population.fitness[position],max_neighbors_gen, evaluations_limit);
        ordering_pos_by_fit.pop();
        evaluations_limit = MAX_EVALUATIONS - num_evaluations;
        position = ordering_pos_by_fit.top().first;
        count_exploitations++;
    }
}

