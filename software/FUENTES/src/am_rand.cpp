#include "../inc/am_rand.hpp"

const double AM_Rand::PROB_SELECT_CHROMOSOME = 0.1;

AM_Rand::AM_Rand(const string & name, const Data * training, long seed, CrossingType crossing_type)
: AM(name, training, seed, crossing_type) {}

void AM_Rand::exploitation(Population &population, unsigned &num_evaluations, unsigned max_neighbors_gen)
{
    unsigned evaluations_limit = MAX_EVALUATIONS - num_evaluations;

    for (unsigned i = 0; (i < POPULATION_SIZE) && (evaluations_limit > 0); i++) {
        if (Random::get(0.0, 1.0) < PROB_SELECT_CHROMOSOME) {
            num_evaluations += local_search.do_local_search(population.chromosomes[i], population.fitness[i], max_neighbors_gen, evaluations_limit);
            evaluations_limit = MAX_EVALUATIONS - num_evaluations;
        }
    }
}

