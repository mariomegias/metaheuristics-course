#include "../inc/metaheuristics.hpp"

const double Metaheuristics::FIT_PARAMETER = 0.75;
const double Metaheuristics::W_THRESHOLD = 0.1;

Metaheuristics::Metaheuristics(const string & name, const Data * training)
{
    this->name = name;
    this->training = training;
    this->num_attributes = training->input[0].size();
    this->weights = vector<double>(num_attributes, 0.0);
    this->trained = false;
}

double Metaheuristics::distance(const vector<double> & a, const vector<double> & b, const vector<double> & w) const
{
    double sum = 0.0;
    unsigned int size = a.size();
    for (int i = 0; i < size; i++) {
        if (w[i] >= W_THRESHOLD) {
            sum += w[i] * pow((a[i] - b[i]), 2);
        }
    }
    return sqrt(sum);
}

string Metaheuristics::classify(const vector<double> & example, const vector<double> & w) const
{
    string target;
    auto min_distance = DBL_MAX;
    double d = -1.0;
    unsigned int num_records = training->input.size();
    if (!trained) {
        for (int i = 0; i < num_records; i++) {
            if (example != training->input[i]) {    // live one out
                d = distance(example, training->input[i], w);
                if (d < min_distance) {
                    target = training->output[i];
                    min_distance = d;
                }
            }
        }
    } else {
        for (int i = 0; i < num_records; i++) {
            d = distance(example, training->input[i], w);
            if (d < min_distance) { // d > 0.0
                target = training->output[i];
                min_distance = d;
            }
        }
    }
    return target;
}

double Metaheuristics::compute_tasa_clas(const Data & data, const vector<double> & w)
{
    unsigned int num_correct_answer = 0;
    unsigned int num_records = data.input.size();
    for (int i = 0; i < num_records; i++) {
        if (classify(data.input[i], w) == data.output[i]) {
            num_correct_answer++;
        }
    }
    return(100.0*(double(num_correct_answer)/num_records));
}

double Metaheuristics::compute_tasa_red(const vector<double> & w) const
{
    int num_low_attributes = 0;
    for (int i = 0; i < num_attributes; i++) {
        if (w[i] < W_THRESHOLD) {
            num_low_attributes++;
        }
    }
    return(100.0*(double(num_low_attributes)/num_attributes));
}

double Metaheuristics::compute_fitness(const Data & data, const vector<double> & w,  Metrics & metrics)
{
    double t_clas = compute_tasa_clas(data, w);
    double t_red = compute_tasa_red(w);
    double fitness = (FIT_PARAMETER * t_clas) + ((1.0 - FIT_PARAMETER) * t_red);
    if (trained) {
        metrics = Metrics(t_clas, t_red, fitness);
    }
    return fitness;
}

Result Metaheuristics::train()
{
    auto ini = high_resolution_clock::now();
    compute_weights();
    auto fin = high_resolution_clock::now();
    training_time = duration_cast<milliseconds>(fin - ini);
    trained = true;
    Metrics metrics;
    compute_fitness(*training, weights, metrics);
    return {name, metrics, weights, training_time};
}

Result Metaheuristics::test(const Data & testing)
{
    if (!trained) {
        train();
    }
    Metrics metrics;
    compute_fitness(testing, weights, metrics);
    return {name, metrics, weights, training_time};
}