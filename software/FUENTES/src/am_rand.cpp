#include "../inc/am_rand.hpp"

AM_Rand::AM_Rand(const string & name, const Data * training, long seed, CrossingType crossing_type)
: AM(name, training, seed, crossing_type) {}

void AM_Rand::exploitation(Population & population)
{
    const unsigned N_EXPLOITATIONS = population.size() * 0.1;

    vector<unsigned> positions =
            Random::get<vector>((unsigned)(0), (unsigned)(population.size()-1), N_EXPLOITATIONS);

    for (unsigned i = 0; i < N_EXPLOITATIONS; i++) {
        local_search.do_search(population.chromosomes[positions[i]]);
        population.fitness[positions[i]] = compute_fitness(*training, population.chromosomes[positions[i]]);
    }
}

