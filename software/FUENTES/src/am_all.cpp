#include "../inc/am_all.hpp"

AM_All::AM_All(const string & name, const Data * training, long seed, CrossingType crossing_type)
: AM(name, training, seed, crossing_type) {}

void AM_All::exploitation(Population &population, unsigned &num_evaluations, unsigned max_neighbors_gen)
{
    unsigned evaluations_limit = MAX_EVALUATIONS - num_evaluations;

    for (unsigned i = 0; (i < POPULATION_SIZE) && (evaluations_limit > 0); i++) {
        num_evaluations += local_search.do_search(population.chromosomes[i], population.fitness[i], max_neighbors_gen, evaluations_limit);
        evaluations_limit = MAX_EVALUATIONS - num_evaluations;
    }
}

