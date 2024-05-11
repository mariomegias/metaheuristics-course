#include "../inc/agg.hpp"

const unsigned AGG::N_CHROMOSOMES_SELECT = 50;
const unsigned AGG::N_EXPECTED_CROSSINGS = 17;
const unsigned AGG::N_EXPECTED_MUTATIONS = 4;

AGG::AGG(const string & name, const Data * training, long seed, CrossingType crossing_type)
: AG(name, training, seed, crossing_type)
{
    this->n_chromosomes_select = N_CHROMOSOMES_SELECT;
    this->n_expected_crossings = N_EXPECTED_CROSSINGS;
}

void AGG::mutate(Population & intermediate)
{
    const unsigned TOP_GENES = (num_attributes - 1);
    const unsigned TOP_CHROMOSOMES = (N_CHROMOSOMES_SELECT - 1);

    unsigned mutations_count = 0;
    while (mutations_count < N_EXPECTED_MUTATIONS)
    {
        mutation_operator(intermediate.chromosomes[Random::get<unsigned>(0, TOP_CHROMOSOMES)],
                          Random::get<unsigned>(0, TOP_GENES));
        mutations_count++;
    }
}

void AGG::replace(Population & children)
{
    unsigned pos_best_current = get_pos_best(current_population);
    unsigned pos_best_children = get_pos_best(children);

    if (children.fitness[pos_best_children] < current_population.fitness[pos_best_current])
    {
        unsigned pos_worst_children = get_pos_worst(children);
        children.chromosomes[pos_worst_children] = current_population.chromosomes[pos_best_current];
        children.fitness[pos_worst_children] = current_population.fitness[pos_best_current];
    }

    current_population = children;
}

