#ifndef AGE_HPP
#define AGE_HPP

#include "ag.hpp"
#include "blx.hpp"
#include "ca.hpp"
#include "tournament.hpp"
#include <queue>
#include <utility>

class Compare_AGE
{
public:
    bool operator() (const pair<vector<double>, double> & lhs, const pair<vector<double>, double> & rhs) const {
        return lhs.second < rhs.second;
    }
};

class AGE : public AG
{
private:
    static const unsigned N_CHROMOSOMES_SELECT;
    static const unsigned TOURNAMENT_SIZE;

    CrossingType crossing_type;
    Crossing * crossing;
    Tournament tournament;

    void get_two_worst_pos(vector<unsigned> & worst_positions);

protected:
    Population select() override;
    void mutate(Population & intermediate) override;
    void cross(Population & parents) override;
    void replace(Population & children) override;

public:
    AGE(const string & name, const Data * training, long seed, CrossingType crossing_type);
};


#endif // ifndef AGE_HPP