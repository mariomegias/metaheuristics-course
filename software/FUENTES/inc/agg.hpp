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
    static const unsigned N_EXPECTED_CROSSINGS;
    static const unsigned N_EXPECTED_MUTATIONS;

protected:
    void mutate(Population & intermediate) override;
    void replace(Population & children) override;

public:
    AGG(const string & name, const Data * training, long seed, CrossingType crossing_type);
};


#endif // ifndef AGG_HPP