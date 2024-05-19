#include "../inc/bmb.hpp"

const unsigned BMB::MAX_EVALUATIONS_LS = 750;
const unsigned BMB::MAX_ITERATIONS = 20;

BMB::BMB(const string & name, const Data * training)
: Metaheuristics(name, training), local_search(Local_search(name, training))
{}

void BMB::compute_weights()
{
    unsigned n_iterations = 0;
    unsigned max_neighbours = 20 * num_attributes;  // esta bien??
    unsigned eval_limit = MAX_EVALUATIONS_LS - 1;

    vector<double> act_sol = Random::get<vector>(0.0, 1.0, num_attributes);
    double fitness_act_sol = compute_fitness(*training, act_sol);

    vector<double> best_sol(act_sol);
    double fitness_best_sol = fitness_act_sol;

    while (n_iterations < MAX_ITERATIONS)
    {
        local_search.do_search(act_sol, fitness_act_sol, max_neighbours, eval_limit);

        if (fitness_best_sol < fitness_act_sol) {
            best_sol = act_sol;
            fitness_best_sol = fitness_act_sol;
        }

        act_sol = Random::get<vector>(0.0, 1.0, num_attributes);
        fitness_act_sol = compute_fitness(*training, act_sol);

        n_iterations++;
    }

    this->weights = best_sol;
}

