#include "../inc/apc.hpp"
#include <iomanip>

void show_results(Dataset dataset_name, vector<vector<Result>> & results, const string & sep)
{
    string name;
    switch (dataset_name) {
        case Dataset::ecoli: name = "ecoli        "; break;
        case Dataset::parkinsons: name = "parkinsons   "; break;
        case Dataset::breast_cancer: name = "breast-cancer"; break;
    }

    unsigned int num_sets = results.size();
    unsigned int num_mh = results[0].size();
    unsigned int num_attributes = results[0][0].w.size();
    unsigned int top = num_attributes - 1;

    double sum_tasa_clas = 0;
    double sum_tasa_red = 0;
    double sum_fitness = 0;
    double sum_time = 0;
    double aux = 1.0/double(num_sets);

    cout << fixed << setprecision(2);

    for (int j = 0; j < num_mh; j++) {
        for (int i = 0; i < num_sets; ++i) {
            sum_tasa_clas += results[i][j].metrics.tasa_clas;
            sum_tasa_red += results[i][j].metrics.tasa_red;
            sum_fitness += results[i][j].metrics.fitness;
            auto time_sec = double(results[i][j].time.count())/1000;
            sum_time += time_sec;
            cout << name                            << setw(15)
                 << results[i][j].name_mh           << setw(15)
                 << (i+1)                           << setw(15)
                 << results[i][j].metrics.tasa_clas << setw(15)
                 << results[i][j].metrics.tasa_red  << setw(15)
                 << results[i][j].metrics.fitness   << setw(15)
                 << scientific << time_sec
                 << fixed << setprecision(2) << endl;
        }
        cout << "Mean:"               << setw(53)
             << (sum_tasa_clas * aux) << setw(15)
             << (sum_tasa_red  * aux) << setw(15)
             << (sum_fitness   * aux) << setw(15)
             << scientific << (sum_time * aux)
             << fixed << setprecision(2) << endl << endl;
        for (int i = 0; i < num_sets; ++i) {
            cout << "Weights partition " << (i+1) << ": " ;
            for (int k = 0; k < top; ++k) {
                cout << results[i][j].w[k] << ",";
            }
            cout << results[i][j].w[top] << endl;
        }
        cout << sep << endl;
        sum_tasa_clas = 0;
        sum_tasa_red = 0;
        sum_fitness = 0;
        sum_time = 0;
    }
}

void show_results_csv(Dataset dataset_name, vector<vector<Result>> & results, const string & sep)
{
    string name;
    switch (dataset_name) {
        case Dataset::ecoli: name = "ecoli        "; break;
        case Dataset::parkinsons: name = "parkinsons   "; break;
        case Dataset::breast_cancer: name = "breast-cancer"; break;
    }

    unsigned int num_sets = results.size();
    unsigned int num_mh = results[0].size();

    double sum_tasa_clas = 0;
    double sum_tasa_red = 0;
    double sum_fitness = 0;
    double sum_time = 0;
    double aux = 1.0/double(num_sets);

    cout << fixed << setprecision(2);

    for (int j = 0; j < num_mh; j++) {
        for (int i = 0; i < num_sets; ++i) {
            sum_tasa_clas += results[i][j].metrics.tasa_clas;
            sum_tasa_red += results[i][j].metrics.tasa_red;
            sum_fitness += results[i][j].metrics.fitness;
            auto time_sec = double(results[i][j].time.count())/1000;
            sum_time += time_sec;
            cout << name                            << ";"
                 << results[i][j].name_mh           << ";"
                 << (i+1)                           << ";"
                 << results[i][j].metrics.tasa_clas << ";"
                 << results[i][j].metrics.tasa_red  << ";"
                 << results[i][j].metrics.fitness   << ";"
                 << scientific << time_sec
                 << fixed << setprecision(2) << endl;
        }
        cout << (sum_tasa_clas * aux) << ";"
             << (sum_tasa_red  * aux) << ";"
             << (sum_fitness   * aux) << ";"
             << scientific << (sum_time * aux)
             << fixed << setprecision(2) << endl << endl;
        cout << sep << endl;
        sum_tasa_clas = 0;
        sum_tasa_red = 0;
        sum_fitness = 0;
        sum_time = 0;
    }
}


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cerr << "Error in parameters, introduce only the name of the program and the seed: "
             << "\t./program_name <seed>" << endl;
        exit(EXIT_FAILURE);
    }

    string curr_arg;
    long seed = stol(argv[1]);

    Random::seed(seed);

    string path = "Instancias_APC/";

    vector<string> ecoli;
    ecoli.push_back(path + "ecoli_1.arff");
    ecoli.push_back(path + "ecoli_2.arff");
    ecoli.push_back(path + "ecoli_3.arff");
    ecoli.push_back(path + "ecoli_4.arff");
    ecoli.push_back(path + "ecoli_5.arff");

    vector<string> parkinsons;
    parkinsons.push_back(path + "parkinsons_1.arff");
    parkinsons.push_back(path + "parkinsons_2.arff");
    parkinsons.push_back(path + "parkinsons_3.arff");
    parkinsons.push_back(path + "parkinsons_4.arff");
    parkinsons.push_back(path + "parkinsons_5.arff");

    vector<string> breast;
    breast.push_back(path + "breast-cancer_1.arff");
    breast.push_back(path + "breast-cancer_2.arff");
    breast.push_back(path + "breast-cancer_3.arff");
    breast.push_back(path + "breast-cancer_4.arff");
    breast.push_back(path + "breast-cancer_5.arff");

    vector<vector<string>> data_sets;
    data_sets.push_back(ecoli);
    data_sets.push_back(parkinsons);
    data_sets.push_back(breast);

    vector<vector<Result>> train_results;
    vector<vector<Result>> test_results;

    string sep = "..........................................................................................................";

    cout << sep << endl;
    cout << "Seed: " << seed << endl;
    cout << sep << endl;
    cout << "Dataset" << setw(21) << "Algorithm" << setw(15 ) << "Partition" << setw(15)
         << "%_class" << setw(15) << "%_red"     << setw(15 ) << "Fitness"   << setw(15) << "T (s)" << endl;
    cout << sep << endl;

    unsigned int num_data_sets = data_sets.size();
    for (int i = 0; i < num_data_sets; ++i) {
        APC apc(data_sets[i]);
        apc.test();
        apc.get_test_results(test_results);
        show_results(Dataset(i), test_results, sep);
    }

    return EXIT_SUCCESS;
}