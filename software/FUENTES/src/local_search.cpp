#include "../inc/local_search.hpp"

const double Local_search::MEAN = 0.0;
const double Local_search::VARIANCE = 0.3;
const double Local_search::MAX_EVALUATIONS = 15000;

using Random = effolkronium::random_static;

Local_search::Local_search(const string & name, const Data * training, long seed)
: Metaheuristics(name, training)
{
    Random::seed(seed);
    this->max_neighbors_to_generate = 20 * num_attributes;
    this->normal = normal_distribution<double>(MEAN, sqrt(VARIANCE));
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

void Local_search::do_local_search(vector<double> & actual_solution, double & fitness_act_sol, unsigned & num_evaluations, unsigned max_neighbors_gen)
{
    if (num_evaluations < MAX_EVALUATIONS)
    {
        unsigned int num_neighbors_gen = 0;

        vector<double> neighbour;
        vector<int> permutation;

        for (int i = 0; i < num_attributes; i++) {
            permutation.push_back(i);
        }

        unsigned int pos = 0;
        double fitness_neighbour = -1.0;

        fitness_act_sol = compute_fitness(*training, actual_solution);
        num_evaluations++;

        Random::shuffle(permutation);
        while ((num_neighbors_gen < max_neighbors_gen) && (num_evaluations < MAX_EVALUATIONS))
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
}

void Local_search::compute_weights()
{
    vector<double> actual_solution = Random::get<vector>(0.0, 1.0, num_attributes);
    double fitness_act_sol;
    unsigned num_evaluations = 0;
    do_local_search(actual_solution, fitness_act_sol, num_evaluations, max_neighbors_to_generate);
    weights = actual_solution;
}

