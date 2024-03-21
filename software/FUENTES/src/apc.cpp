#include "../inc/apc.hpp"

const double APC::FIT_PARAMETER = 0.75;

APC::APC(const vector<string> & file_names, long seed)
{
    this->seed = seed;
    trained = false;
    Data training;
    Data testing;
    unsigned int num_files = file_names.size();
    for (int i = 0; i < num_files; i++) {
        process_partition(file_names, i, training, testing);
        training_sets.push_back(training);
        testing_sets.push_back(testing);
        training.input.clear();
        training.output.clear();
        testing.output.clear();
        testing.output.clear();
    }
    add_metaheuristics();
    // num_sets = 1;
    num_sets = training_sets.size();
    num_mh = mh[0].size();
}

void APC::normalize_input(vector<vector<double>> & input)
{
    vector<double> max(input[0]);
    vector<double> min(input[0]);
    unsigned int num_records = input.size();
    unsigned int num_attributes = input[0].size();

    for (int j = 0; j < num_attributes; j++) {
        for (int i = 1; i < num_records; i++) {
            if (input[i][j] > max[j]) {
                max[j] = input[i][j];
            }
            if (input[i][j] < min[j]) {
                min[j] = input[i][j];
            }
        }
    }

    double quot = 1.0;
    for (int j = 0; j < num_attributes; j++) {
        if (min[j] < max[j]) {
            quot = 1.0 / (max[j] - min[j]);
            for (int i = 0; i < num_records; i++) {
                input[i][j] = (input[i][j] - min[j]) * quot;
            }
        } else { // unique value
            for (int i = 0; i < num_records; i++) {
                input[i][j] = 1.0;
            }
        }
    }
}

void APC::process_partition(const vector<string> & file_names, int pos_test, Data & training, Data & testing)
{
    unsigned int num_files = file_names.size();
    if (!(0 <= pos_test && pos_test < num_files)) {
        cout << "Incorrect position" << endl;
        exit(EXIT_FAILURE);
    }
    unsigned int num_records = 0;
    vector<vector<double>> input;
    vector<string> output;
    for (int i = 0; i < num_files; i++) {
        ARFF_file arff(file_names[i]);
        input = arff.get_data().input;
        output = arff.get_data().output;
        if (i != pos_test) {
            num_records = arff.get_num_records();
            for (int j = 0; j < num_records; j++) {
                training.input.push_back(input[j]);
                training.output.push_back(output[j]);
            }
        } else {
            testing.input = input;
            testing.output = output;
        }
    }
    normalize_input(training.input);
    normalize_input(testing.input);
}

void APC::add_metaheuristics() {
    vector<Metaheuristics *> mh4set;
    unsigned int num_sets = training_sets.size();
    for (int i = 0; i < num_sets; i++) {
        mh4set.push_back(new Classifier_1NN("1NN", &training_sets[i], FIT_PARAMETER));
        mh4set.push_back(new Greedy_relief("Greedy", &training_sets[i], FIT_PARAMETER));
//        mh4set.push_back(new Local_search("Local search", &training_sets[i], FIT_PARAMETER, seed));
        mh.push_back(mh4set);
        mh4set.clear();
    }
}

void APC::train()
{
    vector<Result> results;
    for (int i = 0; i < num_sets; i++) {
        for (int j = 0; j < num_mh; j++) {
            results.push_back(mh[i][j]->train());
        }
        train_results.push_back(results);
        results.clear();
    }
    trained = true;
}

void APC::test()
{
    vector<Result> results;
    if (!trained) {
        train();
    }
    for (int i = 0; i < num_sets; i++) {
        for (int j = 0; j < num_mh; j++) {
            results.push_back(mh[i][j]->test(testing_sets[i]));
        }
        test_results.push_back(results);
        results.clear();
    }
}

void APC::get_train_results(vector<vector<Result>> & results)
{
    results = this->train_results;
}

void APC::get_test_results(vector<vector<Result>> & results)
{
    results = this->test_results;
}