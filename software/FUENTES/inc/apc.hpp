#ifndef APC_HPP
#define APC_HPP

#include "age.hpp"
#include "agg.hpp"
#include "am_all.hpp"
#include "am_best.hpp"
#include "am_rand.hpp"
#include "arff_file.hpp"
#include "classifier_1NN.hpp"
#include "structures.hpp"
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

    void normalize(vector<Data> & data);
    void add_metaheuristics();
    void process_partition(const vector<Data> & data, int pos_test, Data & training, Data & testing);

public:
    APC(const vector<string> & file_names, long seed);
    void train();
    void test();
    void get_train_results(vector<vector<Result>> & train_results);
    void get_test_results(vector<vector<Result>> & test_results);
};

#endif // ifndef APC_HPP