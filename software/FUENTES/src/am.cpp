#include "../inc/am.hpp"

AM::AM(const string & name, const Data * training, long seed, CrossingType crossing_type)
: AGG(name, training, seed, crossing_type), local_search(Local_search(name, training, seed))
{}

void AM::compute_weights()
{
    unsigned count_n_generations = 0;

    ini_population();

    Population aux_population;
    for (unsigned int i = 0; i < MAX_EVALUATIONS; i++)
    {
        if (count_n_generations % 10 == 0) {
            exploitation(aux_population);
        } else {
            aux_population = select();
            cross(aux_population);
            mutate(aux_population);
            replace(aux_population);
        }

        count_n_generations++;
    }

    weights = actual.chromosomes[get_pos_best(actual)];
}