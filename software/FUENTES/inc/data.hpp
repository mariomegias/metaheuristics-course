#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <vector>

using namespace std;

// Crear un enumerado para los nombres de los algoritmos

struct Data
{
    vector<vector<double>> input;
    vector<string> output;
};

struct Metrics
{
    double tasa_clas;
    double tasa_red;
    double fitness;
    Metrics() = default;
    Metrics(double tasa_clas, double tasa_red, double fitness)
    :  tasa_clas(tasa_clas), tasa_red(tasa_red), fitness(fitness) {}
};

struct Result 
{
    Metrics metrics;
    vector<double> w;
    Result() = default;
    Result(const Metrics & metrics, const vector<double> & w)
    :  metrics(metrics.tasa_clas, metrics.tasa_red, metrics.fitness), w(w) {}
};

#endif // ifndef DATA_HPP


