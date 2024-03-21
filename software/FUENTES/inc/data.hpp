#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <utility>
#include <vector>

using namespace std;

enum class Dataset_name {ecoli, parkinsons, breast_cancer};

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
    string name_mh;
    Metrics metrics;
    vector<double> w;
    Result() = default;
    Result(const string & name_mh, const Metrics & metrics, const vector<double> & w)
    :  name_mh(name_mh), metrics(metrics.tasa_clas, metrics.tasa_red, metrics.fitness), w(w) {}
};

#endif // ifndef DATA_HPP


