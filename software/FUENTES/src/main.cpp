#include "../inc/apc.hpp"
#include <iomanip>

void show_results(Dataset_name dataset_name, vector<vector<Result>> & results)
{
    string name;
    switch (dataset_name) {
        case Dataset_name::ecoli:           name = "ecoli        "; break;
        case Dataset_name::parkinsons:      name = "parkinsons   "; break;
        case Dataset_name::breast_cancer:   name = "breast-cancer"; break;
    }

    unsigned int num_sets = results.size();
    unsigned int num_mh = results[0].size();
    unsigned int num_attributes = results[0][0].w.size();
    unsigned int top = num_attributes - 1;

    double tasa_clas = -1;
    double tasa_red = -1;
    double fitness = -1;
    double sum_tasa_clas = 0;
    double sum_tasa_red = 0;
    double sum_fitness = 0;

    double aux = 1.0/double(num_sets);

    cout << fixed << setprecision(2);
//  cout << scientific;

    for (int j = 0; j < num_mh; j++) {
        for (int i = 0; i < num_sets; ++i) {
            sum_tasa_clas += results[i][j].metrics.tasa_clas;
            sum_tasa_red += results[i][j].metrics.tasa_red;
            sum_fitness += results[i][j].metrics.fitness;
            cout << name                            << setw(15)
                 << results[i][j].name_mh           << setw(15)
                 << (i+1)                           << setw(15)
                 << results[i][j].metrics.tasa_clas << setw(15)
                 << results[i][j].metrics.tasa_red  << setw(15)
                 << results[i][j].metrics.fitness   << setw(15);
            cout << "Weights: ";
            for (int k = 0; k < top; ++k) {
                cout << results[i][j].w[k] << ",";
            }
            cout << results[i][j].w[top];
            cout << endl;
        }
        cout << "Mean:"               << setw(53)
             << (sum_tasa_clas * aux) << setw(15)
             << (sum_tasa_red  * aux) << setw(15)
             << (sum_fitness   * aux) << endl;
        cout << ".........................................................................................." << endl;
        sum_tasa_clas = 0;
        sum_tasa_red = 0;
        sum_fitness = 0;
    }
}

void show_weights()
{

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

    vector<string> ecoli;
    ecoli.push_back("Instancias_APC/ecoli_1.arff");
    ecoli.push_back("Instancias_APC/ecoli_2.arff");
    ecoli.push_back("Instancias_APC/ecoli_3.arff");
    ecoli.push_back("Instancias_APC/ecoli_4.arff");
    ecoli.push_back("Instancias_APC/ecoli_5.arff");

    vector<string> parkinsons;
    parkinsons.push_back("Instancias_APC/parkinsons_1.arff");
    parkinsons.push_back("Instancias_APC/parkinsons_2.arff");
    parkinsons.push_back("Instancias_APC/parkinsons_3.arff");
    parkinsons.push_back("Instancias_APC/parkinsons_4.arff");
    parkinsons.push_back("Instancias_APC/parkinsons_5.arff");

    vector<string> breast;
    breast.push_back("Instancias_APC/breast-cancer_1.arff");
    breast.push_back("Instancias_APC/breast-cancer_2.arff");
    breast.push_back("Instancias_APC/breast-cancer_3.arff");
    breast.push_back("Instancias_APC/breast-cancer_4.arff");
    breast.push_back("Instancias_APC/breast-cancer_5.arff");

    vector<vector<string>> data_sets;
    data_sets.push_back(ecoli);
    data_sets.push_back(parkinsons);
    data_sets.push_back(breast);

    vector<vector<Result>> train_results;
    vector<vector<Result>> test_results;

    cout << ".........................................................................................." << endl;
    cout << "Seed: " << seed << endl;
    cout << ".........................................................................................." << endl;
    cout << "Dataset" << setw(21)
         << "Algorithm" << setw(15 )
         << "Partition" << setw(15 )
         << "%_class" << setw(15)
         << "%_red" << setw(15 )
         << "Fitness" << setw(15) << endl;
        // T (ms)
    cout << ".........................................................................................." << endl;

    unsigned int num_data_sets = data_sets.size();
    for (int i = 0; i < num_data_sets; ++i) {
        APC apc(data_sets[i], seed);
        apc.test();
        apc.get_test_results(test_results);
        show_results(Dataset_name(i), test_results);
    }

    return EXIT_SUCCESS;
}