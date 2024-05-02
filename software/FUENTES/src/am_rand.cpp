#include "../inc/am_rand.hpp"

AM_Rand::AM_Rand(const string & name, const Data * training, long seed, CrossingType crossing_type)
: AM(name, training, seed, crossing_type) {}

void AM_Rand::exploitation(Population & population)
{
//    const unsigned N_EXPLOITATIONS = population.size();
//    for (unsigned i = 0; i < N_EXPLOITATIONS; i++) {
//        local_search.do_search(population.chromosomes[i]);
//        population.fitness[i] = compute_fitness(*training, population.chromosomes[i]);
//    }
}

