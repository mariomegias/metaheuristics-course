#include "../inc/am_best.hpp"

AM_Best::AM_Best(const string & name, const Data * training, long seed, CrossingType crossing_type)
: AM(name, training, seed, crossing_type) {}

void AM_Best::exploitation(Population & population)
{
    priority_queue<pair<unsigned, double>, vector<pair<unsigned, double>>, Compare> ordering_pos_and_fit;

    for (unsigned i = 0; i < population.size(); i++) {
        ordering_pos_and_fit.emplace(i, population.fitness[i]);
    }

    const auto N_EXPLOITATIONS = (unsigned)(0.1 * (double)(population.size()));
    unsigned count_exploitations = 0;
    unsigned pos;

    while (count_exploitations < N_EXPLOITATIONS)
    {
        pos = ordering_pos_and_fit.top().first;
        ordering_pos_and_fit.pop();
        local_search.do_search(population.chromosomes[pos]);
        population.fitness[pos] = compute_fitness(*training, population.chromosomes[pos]);
        count_exploitations++;
    }
}

