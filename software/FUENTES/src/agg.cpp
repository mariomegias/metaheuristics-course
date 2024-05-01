#include "../inc/agg.hpp"

const double AGG::PROB_CROSSING = 0.68;
const unsigned AGG::TOURNAMENT_SIZE = 3;
const unsigned AGG::N_CHROMOSOMES_SELECT = 50;

AGG::AGG(const string & name, const Data * training, long seed, CrossingType crossing_type)
: AG(name, training, seed)
{
    this->tournament = Tournament(TOURNAMENT_SIZE);
    this->crossing_type = crossing_type;

    switch (crossing_type)
    {
        case CrossingType::BLX:
            crossing = new BLX(0.3);
        break;
        case CrossingType::CA:
            crossing = new CA();
        break;
        default:
            crossing = nullptr;
    }
}

Population AGG::select()
{
    vector<vector<double>> chromosomes;
    vector<double> fitness;

    for (unsigned i = 0; i < N_CHROMOSOMES_SELECT; i++)
    {
        chromosomes.push_back(actual.chromosomes[tournament.get_pos_winner(actual)]);
        fitness.push_back(compute_fitness(*training, chromosomes[i]));
    }

    return {chromosomes, fitness};
}

void AGG::cross(Population & parents)
{
    auto N_EXPECTED_CROSSINGS = (unsigned)(round(PROB_CROSSING * (double)(parents.size()) * 0.5));
    for (unsigned i = 0; i < N_EXPECTED_CROSSINGS; i+=2)
    {
        crossing->cross(parents.chromosomes[i], parents.chromosomes[i+1]);
        parents.fitness[i] = compute_fitness(*training, parents.chromosomes[i]);
        parents.fitness[i+1] = compute_fitness(*training, parents.chromosomes[i+1]);
    }
}

void AGG::replace(Population & children)
{
    unsigned pos_best_actual = get_pos_best(actual);
    unsigned pos_best_children = get_pos_best(children);

    if (children.fitness[pos_best_children] < actual.fitness[pos_best_actual])
    {
        unsigned pos_worst_children = get_pos_worst(children);
        children.chromosomes[pos_worst_children] = actual.chromosomes[pos_best_actual];
        children.fitness[pos_worst_children] = actual.fitness[pos_best_actual];
    }

    actual = children;
}

