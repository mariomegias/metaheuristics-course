#include "../inc/agg.hpp"

const unsigned AGG::N_CHROMOSOMES_SELECT = 50;
const unsigned AGG::TOURNAMENT_SIZE = 3;
const unsigned AGG::N_EXPECTED_CROSSINGS = 17;
const unsigned AGG::N_EXPECTED_MUTATIONS = 4;

AGG::AGG(const string & name, const Data * training, long seed, CrossingType crossing_type)
: AG(name, training, seed)
{
    this->tournament = Tournament(TOURNAMENT_SIZE);
    this->crossing_type = crossing_type;

    switch (crossing_type)
    {
        case CrossingType::BLX:
            crossing = new BLX();
            break;
        case CrossingType::CA:
            crossing = new CA();
            break;
    }
}

Population AGG::select()
{
    unsigned pos_winner = 0;
    vector<vector<double>> chromosomes;
    vector<double> fitness;

    for (unsigned i = 0; i < N_CHROMOSOMES_SELECT; i++) {
        pos_winner = tournament.get_pos_winner(current_population);
        chromosomes.push_back(current_population.chromosomes[pos_winner]);
        fitness.push_back(current_population.fitness[pos_winner]);
    }

    return {chromosomes, fitness};
}

void AGG::cross(Population & parents)
{
    for (unsigned i = 0; i < N_EXPECTED_CROSSINGS; i+=2) {
        crossing->cross(parents.chromosomes[i], parents.chromosomes[i+1]);
    }
}

void AGG::mutate(Population & intermediate)
{
    const unsigned TOP_GENES = (intermediate.n_genes() - 1);
    const unsigned TOP_CHROMOSOMES = (intermediate.size() - 1);

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

