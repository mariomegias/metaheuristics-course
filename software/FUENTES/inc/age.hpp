#ifndef AGE_HPP
#define AGE_HPP

#include "ag.hpp"
#include "blx.hpp"
#include "ca.hpp"
#include "tournament.hpp"

class AGE : public AG
{
private:
    static const double PROB_CROSSING;
    static const unsigned TOURNAMENT_SIZE;
    static const unsigned N_CHROMOSOMES_SELECT;

    Tournament tournament;
    CrossingType crossing_type;
    Crossing * crossing;

    void get_two_worst_pos(vector<unsigned> worst_positions);

    Population select() override;
    void cross(Population & parents) override;
    void replace(Population & children) override;

public:
    AGE(const string & name, const Data * training, long seed, CrossingType crossing_type);
};


#endif // ifndef AGE_HPP