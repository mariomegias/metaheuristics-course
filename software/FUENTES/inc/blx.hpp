#ifndef BLX_HPP
#define BLX_HPP

#include "crossing.hpp"
#include "random.hpp"
#include <cmath>

using Random = effolkronium::random_static;

class BLX : public Crossing
{
private:
    double alpha;

public:
    BLX(double alpha);
    void cross(vector<double> & chromosome_1, vector<double> & chromosome_2) override;
};

#endif // ifndef BLX_HPP