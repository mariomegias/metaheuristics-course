#include "../inc/apc.hpp"

APC::APC(const vector<string> & file_names, long seed)
{
    this->seed = seed;
    this->trained = false;
    this->num_sets = file_names.size();

    vector<Data> data;
    for (int i = 0; i < num_sets; i++) {
        ARFF_file arff_file(file_names[i]);
        data.push_back(arff_file.get_data());
    }

    normalize(data);

    Data training;
    Data testing;
    for (int i = 0; i < num_sets; i++) {
        process_partition(data, i, training, testing);
        this->training_sets.push_back(training);
        this->testing_sets.push_back(testing);
        training.clear();
        testing.clear();
    }

    add_metaheuristics();
    this->num_mh = mh[0].size();
}

void APC::normalize(vector<Data> & data)
{
    unsigned int num_attributes = data[0].input[0].size();
    unsigned int num_records = 0;
    vector<double> max(num_attributes, DBL_MIN);
    vector<double> min(num_attributes, DBL_MAX);

    for (int i = 0; i < num_sets; i++) {
        num_records = data[i].input.size();
        for (int j = 0; j < num_attributes; j++) {
            for (int k = 0; k < num_records; k++) {
                if (data[i].input[k][j] > max[j]) {
                    max[j] = data[i].input[k][j];
                }
                if (data[i].input[k][j] < min[j]) {
                    min[j] = data[i].input[k][j];
                }
            }
        }
    }

    double quot = 1.0;
    for (int i = 0; i < num_sets; i++) {
        num_records = data[i].input.size();
        for (int j = 0; j < num_attributes; j++) {
            if (min[j] < max[j])
            {
                quot = 1.0 / (max[j] - min[j]);
                for (int k = 0; k < num_records; k++) {
                    data[i].input[k][j] = (data[i].input[k][j] - min[j]) * quot;
                }
            } else {
                cerr << "Error in data. " << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}

void APC::process_partition(const vector<Data> & data, int pos_test, Data & training, Data & testing)
{
    unsigned int num_records = 0;
    vector<vector<double>> input;
    vector<string> output;
    for (int i = 0; i < num_sets; i++) {
        input = data[i].input;
        output = data[i].output;
        if (i != pos_test) {
            num_records = input.size();
            for (int j = 0; j < num_records; j++) {
                training.input.push_back(input[j]);
                training.output.push_back(output[j]);
            }
        } else {
            testing.input = input;
            testing.output = output;
        }
    }
}

void APC::add_metaheuristics() {
    vector<Metaheuristics *> mh4set;
    for (int i = 0; i < num_sets; i++) {
//        mh4set.push_back(new Classifier_1NN("1NN", &training_sets[i]));
//        mh4set.push_back(new Greedy_relief("Greedy", &training_sets[i]));
//        mh4set.push_back(new Local_search("Local search", &training_sets[i], seed));
//        mh4set.push_back(new AGG("AGG-BLX", &training_sets[i], seed, CrossingType::BLX));
//        mh4set.push_back(new AGG("AGG-CA", &training_sets[i], seed, CrossingType::CA));
//        mh4set.push_back(new AGE("AGE-BLX", &training_sets[i], seed, CrossingType::BLX));
//        mh4set.push_back(new AGE("AGE-CA", &training_sets[i], seed, CrossingType::CA));
//        mh4set.push_back(new AM_All("AM_ALL-BLX", &training_sets[i], seed, CrossingType::BLX));
//        mh4set.push_back(new AM_Best("AM_best-BLX", &training_sets[i], seed, CrossingType::BLX));
//        mh4set.push_back(new AM_Rand("AM_Rand-BLX", &training_sets[i], seed, CrossingType::BLX));
        mh4set.push_back(new ES("ES", &training_sets[i], seed));
        mh4set.push_back(new BMB("BMB", &training_sets[i], seed));
        mh4set.push_back(new ILS("ILS-LS", &training_sets[i], seed, NeighborhoodSearchType::LS));
        mh4set.push_back(new ILS("ILS-ES", &training_sets[i], seed, NeighborhoodSearchType::ES));
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