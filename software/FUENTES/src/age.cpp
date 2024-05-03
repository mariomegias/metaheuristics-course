#include "../inc/age.hpp"

const unsigned AGE::N_CHROMOSOMES_SELECT = 2;
const unsigned AGE::TOURNAMENT_SIZE = 3;

AGE::AGE(const string & name, const Data * training, long seed, CrossingType crossing_type)
: AG(name, training, seed)
{
    this->tournament = Tournament(TOURNAMENT_SIZE);
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
}

Population AGE::select()
{
    unsigned pos_winner = 0;
    vector<vector<double>> chromosomes;
    vector<double> fitness;

    for (unsigned i = 0; i < N_CHROMOSOMES_SELECT; i++) {
        pos_winner = tournament.get_pos_winner(current_population);
        chromosomes.push_back(current_population.chromosomes[pos_winner]);
        fitness.push_back(current_population.fitness[pos_winner]);
    }

    return {chromosomes, fitness};
}

void AGE::cross(Population & parents)
{
    crossing->cross(parents.chromosomes[0], parents.chromosomes[1]);
}

void AGE::mutate(Population & intermediate)
{
    const unsigned TOP_GENES = (intermediate.n_genes() - 1);
    const unsigned N_CHROMOSOMES = intermediate.size();
    for (int i = 0; i < N_CHROMOSOMES; i++) {
        if (Random::get(0.0, 1.0) < PROB_MUTATION_CHROMOSOME) {
            mutation_operator(intermediate.chromosomes[i], Random::get<unsigned>(0, TOP_GENES));
        }
    }
}

void AGE::get_two_worst_pos(vector<unsigned> & worst_positions)
{
    unsigned pos_first_worst = get_pos_worst(current_population);

    unsigned pos_second_worst;
    double fitness_second_worst = 101;

    for (int i = 0; i < POPULATION_SIZE; i++) {
        if ((i != pos_first_worst) && (fitness_second_worst > current_population.fitness[i])) {
            pos_second_worst = i;
            fitness_second_worst = current_population.fitness[pos_second_worst];
        }
    }

    worst_positions.push_back(pos_first_worst);
    worst_positions.push_back(pos_second_worst);
}

void AGE::replace(Population & children)
{
    vector<unsigned> worst_positions;
    get_two_worst_pos(worst_positions);

    priority_queue<pair<vector<double>, double>, vector<pair<vector<double>, double>>, Compare_AGE> rivals;
    rivals.emplace(children.chromosomes[0], children.fitness[0]);
    rivals.emplace(children.chromosomes[1], children.fitness[1]);
    rivals.emplace(current_population.chromosomes[worst_positions[0]], current_population.fitness[worst_positions[0]]);
    rivals.emplace(current_population.chromosomes[worst_positions[1]], current_population.fitness[worst_positions[1]]);

    current_population.chromosomes[worst_positions[0]] = rivals.top().first;
    current_population.fitness[worst_positions[0]] = rivals.top().second;

    rivals.pop();

    current_population.chromosomes[worst_positions[1]] = rivals.top().first;
    current_population.fitness[worst_positions[1]] = rivals.top().second;
}