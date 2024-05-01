#include "../inc/ag.hpp"

const unsigned AG::POPULATION_SIZE = 50;
const double AG::PROB_MUTATION_CHROMOSOME = 0.08;
const double AG::MEAN = 0.0;
const double AG::VARIANCE = 0.3;
const double AG::MAX_EVALUATIONS = 1500;

AG::AG(const string & name, const Data * training, long seed)
: Metaheuristics(name, training)
{
    Random::seed(seed);
    this->prob_mutation_gen = (PROB_MUTATION_CHROMOSOME/((double)num_attributes));
    this->normal = normal_distribution<double>(MEAN, sqrt(VARIANCE));
}

void AG::ini_population()
{
    for (unsigned i = 0; i < POPULATION_SIZE; i++)
    {
        actual.chromosomes.push_back(Random::get<vector>(0.0, 1.0, num_attributes));
        actual.fitness.push_back(compute_fitness(*training, actual.chromosomes[i]));
    }
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

void AG::mutate(Population & intermediate)
{
    unsigned n_chromosomes = intermediate.size();
    unsigned n_genes = intermediate.n_genes();

    auto n_expected_mutations =
            (unsigned)(round((double)(n_chromosomes * n_genes) * prob_mutation_gen));

    unsigned top_genes = n_genes - 1;
    unsigned top_chromosomes = n_chromosomes - 1;

    unsigned pos_gene, pos_chromosome;

    unsigned count_mutations = 0;
    while (count_mutations < n_expected_mutations)
    {
        pos_gene = Random::get<unsigned>(0, top_genes);
        pos_chromosome = Random::get<unsigned>(0, top_chromosomes);
        mutation_operator(intermediate.chromosomes[pos_chromosome], pos_gene);
        intermediate.fitness[pos_chromosome] =
                compute_fitness(*training, intermediate.chromosomes[pos_chromosome]);

        count_mutations++;
    }
}

unsigned AG::get_pos_best(const Population & population)
{
    const unsigned N_CHROMOSOMES = population.size();

    unsigned pos_best = 0;
    double fitness_best = population.fitness[pos_best];

    for (unsigned i = 1; i < N_CHROMOSOMES; i++)
    {
        if (fitness_best < population.fitness[i]) {
            pos_best = i;
            fitness_best = population.fitness[pos_best];
        }
    }

    return pos_best;
}

unsigned AG::get_pos_worst(const Population & population)
{
    const unsigned N_CHROMOSOMES = population.size();

    unsigned pos_worst = 0;
    double fitness_worst = population.fitness[pos_worst];

    for (unsigned i = 1; i < N_CHROMOSOMES; i++)
    {
        if (fitness_worst > population.fitness[i]) {
            pos_worst = i;
            fitness_worst = population.fitness[pos_worst];
        }
    }

    return pos_worst;
}

void AG::compute_weights()
{
    ini_population();

    Population aux_population;
    for (unsigned int i = 0; i < MAX_EVALUATIONS; i++)
    {
        aux_population = select();
        cross(aux_population);
        mutate(aux_population);
        replace(aux_population);
    }

    weights = actual.chromosomes[get_pos_best(actual)];
}

