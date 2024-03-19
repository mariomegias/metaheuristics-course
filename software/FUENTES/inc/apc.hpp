#ifndef APC_HPP
#define APC_HPP

#include "arff_file.hpp"
#include "classifier_1NN.hpp"
#include "data.hpp"
#include "greedy_relief.hpp"
#include "local_search.hpp"

//class APC
//{
//private:
//    vector<Data> training_partitions;
//    vector<Data> testing_partitions;
//    vector<vector<Metaheuristics * >> mh;
//    vector<vector<Result>> train_results;
//    vector<vector<Result>> test_results;
//
//    long seed;
//    bool trained;
//
//    static const double FIT_PARAMETER;
//
//    void normalize_input(vector<vector<double>> & input);
//    void add_metaheuristics();
//
//public:
//    APC(const vector<string> & file_names, long seed);
//    void train();
//    void test();
//    void get_train_results(vector<vector<Result>> & train_results);
//    void get_test_results(vector<vector<Result>> & test_results);
//};

class APC
{
private:
    Data training;
    Data testing;
    vector<Metaheuristics * > mh;
    vector<Result> train_results;
    vector<Result> test_results;
    long seed;
    bool trained;

    static const double FIT_PARAMETER;

    void normalize_input(vector<vector<double>> & input);
    void add_metaheuristics();

public:
    APC(const vector<string> & file_names, int pos_test, long seed);
    void train();
    void test();
    void get_train_results(vector<Result> & train_results);
    void get_test_results(vector<Result> & test_results);
};

#endif // ifndef APC_HPP