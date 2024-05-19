#include "../inc/es.hpp"

const unsigned ES::MAX_EVALUATIONS = 15000;
const double ES::MEAN = 0.0;
const double ES::VARIANCE = 0.3;
const double ES::PHI = 0.3;
const double ES::MU = 0.1;
const double ES::FIN_TEMP= 0.001;

ES::ES(const string & name, const Data * training, long seed)
: Metaheuristics(name, training)
{
    Random::seed(seed);
    this->normal = normal_distribution<double>(MEAN, sqrt(VARIANCE));
}

void ES::gen_neighbour(const vector<double> & act_sol, vector<double> & neighbor, unsigned pos)
{
    neighbor = act_sol;
    neighbor[pos] += Random::get(normal);
    if (neighbor[pos] < 0.0) {
        neighbor[pos] = 0.0;
    } else if (neighbor[pos] > 1.0) {
        neighbor[pos] = 1.0;
    }
}

unsigned ES::do_search(vector<double> & act_sol, double & fitness_act_sol, unsigned max_neighbors, unsigned eval_limit)
{
    unsigned n_evaluations = 0;
    unsigned n_neighbors = 0;
    unsigned n_successes = 0;
    auto max_successes = (unsigned)(round(0.1 * max_neighbors));

    vector<double> best_sol(act_sol);
    double fitness_best_sol = fitness_act_sol;

    double ini_temp = (MU * fitness_act_sol) / ((-1.0) * log(PHI));
    double act_temp = ini_temp;
    double beta = (ini_temp - FIN_TEMP) / ((double(MAX_EVALUATIONS) / max_neighbors) * ini_temp * FIN_TEMP);

    if (FIN_TEMP < ini_temp)
    {
        vector<double> neighbor;
        double fitness_neighbor;
        double fitness_diff;

        do {

            n_neighbors = 0;
            n_successes = 0;

            while ((n_neighbors < max_neighbors) && (n_successes < max_successes))
            {
                gen_neighbour(act_sol , neighbor, Random::get<unsigned>(0, num_attributes - 1));
                n_neighbors++;
                fitness_neighbor = compute_fitness(*training, neighbor);
                n_evaluations++;

                fitness_diff = fitness_act_sol - fitness_neighbor;

                if (fitness_diff < 0 || Random::get(0.0, 1.0) < exp(((-1.0) * fitness_diff) / act_temp)) {
                    act_sol = neighbor;
                    fitness_act_sol = fitness_neighbor;
                    n_successes++;

                    if (fitness_best_sol < fitness_act_sol) {
                        best_sol = act_sol;
                        fitness_best_sol = fitness_act_sol;
                    }
                }
            }

            act_temp = (act_temp / (1 + beta * act_temp));

        }  while ((0 < n_successes) && (n_evaluations < eval_limit));
    }

    act_sol = best_sol; // output argument

    return n_evaluations;
}

void ES::compute_weights()
{
    unsigned max_neighbors = 10 * num_attributes;

    vector<double> act_sol(Random::get<vector>(0.0, 1.0, num_attributes));
    double fitness_act_sol = compute_fitness(*training, act_sol);

    do_search(act_sol, fitness_act_sol, max_neighbors, MAX_EVALUATIONS - 1);

    this->weights = act_sol;
}

//void ES::compute_weights()
//{
//    unsigned n_evaluations = 0;
//    unsigned n_neighbors = 0;
//    unsigned n_successes = 0;
//    unsigned max_neighbors = 10 * num_attributes;
//    auto max_successes = (unsigned)(round(0.1 * max_neighbors));
//
//    vector<double> act_sol = Random::get<vector>(0.0, 1.0, num_attributes);
//    double fitness_act_sol = compute_fitness(*training, act_sol);
//    n_evaluations++;
//
//    vector<double> best_sol(act_sol);
//    double fitness_best_sol = fitness_act_sol;
//
//    double ini_temp = (MU * fitness_act_sol) / ((-1.0) * log(PHI));
//    double act_temp = ini_temp;
//    double beta = (ini_temp - FIN_TEMP) / ((double(MAX_EVALUATIONS) / max_neighbors) * ini_temp * FIN_TEMP);
//
//    if (FIN_TEMP < ini_temp)
//    {
//        vector<double> neighbor;
//        double fitness_neighbor;
//        double fitness_diff;
//
//        do {
//
//            n_neighbors = 0;
//            n_successes = 0;
//
//            while ((n_neighbors < max_neighbors) && (n_successes < max_successes))
//            {
//                gen_neighbour(act_sol , neighbor, Random::get<unsigned>(0, num_attributes - 1));
//                n_neighbors++;
//                fitness_neighbor = compute_fitness(*training, neighbor);
//                n_evaluations++;
//
//                fitness_diff = fitness_act_sol - fitness_neighbor;
//
//                if (fitness_diff < 0 || Random::get(0.0, 1.0) < exp(((-1.0) * fitness_diff) / act_temp)) {
//                    act_sol = neighbor;
//                    fitness_act_sol = fitness_neighbor;
//                    n_successes++;
//
//                    if (fitness_best_sol < fitness_act_sol) {
//                        best_sol = act_sol;
//                        fitness_best_sol = fitness_act_sol;
//                    }
//                }
//            }
//
//            act_temp = (act_temp / (1 + beta * act_temp));
//
//        }  while ((0 < n_successes) && (n_evaluations < MAX_EVALUATIONS));
//    }
//
//    this->weights = best_sol;
//}