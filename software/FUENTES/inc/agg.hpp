#ifndef AGG_HPP
#define AGG_HPP

#include "ag.hpp"
#include "blx.hpp"
#include "ca.hpp"
#include "tournament.hpp"

class AGG : public AG
{
private:
    static const double PROB_CROSSING;
    static const unsigned TOURNAMENT_SIZE;
    static const unsigned N_CHROMOSOMES_SELECT;

    Tournament tournament;
    CrossingType crossing_type;
    Crossing * crossing;

protected:
    Population select() override;
    void cross(Population & parents) override;
    void replace(Population & children) override;

public:
    AGG(const string & name, const Data * training, long seed, CrossingType crossing_type);
};


#endif // ifndef AGG_HPP