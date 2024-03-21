#ifndef APC_HPP
#define APC_HPP

#include "arff_file.hpp"
#include "classifier_1NN.hpp"
#include "data.hpp"
#include "greedy_relief.hpp"
#include "local_search.hpp"

class APC
{
private:
    vector<Data> training_sets;
    vector<Data> testing_sets;
    vector<vector<Metaheuristics * >> mh;
    vector<vector<Result>> train_results;
    vector<vector<Result>> test_results;

    unsigned int num_sets;
    unsigned int num_mh;

    long seed;
    bool trained;

    static const double FIT_PARAMETER;

    void normalize_input(vector<vector<double>> & input);
    void add_metaheuristics();
    void process_partition(const vector<string> & file_names, int pos_test, Data & training, Data & testing);

public:
    APC(const vector<string> & file_names, long seed);
    void train();
    void test();
    void get_train_results(vector<vector<Result>> & train_results);
    void get_test_results(vector<vector<Result>> & test_results);
};

#endif // ifndef APC_HPP