#include "../inc/local_search.hpp"

const double Local_search::MEAN = 0.0;
const double Local_search::VARIANCE = 0.3;
const unsigned Local_search::MAX_EVALUATIONS = 15000;

using Random = effolkronium::random_static;

Local_search::Local_search(const string & name, const Data * training)
: Metaheuristics(name, training)
{
    this->normal = normal_distribution<double>(MEAN, sqrt(VARIANCE));
}

void Local_search::gen_neighbour(const vector<double> & actual_solution, vector<double> & neighbor, unsigned pos)
{
    neighbor = actual_solution;
    neighbor[pos] += Random::get(normal);
    if (neighbor[pos] < 0.0) {
        neighbor[pos] = 0.0;
    } else if (neighbor[pos] > 1.0) {
        neighbor[pos] = 1.0;
    }
}

unsigned Local_search::do_search(vector<double> & act_sol, double & fitness_act_sol, unsigned max_neighbors, unsigned eval_limit)
{
    vector<double> neighbor;
    double fitness_neighbor;

    vector<unsigned> permutation;

    for (int i = 0; i < num_attributes; i++) {
        permutation.push_back(i);
    }

    Random::shuffle(permutation);

    unsigned position = 0;
    unsigned count_evaluations = 0;
    unsigned num_neighbors_gen = 0;

    while ((num_neighbors_gen < max_neighbors) && (count_evaluations < eval_limit))
    {
        gen_neighbour(act_sol , neighbor, position);
        num_neighbors_gen++;
        fitness_neighbor = compute_fitness(*training, neighbor);
        count_evaluations++;
        if (fitness_neighbor > fitness_act_sol) {
            act_sol = neighbor;
            fitness_act_sol = fitness_neighbor;
            num_neighbors_gen = 0;
            Random::shuffle(permutation);
            position = 0;
        } else {
            position++;
            if (position == num_attributes) {
                position = 0;
            }
        }
    }

    return count_evaluations;
}

void Local_search::compute_weights()
{
    unsigned max_neighbors = 20 * num_attributes;

    vector<double> act_sol(Random::get<vector>(0.0, 1.0, num_attributes));
    double fitness_act_sol = compute_fitness(*training, act_sol);

    do_search(act_sol, fitness_act_sol, max_neighbors, MAX_EVALUATIONS - 1);

    this->weights = act_sol;
}

