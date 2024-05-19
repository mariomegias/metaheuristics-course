#include "../inc/age.hpp"

const unsigned AGE::N_CHROMOSOMES_SELECT = 2;
const unsigned AGE::N_EXPECTED_CROSSINGS = 1;

AGE::AGE(const string & name, const Data * training, CrossingType crossing_type)
: AG(name, training, crossing_type)
{
    this->n_chromosomes_select = N_CHROMOSOMES_SELECT;
    this->n_expected_crossings = N_EXPECTED_CROSSINGS;
}

void AGE::mutate(Population & intermediate)
{
    const unsigned TOP_GENES = (num_attributes - 1);
    for (int i = 0; i < N_CHROMOSOMES_SELECT; i++) {
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

