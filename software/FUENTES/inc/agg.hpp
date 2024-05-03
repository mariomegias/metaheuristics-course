#ifndef AGG_HPP
#define AGG_HPP

#include "ag.hpp"
#include "blx.hpp"
#include "ca.hpp"
#include "tournament.hpp"

class AGG : public AG
{
private:
    static const unsigned N_CHROMOSOMES_SELECT;
    static const unsigned TOURNAMENT_SIZE;
    static const unsigned N_EXPECTED_CROSSINGS;
    static const unsigned N_EXPECTED_MUTATIONS;

    CrossingType crossing_type;
    Crossing * crossing;
    Tournament tournament;

protected:
    Population select() override;
    void mutate(Population & intermediate) override;
    void cross(Population & parents) override;
    void replace(Population & children) override;

public:
    AGG(const string & name, const Data * training, long seed, CrossingType crossing_type);
};


#endif // ifndef AGG_HPP