#ifndef AGG_HPP
#define AGG_HPP

#include "../inc/ag.hpp"

class AGG : public AG
{
private:

    static const double PROB_CROSSING;

    vector<vector<double>> select() override;
    void cross(vector<vector<double>> & parents_population) override;
    void replace(vector<vector<double>> & children_population) override;

public:
    AGG(const string & name, const Data * training, long seed);
};


#endif // ifndef AGG_HPP