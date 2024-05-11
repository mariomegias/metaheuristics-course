#include "../inc/local_search.hpp"

const double Local_search::MEAN = 0.0;
const double Local_search::VARIANCE = 0.3;
const unsigned Local_search::MAX_EVALUATIONS = 15000;

using Random = effolkronium::random_static;

Local_search::Local_search(const string & name, const Data * training, long seed)
: Metaheuristics(name, training)
{
    Random::seed(seed);
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

unsigned Local_search::do_local_search(vector<double> & actual_solution, double & fitness_act_sol, unsigned max_neighbors_gen, unsigned evaluations_limit)
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

    while ((num_neighbors_gen < max_neighbors_gen) && (count_evaluations < evaluations_limit))
    {
        gen_neighbour(actual_solution , neighbor, position);
        num_neighbors_gen++;
        fitness_neighbor = compute_fitness(*training, neighbor);
        count_evaluations++;
        if (fitness_neighbor > fitness_act_sol) {
            actual_solution = neighbor;
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
    vector<double> actual_solution = Random::get<vector>(0.0, 1.0, num_attributes);
    double fitness_act_sol = compute_fitness(*training, actual_solution);
    unsigned max_neighbours_gen = 20 * num_attributes;
    unsigned evaluations_limit = MAX_EVALUATIONS - 1;

    do_local_search(actual_solution, fitness_act_sol, max_neighbours_gen, evaluations_limit);

    weights = actual_solution;
}

