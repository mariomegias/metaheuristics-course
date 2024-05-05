#include "../inc/am.hpp"

AM::AM(const string & name, const Data * training, long seed, CrossingType crossing_type)
:   AGG(name, training, seed, crossing_type),
    local_search(Local_search(name, training, seed))
{
    this->max_neighbors_gen = 2 * num_attributes;
}

void AM::compute_weights()
{
    unsigned num_evaluations = 0;
    unsigned num_generations = 0;
    Population aux_population;

    ini_current_population();
    evaluate(current_population, num_evaluations);

    while (num_evaluations < MAX_EVALUATIONS) {
        aux_population = select();
        cross(aux_population);
        mutate(aux_population);
        if (num_generations % 9 == 0) {
            exploitation(aux_population, num_evaluations);
        }
        evaluate(aux_population, num_evaluations);
        replace(aux_population);
        num_generations++;
    }

    weights = current_population.chromosomes[get_pos_best(current_population)];
}

