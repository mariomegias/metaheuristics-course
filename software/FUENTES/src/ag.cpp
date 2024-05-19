#include "../inc/ag.hpp"

const double AG::MEAN = 0.0;
const double AG::VARIANCE = 0.3;
const double AG::PROB_MUTATION_CHROMOSOME = 0.08;

const unsigned AG::MAX_EVALUATIONS = 15000;
const unsigned AG::POPULATION_SIZE = 50;

AG::AG(const string & name, const Data * training, CrossingType crossing_type)
: Metaheuristics(name, training)
{
    this->normal = normal_distribution<double>(MEAN, sqrt(VARIANCE));

    this->tournament = Tournament();
    this->crossing_type = crossing_type;

    switch (crossing_type)
    {
        case CrossingType::BLX:
            crossing = new BLX();
            break;
        case CrossingType::CA:
            crossing = new CA();
            break;
    }

    // Initial values without meaning. Reinitialize in subclasses.
    this->n_chromosomes_select = 0;
    this->n_expected_crossings = 0;
}

void AG::mutation_operator(vector<double> & chromosome, unsigned pos_gene)
{
    chromosome[pos_gene] += Random::get(normal);
    if (chromosome[pos_gene] < 0.0) {
        chromosome[pos_gene] = 0.0;
    } else if (chromosome[pos_gene] > 1.0) {
        chromosome[pos_gene] = 1.0;
    }
}

void AG::ini_current_population()
{
    for (unsigned i = 0; i < POPULATION_SIZE; i++) {
        current_population.chromosomes.push_back(Random::get<vector>(0.0, 1.0, num_attributes));
    }

    // Initial values without meaning. This population will immediately evaluate with evaluate function.
    current_population.fitness = vector<double>(POPULATION_SIZE, 0.0);
}

void AG::evaluate(Population & population, unsigned & num_evaluations)
{
    const unsigned N_CHROMOSOMES = population.size();
    for (unsigned i = 0; i < N_CHROMOSOMES; i++) {
        population.fitness[i] = compute_fitness(*training, population.chromosomes[i]);
        num_evaluations++;
    }
}

Population AG::select()
{
    unsigned pos_winner;
    vector<vector<double>> chromosomes;
    vector<double> fitness;

    for (unsigned i = 0; i < n_chromosomes_select; i++) {
        pos_winner = tournament.get_pos_winner(current_population);
        chromosomes.push_back(current_population.chromosomes[pos_winner]);
        fitness.push_back(current_population.fitness[pos_winner]);
    }

    return {chromosomes, fitness};
}

void AG::cross(Population & parents)
{
    for (unsigned i = 0; i < n_expected_crossings; i+=2) {
        crossing->cross(parents.chromosomes[i], parents.chromosomes[i+1]);
    }
}

unsigned AG::get_pos_best(const Population & population)
{
    unsigned pos_best = 0;
    double fitness_best = population.fitness[pos_best];

    const unsigned N_CHROMOSOMES = population.size();
    for (unsigned i = 1; i < N_CHROMOSOMES; i++) {
        if (fitness_best < population.fitness[i]) {
            pos_best = i;
            fitness_best = population.fitness[pos_best];
        }
    }

    return pos_best;
}

unsigned AG::get_pos_worst(const Population & population)
{
    unsigned pos_worst = 0;
    double fitness_worst = population.fitness[pos_worst];

    const unsigned N_CHROMOSOMES = population.size();
    for (unsigned i = 1; i < N_CHROMOSOMES; i++) {
        if (fitness_worst > population.fitness[i]) {
            pos_worst = i;
            fitness_worst = population.fitness[pos_worst];
        }
    }

    return pos_worst;
}

void AG::compute_weights()
{
    unsigned n_evaluations = 0;
    Population aux_population;

    ini_current_population();
    evaluate(current_population, n_evaluations);

    while (n_evaluations < MAX_EVALUATIONS) {
        aux_population = select();
        cross(aux_population);
        mutate(aux_population);
        evaluate(aux_population, n_evaluations);
        replace(aux_population);
    }

    weights = current_population.chromosomes[get_pos_best(current_population)];
}

