#include "../inc/local_search.hpp"

const double Local_search::MEAN = 0.0;
const double Local_search::VARIANCE = 0.3;
const double Local_search::MAX_EVALUATIONS = 1500;

using Random = effolkronium::random_static;

Local_search::Local_search(const string & name, const Data * training, long seed)
: Metaheuristics(name, training)
{
    Random::seed(seed);
}

void Local_search::gen_neighbour(const vector<double> & actual_solution, vector<double> & neighbour, unsigned int pos, normal_distribution<double> & normal) const
{
    neighbour = actual_solution;
    neighbour[pos] += Random::get(normal);
    if (neighbour[pos] < 0.0) {
        neighbour[pos] = 0.0;
    } else if (neighbour[pos] > 1.0) {
        neighbour[pos] = 1.0;
    }
}

void Local_search::do_search(vector<double> & actual_solution)
{
    normal_distribution<double> normal(MEAN, sqrt(VARIANCE));

    unsigned int num_evaluations = 0;
    unsigned int num_neighbors_gen = 0;
    const unsigned int MAX_NEIGHBORS_GEN = 20 * num_attributes;

    vector<double> neighbour;
    vector<int> permutation;

    for (int i = 0; i < num_attributes; i++) {
        permutation.push_back(i);
    }

    unsigned int pos = 0;
    double fitness_neighbour = -1.0;
    double fitness_act_sol = compute_fitness(*training, actual_solution);
    num_evaluations++;

    Random::shuffle(permutation);
    while ((num_neighbors_gen < MAX_NEIGHBORS_GEN) && (num_evaluations < MAX_EVALUATIONS))
    {
        gen_neighbour(actual_solution , neighbour, pos, normal);
        num_neighbors_gen++;
        fitness_neighbour = compute_fitness(*training, neighbour);
        num_evaluations++;
        if (fitness_neighbour > fitness_act_sol) {
            actual_solution = neighbour;
            fitness_act_sol = fitness_neighbour;
            num_neighbors_gen = 0;
            Random::shuffle(permutation);
            pos = 0;
        } else {
            pos++;
            if (pos == num_attributes) {
                pos = 0;
            }
        }
    }
}

void Local_search::compute_weights()
{
    vector<double> actual_solution = Random::get<vector>(0.0, 1.0, num_attributes);
    do_search(actual_solution);
    weights = actual_solution;
}

//void Local_search::compute_weights()
//{
//    normal_distribution<double> distribution(MEAN, sqrt(VARIANCE));
//
//    unsigned int num_evaluations = 0;
//    unsigned int num_neighbours_gen = 0;
//    const unsigned int MAX_NEIGHBOURS_GEN = 20 * num_attributes;
//
//    vector<double> actual_sol;
//    vector<double> neighbour;
//    vector<int> permutation;
//
//    Metrics m;
//
//    bool better_sol = false;
//
//    for (int i = 0; i < num_attributes; i++) {
//        permutation.push_back(i);
//    }
//
//    actual_sol = Random::get<vector>(0.0, 1.0, num_attributes);
//
//    unsigned int i = 0;
//    double fitness_neighbour = -1.0;
//    double fitness_act_sol = compute_fitness(*training, actual_sol, m);
//    num_evaluations++;
//
//    do {
//        Random::shuffle(permutation);
//        i = 0;
//        better_sol = false;
//        while (!better_sol && (num_neighbours_gen < MAX_NEIGHBOURS_GEN) && (num_evaluations < MAX_EVALUATIONS))
//        {
//            gen_neighbour(actual_sol ,neighbour, i, distribution);
//            num_neighbours_gen++;
//            fitness_neighbour = compute_fitness(*training, neighbour, m);
//            num_evaluations++;
//            if (fitness_neighbour > fitness_act_sol) {
//                better_sol = true;
//                actual_sol = neighbour;
//                fitness_act_sol = fitness_neighbour;
//            } else {
//                i++;
//                if (i == num_attributes) {
//                    i = 0;
//                }
//            }
//        }
//        num_neighbours_gen = 0;
//    } while (better_sol && (num_evaluations < MAX_EVALUATIONS));
//
//    weights = actual_sol;
//}