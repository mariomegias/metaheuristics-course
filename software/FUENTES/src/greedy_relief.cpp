#include "../inc/greedy_relief.hpp"

Greedy_relief::Greedy_relief(string name, const Data * training, double fit_parameter)
: Metaheuristics(name, training, fit_parameter) {}

double Greedy_relief::euclidean_distance(const vector<double> & a, const vector<double> & b) const
{
    double sum = 0.0;
    unsigned int size = a.size();
    for (int i = 0; i < size; i++) {
        sum += pow((a[i] - b[i]), 2);
    }
    return sqrt(sum);
}

void Greedy_relief::compute_nearest_enemy(const vector<double> & example, const string & target, vector<double> & nearest_enemy)
{
    auto min_distance = DBL_MAX;
    double distance = -1.0;
    unsigned int num_records = training->input.size();
    for (int i = 0; i < num_records; i++) {
        if (training->output[i] != target) {
            distance = euclidean_distance(training->input[i], example);
            if (distance < min_distance) {
                min_distance = distance;
                nearest_enemy = training->input[i];
            }
        }
    }
}

void Greedy_relief::compute_nearest_friend(const vector<double> & example, const string & target, vector<double> & nearest_friend)
{
    auto min_distance = DBL_MAX;
    double distance = -1.0;
    unsigned int num_records = training->input.size();
    for (int i = 0; i < num_records; i++) {
        if (training->output[i] == target && (example != training->input[i])) {
            distance = euclidean_distance(training->input[i], example);
            if (distance < min_distance) {
                min_distance = distance;
                nearest_friend = training->input[i];
            }
        }
    }
}

void Greedy_relief::compute_weights()
{
    vector<double> nearest_friend;
    vector<double> nearest_enemy;
    unsigned int num_records = training->input.size();
    for (int i = 0; i < num_records; i++) {
        compute_nearest_friend(training->input[i], training->output[i], nearest_friend);
        compute_nearest_enemy(training->input[i], training->output[i], nearest_enemy);
        for (int j = 0; j < num_attributes; j++) {
            weights[j] += abs(training->input[i][j] - nearest_enemy[j]) - abs(training->input[i][j] - nearest_friend[j]);
        }
    }

    double max = weights[0];
    for (int i = 0; i < num_attributes; i++) {
        if (weights[i] > max) {
            max = weights[i];
        }
    }

    for (int i = 0; i < num_attributes; i++) {
        if (weights[i] < 0) {
            weights[i] = 0.0;
        } else {
            weights[i] = weights[i] / max;
        }
    }
}