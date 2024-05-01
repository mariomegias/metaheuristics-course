#ifndef TOURNAMENT_HPP
#define TOURNAMENT_HPP

#include "random.hpp"
#include "structures.hpp"

using Random = effolkronium::random_static;


class Tournament
{
private:
    static const unsigned TOURNAMENT_DEFAULT_SIZE;
    unsigned tournament_size;

public:
    Tournament();
    explicit Tournament(unsigned tournament_size);
    unsigned get_pos_winner(const Population & population) const;
};


#endif // ifndef TOURNAMENT_HPP