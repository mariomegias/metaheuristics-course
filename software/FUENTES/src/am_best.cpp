#include "../inc/am_best.hpp"

AM_Best::AM_Best(const string & name, const Data * training, long seed, CrossingType crossing_type)
: AM(name, training, seed, crossing_type) {}

void AM_Best::exploitation(Population &population, unsigned &num_evaluations)
{
    priority_queue<pair<unsigned, double>, vector<pair<unsigned, double>>, Compare_AM> ordering_pos_and_fit;

    const unsigned N_CHROMOSOMES = population.size();
    for (unsigned i = 0; i < N_CHROMOSOMES; i++) {
        ordering_pos_and_fit.emplace(i, population.fitness[i]);
    }

    const auto N_EXPLOITATIONS = (unsigned)(0.1 * (double)(N_CHROMOSOMES));     // OPTIMIZAR ???
    unsigned count_exploitations = 0;

    while (count_exploitations < N_EXPLOITATIONS)
    {
        local_search.do_local_search(population.chromosomes[ordering_pos_and_fit.top().first], num_evaluations, max_neighbors_gen);
        ordering_pos_and_fit.pop();
        count_exploitations++;
    }
}

