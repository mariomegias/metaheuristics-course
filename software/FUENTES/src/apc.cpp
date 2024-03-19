#include "../inc/apc.hpp"

const double APC::FIT_PARAMETER = 0.75;

//APC::APC(const vector<string> & file_names, long seed)
//{
//    this->seed = seed;
//    this->trained = false;
//    unsigned int num_files = file_names.size();
//
//    for (int pos_test = 0; pos_test < num_files; pos_test++) {
//        unsigned int num_records = 0;
//        Data data;
//        vector<vector<double>> input;
//        vector<string> output;
//        for (int i = 0; i < num_files; i++) {
//            ARFF_file arff(file_names[i]);
//            input = arff.get_data().input;
//            output = arff.get_data().output;
//            if (i != pos_test) {
//                num_records = arff.get_num_records();
//                for (int j = 0; j < num_records; j++) {
//                    training_partitions[pos_test].input.push_back(input[j]);
//                    training_partitions[pos_test].output.push_back(output[j]);
//                }
//            } else {
//                testing_partitions[pos_test].input = input;
//                testing_partitions[pos_test].output = output;
//            }
//        }
//        normalize_input(training_partitions[pos_test].input);
//        normalize_input(testing_partitions[pos_test].input);
//    }
//    add_metaheuristics();
//}
//
//void APC::normalize_input(vector<vector<double>> & input)
//{
//    vector<double> max(input[0]);
//    vector<double> min(input[0]);
//    unsigned int num_records = input.size();
//    unsigned int num_attributes = input[0].size();
//
//    for (int j = 0; j < num_attributes; j++) {
//        for (int i = 1; i < num_records; i++) {
//            if (input[i][j] > max[j]) {
//                max[j] = input[i][j];
//            }
//            if (input[i][j] < min[j]) {
//                min[j] = input[i][j];
//            }
//        }
//    }
//
//    double quot = 1.0;
//    for (int j = 0; j < num_attributes; j++) {
//        if (min[j] < max[j]) {
//            quot = 1.0 / (max[j] - min[j]);
//            for (int i = 0; i < num_records; i++) {
//                input[i][j] = (input[i][j] - min[j]) * quot;
//            }
//        } else { // unique value
//            for (int i = 0; i < num_records; i++) {
//                input[i][j] = 1.0;
//            }
//        }
//    }
//}
//
//void APC::add_metaheuristics()
//{
//    unsigned int num_partitions = training_partitions.size();
//    for (int i = 0; i < num_partitions; i++) {
//        mh
//    }
//
//
//    mh.push_back(new Classifier_1NN("1NN", training_partitions, FIT_PARAMETER));
//    mh.push_back(new Greedy_relief("Greedy", reinterpret_cast<const Data *>(&training_partitions), FIT_PARAMETER));
//    // mh.push_back(new Local_search("Local search", training, FIT_PARAMETER, seed));
//}
//
//void APC::train()
//{
//    unsigned int num_mh = mh.size();
//    for (int i = 0; i < num_mh; i++) {
//        train_results.push_back(mh[i]->train());
//    }
//    trained = true;
//}

APC::APC(const vector<string> & file_names, int pos_test, long seed)
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
    this->seed = seed;
    this->trained = false;
    add_metaheuristics();
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

void APC::add_metaheuristics()
{
    //mh.push_back(new Classifier_1NN("1NN", &training, FIT_PARAMETER));
    //mh.push_back(new Greedy_relief("Greedy", &training, FIT_PARAMETER));
    mh.push_back(new Local_search("Local search", &training, FIT_PARAMETER, seed));
}

void APC::train()
{
    unsigned int num_mh = mh.size();
    for (int i = 0; i < num_mh; i++) {
        train_results.push_back(mh[i]->train());
    }
    trained = true;
}

void APC::test()
{
    if (!trained) {
        train();
    }
    unsigned int num_mh = mh.size();
    for (int i = 0; i < num_mh; i++) {
        test_results.push_back(mh[i]->test(testing));
    }
}

void APC::get_train_results(vector<Result> & results)
{
    results = this->train_results;
}

void APC::get_test_results(vector<Result> & results)
{
    results = this->test_results;
}