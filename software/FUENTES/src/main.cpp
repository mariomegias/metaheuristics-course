#include "../inc/apc.hpp"

void show_train_results(vector<Result> & train_results) 
{
    cout << "////////       TRAIN          ///////////" << endl;
    unsigned int num_results = train_results.size();
    for (int i = 0; i < num_results; i++) {
        cout << "----------------------------------------" << endl;
        cout << "ALGORITMO " << i << ":" << endl;
        cout << "Tasa de Clasificación: " << train_results[i].metrics.tasa_clas << endl;
        cout << "Tasa de Reducción: " << train_results[i].metrics.tasa_red << endl;
        cout << "Fitness: " << train_results[i].metrics.fitness << endl;
        cout << endl;
    }
}

void show_test_results(vector<Result> & test_results) 
{
    cout << "////////       TEST          ///////////" << endl;
    unsigned int num_results = test_results.size();
    for (int i = 0; i < num_results; i++) {
        cout << "----------------------------------------" << endl;
        cout << "ALGORITMO " << i << ":" << endl;
        cout << "Tasa de Clasificación: " << test_results[i].metrics.tasa_clas << endl;
        cout << "Tasa de Reducción: " << test_results[i].metrics.tasa_red << endl;
        cout << "Fitness: " << test_results[i].metrics.fitness << endl;
        cout << endl;
    }
}

int main()
{
    // path realtive to binary file

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

    vector<vector<string>> datasets;
//    datasets.push_back(ecoli);
    datasets.push_back(parkinsons);
//    datasets.push_back(breast);

    int test_position = 3;
    long seed = 123;

    vector<Result> train_results;
    vector<Result> test_results;

    unsigned num_datasets = datasets.size();
    for (int i = 0; i < num_datasets; i++) {
        cout << "--------------------------------------------------------------------------------------------" << endl;
        APC apc(datasets[i], test_position, seed);
        apc.train();
        apc.test();
        apc.get_train_results(train_results);
        apc.get_test_results(test_results);
        show_train_results(train_results);
        show_test_results(test_results);
    }

    return EXIT_SUCCESS;
}