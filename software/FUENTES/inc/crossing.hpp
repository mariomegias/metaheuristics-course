#ifndef CROSSING_HPP
#define CROSSING_HPP

#include <vector>

using namespace std;

class Crossing
{
public:
    virtual void cross(vector<double> & chromosome_1, vector<double> & chromosome_2) = 0;
};

#endif // ifndef CROSSING_HPP
