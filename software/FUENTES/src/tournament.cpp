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

unsigned Tournament::get_pos_winner(const Population & population)
{
    const unsigned POS_LAST_CHROMOSOME = (population.size() - 1);

    unsigned pos_winner = Random::get<unsigned>(0, POS_LAST_CHROMOSOME);
    double fitness_winner = population.fitness[pos_winner];

    unsigned pos;

    unsigned count = 1;
    while (count < tournament_size) {
        pos = Random::get<unsigned>(0, POS_LAST_CHROMOSOME);
        if (fitness_winner < population.fitness[pos]) {
            pos_winner = pos;
            fitness_winner = population.fitness[pos];
        }
        count++;
    }

    return pos_winner;
}

