#ifndef CA_HPP
#define CA_HPP

#include "crossing.hpp"
#include "random.hpp"

using Random = effolkronium::random_static;

class CA : public Crossing
{
public:
    void cross(vector<double> & chromosome_1, vector<double> & chromosome_2) override;
};

#endif // ifndef CA_HPP