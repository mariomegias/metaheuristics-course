#include "../inc/age.hpp"

const double AGE::PROB_CROSSING = 1.0;
const unsigned AGE::TOURNAMENT_SIZE = 3;
const unsigned AGE::N_CHROMOSOMES_SELECT = 2;

AGE::AGE(const string & name, const Data * training, long seed, CrossingType crossing_type)
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

Population AGE::select()
{
    vector<vector<double>> chromosomes;
    vector<double> fitness;

    for (int i = 0; i < N_CHROMOSOMES_SELECT; i++) {
        chromosomes.push_back(actual.chromosomes[tournament.get_pos_winner(actual)]);
        fitness.push_back(compute_fitness(*training, chromosomes[i]));
    }

    return {chromosomes, fitness};
}

void AGE::cross(Population & parents)
{
    auto N_EXPECTED_CROSSINGS = (unsigned)(round(PROB_CROSSING * (double)(parents.size()) * 0.5));
    for (unsigned i = 0; i < N_EXPECTED_CROSSINGS; i+=2)
    {
        crossing->cross(parents.chromosomes[i], parents.chromosomes[i+1]);
        parents.fitness[i] = compute_fitness(*training, parents.chromosomes[i]);
        parents.fitness[i+1] = compute_fitness(*training, parents.chromosomes[i+1]);
    }
}

void AGE::get_two_worst_pos(vector<unsigned> worst_positions)
{
    unsigned pos_first_worst = get_pos_worst(actual);

    unsigned pos_second_worst;
    double fitness_second_worst = 100;

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        if (i != pos_first_worst && fitness_second_worst > actual.fitness[i]) {
            pos_second_worst = i;
            fitness_second_worst = actual.fitness[pos_second_worst];
        }
    }

    worst_positions.push_back(pos_first_worst);
    worst_positions.push_back(pos_second_worst);
}

void AGE::replace(Population & children)
{
    vector<unsigned> worst_positions;
    get_two_worst_pos(worst_positions);

    if (actual.fitness[worst_positions[0]] < children.fitness[0])
    {
        actual.chromosomes[worst_positions[0]] = children.chromosomes[0];
        actual.fitness[worst_positions[0]] = children.fitness[0];

        if (actual.fitness[worst_positions[1]] < children.fitness[1])
        {
            actual.chromosomes[worst_positions[1]] = children.chromosomes[1];
            actual.fitness[worst_positions[1]] = children.fitness[1];
        }
    }
    else if (actual.fitness[worst_positions[0]] < children.fitness[1])
    {
        actual.chromosomes[worst_positions[0]] = children.chromosomes[1];
        actual.fitness[worst_positions[0]] = children.fitness[1];

        if (actual.fitness[worst_positions[1]] < children.fitness[0])
        {
            actual.chromosomes[worst_positions[1]] = children.chromosomes[0];
            actual.fitness[worst_positions[1]] = children.fitness[0];
        }
    }
}

