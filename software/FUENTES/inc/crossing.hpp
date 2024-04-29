#ifndef CROSSING_HPP
#define CROSSING_HPP

#include "random.hpp"
#include <cmath>
#include <vector>

using namespace std;
using Random = effolkronium::random_static;

class Crossing
{
private:
    int crossing_prob;

public:
    Crossing(int probability);
    void BLX(vector<vector<double>> & population) const; // PASAR EL ALFA COMO PARAMETRO
    void CA(vector<vector<double>> & population);
};

#endif // ifndef CROSSING_HPP
