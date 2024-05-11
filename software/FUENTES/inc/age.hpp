#ifndef AGE_HPP
#define AGE_HPP

#include "ag.hpp"
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
    static const unsigned N_EXPECTED_CROSSINGS;

    void get_two_worst_pos(vector<unsigned> & worst_positions);

protected:
    void mutate(Population & intermediate) override;
    void replace(Population & children) override;

public:
    AGE(const string & name, const Data * training, long seed, CrossingType crossing_type);
};


#endif // ifndef AGE_HPP