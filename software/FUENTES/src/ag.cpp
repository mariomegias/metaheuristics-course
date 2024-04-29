#include "../inc/ag.hpp"

const int AG::POPULATION_SIZE = 50;
const double AG::PROB_MUTATION_CHROMOSOME = 0.08;

const double AG::MEAN = 0.0;
const double AG::VARIANCE = 0.3;
const double AG::MAX_EVALUATIONS = 1500;

AG::AG(const string & name, const Data * training, long seed)
: Metaheuristics(name, training)
{
    Random::seed(seed);
    prob_mutation_gen = (PROB_MUTATION_CHROMOSOME / num_attributes);
    normal = normal_distribution<double>(MEAN, sqrt(VARIANCE));
}

void AG::ini_population()
{
    for (unsigned int i = 0; i < POPULATION_SIZE; i++) {
        population.push_back(Random::get<vector>(0.0, 1.0, num_attributes));
    }
}

void AG::mutation(vector<double> & chromosome, unsigned gene)
{
    chromosome[gene] += Random::get(normal);
    if (chromosome[gene] < 0.0) {
        chromosome[gene] = 0.0;
    } else if (chromosome[gene] > 1.0) {
        chromosome[gene] = 1.0;
    }
}

void AG::mutate(vector<vector<double>> & intermediate_population)
{
    unsigned n_genes = num_attributes;
    unsigned n_chromosomes = intermediate_population.size();

    auto n_expected_mutations = (unsigned)(round((double)(n_chromosomes * n_genes) * prob_mutation_gen));

    unsigned top_genes = n_genes - 1;
    unsigned top_chromosomes = n_chromosomes - 1;

    unsigned pos_gene_to_mutate;
    unsigned pos_chromosome_to_mutate;

    for (unsigned i = 0; i < n_expected_mutations; i++) {
        pos_gene_to_mutate = Random::get<unsigned>(0, top_chromosomes);
        pos_chromosome_to_mutate = Random::get<unsigned>(0, top_genes);
        mutation(intermediate_population[pos_chromosome_to_mutate], pos_gene_to_mutate);
    }
}

void AG::compute_weights()
{
    ini_population();

    vector<vector<double>> aux_population;
    for (unsigned int i = 0; i < MAX_EVALUATIONS; i++)
    {
        aux_population = select();
        cross(aux_population);
        mutate(aux_population);
        replace(aux_population);
    }

    // weights = mejor de la poblacion actual;
}
