#include "../inc/local_search.hpp"

const double Local_search::MEAN = 0.0;
const double Local_search::VARIANCE = 0.3;
const double Local_search::MAX_EVALUATIONS = 1500;

using Random = effolkronium::random_static;

Local_search::Local_search(string name, const Data * training, double fit_parameter, long seed)
: Metaheuristics(name, training, fit_parameter)
{
    Random::seed(seed);
}

void Local_search::gen_neighbour(const vector<double> & actual_sol, vector<double> & neighbour, int pos, normal_distribution<double> & distribution) const
{
    neighbour = actual_sol;
    neighbour[pos] += Random::get(distribution);
    if (neighbour[pos] < 0.0) {
        neighbour[pos] = 0.0;
    } else if (neighbour[pos] > 1.0) {
        neighbour[pos] = 1.0;
    }
}

void Local_search::compute_weights()
{
    normal_distribution<double> distribution(MEAN, sqrt(VARIANCE));

    unsigned int num_evaluations = 0;
    unsigned int num_neighbours_gen = 0;
    const unsigned int MAX_NEIGHBOURS_GEN = 20 * num_attributes;

    vector<double> actual_sol;
    vector<double> neighbour;
    vector<int> permutation;

    Metrics m;

    bool better_sol = false;

    for (int i = 0; i < num_attributes; i++) {
        permutation.push_back(i);
    }

    actual_sol = Random::get<vector>(0.0, 1.0, num_attributes);

    int i = 0;
    double fitness_neighbour = -1.0;
    double fitness_act_sol = compute_fitness(*training, actual_sol, m);
    num_evaluations++;
    do {
        Random::shuffle(permutation);
        i = 0;
        better_sol = false;
        while (!better_sol && (num_neighbours_gen <= MAX_NEIGHBOURS_GEN) && (num_evaluations < MAX_EVALUATIONS))
        {
            gen_neighbour(actual_sol ,neighbour, i, distribution);
            num_neighbours_gen++;
            fitness_neighbour = compute_fitness(*training, neighbour, m);
            num_evaluations++;
            if (fitness_neighbour > fitness_act_sol) {
                better_sol = true;
                actual_sol = neighbour;
                fitness_act_sol = fitness_neighbour;
            } else {
                i++;
                if (i == num_attributes) {
                    i = 0;
                }
            }
        }
        num_neighbours_gen = 0;
    } while (better_sol && (num_evaluations < MAX_EVALUATIONS));

    weights = actual_sol;
}