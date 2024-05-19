#include "../inc/ils.hpp"

const unsigned ILS::MAX_EVALUATIONS = 750;
const unsigned ILS::MAX_ITERATIONS = 20;

ILS::ILS(const string & name, const Data * training, long seed, NeighborhoodSearchType type)
: Metaheuristics(name, training)
{
    Random::seed(seed);

    this->neighborhood_search_type = type;

    switch (neighborhood_search_type)
    {
        case NeighborhoodSearchType::LS:
            this->neighborhood_search = new Local_search(name, training, seed);
            break;
        case NeighborhoodSearchType::ES:
            this->neighborhood_search = new ES(name, training, seed);
            break;
    }
}

vector<double> ILS::mutation_operator(const vector<double> & best_sol, unsigned n_attributes_to_change)
{
    unsigned count = 0, pos;
    vector<double> mutate_sol(best_sol);

    while (count < n_attributes_to_change) {
        pos = Random::get<unsigned>(0, num_attributes - 1);
        mutate_sol[pos] += Random::get(-0.25, 0.25);

        if (mutate_sol[pos] < 0.0) {
            mutate_sol[pos] = 0.0;
        } else if (mutate_sol[pos] > 1.0) {
            mutate_sol[pos] = 1.0;
        }

        count++;
    }

    return mutate_sol;
}

void ILS::compute_weights()
{
    unsigned n_iterations = 0;
    unsigned max_neighbours = 20 * num_attributes;  // esta bien??
    unsigned eval_limit = MAX_EVALUATIONS - 1;

    auto t = (unsigned)(round(0.2 * num_attributes));
    if (t < 3) {
        t = 3;
    }

    vector<double> act_sol = Random::get<vector>(0.0, 1.0, num_attributes);
    double fitness_act_sol = compute_fitness(*training, act_sol);

    neighborhood_search->do_search(act_sol, fitness_act_sol, max_neighbours, eval_limit);

    vector<double> best_sol(act_sol);
    double fitness_best_sol = fitness_act_sol;

    n_iterations++;

    while (n_iterations < MAX_ITERATIONS)
    {
        act_sol = mutation_operator(best_sol, t);
        fitness_act_sol = compute_fitness(*training, act_sol);

        neighborhood_search->do_search(act_sol, fitness_act_sol, max_neighbours, eval_limit);

        if (fitness_best_sol < fitness_act_sol) {
            best_sol = act_sol;
            fitness_best_sol = fitness_act_sol;
        }

        n_iterations++;
    }

    this->weights = best_sol;
}

