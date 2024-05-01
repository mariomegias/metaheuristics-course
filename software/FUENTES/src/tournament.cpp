#include "../inc/tournament.hpp"

const unsigned Tournament::TOURNAMENT_DEFAULT_SIZE = 3;

Tournament::Tournament()
{
    this->tournament_size = TOURNAMENT_DEFAULT_SIZE;
}

Tournament::Tournament(unsigned tournament_size)
{
    this->tournament_size = tournament_size;
}

unsigned Tournament::get_pos_winner(const Population & population) const
{
    vector<unsigned> positions =
            Random::get<vector>((unsigned)(0), (unsigned)(population.size()-1), tournament_size);

    unsigned pos_winner = positions[0];
    double fitness_winner = population.fitness[pos_winner];

    for (unsigned i = 1; i < tournament_size; i++)
    {
        if (fitness_winner < population.fitness[positions[i]])
        {
            fitness_winner = population.fitness[positions[i]];
            pos_winner = i;
        }
    }

    return pos_winner;
}

