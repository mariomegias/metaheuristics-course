#include "../inc/am.hpp"

AM::AM(const string & name, const Data * training, CrossingType crossing_type)
:   AGG(name, training, crossing_type),
    local_search(Local_search(name, training)) {}

void AM::compute_weights()
{
    unsigned num_evaluations = 0;
    unsigned num_generations = 0;
    unsigned max_neighbors_gen = 2 * num_attributes;
    Population aux_population;

    ini_current_population();
    evaluate(current_population, num_evaluations);

    while (num_evaluations < MAX_EVALUATIONS) {
        aux_population = select();
        cross(aux_population);
        mutate(aux_population);
        evaluate(aux_population, num_evaluations);
        if (num_generations % 9 == 0) {
            exploitation(aux_population, num_evaluations, max_neighbors_gen);
        }
        replace(aux_population);
        num_generations++;
    }

    weights = current_population.chromosomes[get_pos_best(current_population)];
}

