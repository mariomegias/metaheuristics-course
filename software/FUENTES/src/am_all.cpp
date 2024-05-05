#include "../inc/am_all.hpp"

AM_All::AM_All(const string & name, const Data * training, long seed, CrossingType crossing_type)
: AM(name, training, seed, crossing_type) {}

void AM_All::exploitation(Population &population, unsigned &num_evaluations)
{
    for (unsigned i = 0; i < POPULATION_SIZE; i++) {
        local_search.do_local_search(population.chromosomes[i], population.fitness[i], num_evaluations, max_neighbors_gen);
        evaluated_by_ls[i] = true;
    }
}

