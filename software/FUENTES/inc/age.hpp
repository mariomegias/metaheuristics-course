#ifndef AGE_HPP
#define AGE_HPP

#include "../inc/ag.hpp"

class AGE : public AG
{
private:

    static const double PROB_CROSSING;

    vector<vector<double>> select() override;
    void cross(vector<vector<double>> & parents_population) override;
    void replace(vector<vector<double>> & children_population) override;

public:
    AGE(const string & name, const Data * training, long seed);
};


#endif // ifndef AGE_HPP