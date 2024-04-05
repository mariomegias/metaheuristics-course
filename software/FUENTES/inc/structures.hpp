#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include <chrono>
#include <ctime>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace std::chrono;

enum class Dataset_name {ecoli, parkinsons, breast_cancer};

struct Data
{
    vector<vector<double>> input;
    vector<string> output;
    void clear() {
        input.clear();
        output.clear();
    }
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
    milliseconds time;

    Result() = default;
    Result(const string & name_mh, const Metrics & metrics, const vector<double> & w, const milliseconds & time)
    :   name_mh(name_mh), metrics(metrics.tasa_clas, metrics.tasa_red, metrics.fitness), w(w), time(time) {}
};

#endif // ifndef STRUCTURES_HPP


