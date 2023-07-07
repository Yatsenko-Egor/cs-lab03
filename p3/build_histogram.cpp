#include "build_histogram.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void find_minmax(const vector<double> numbers, double& min, double& max) {
    if (numbers.empty())
        return;
    min = numbers[0];
    max = numbers[0];
    for (double x : numbers) {
        if (x < min) {
            min = x;
        }
        else if (x > max) {
            max = x;
        }
    }
}

vector<size_t> make_histogram(const vector<double>& numbers, const size_t bin_count) {
    vector<size_t> bins(bin_count);
    double min = 0, max = 0;
    find_minmax(numbers, min, max);
    double bin_size = (max - min) / bin_count;
    for (double number : numbers) {
        size_t bin = static_cast<size_t>((number - min) / bin_size);
        if (bin == bin_count) {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}
vector<double> input_numbers(istream& in,size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }
    return result;
}

void output_numbers(const vector<double>& numbers, const size_t& count) {
    for (size_t i = 0; i < count; i++) {
        cerr << numbers[i] << ' ';
    }
    cerr << '\n' << '\n';
}


void remove_duplicates(vector<double>& numbers, size_t& count) {
    vector<double> dublicates;
    bool is_find;
    int i = 0;
    while (i < count) {
        is_find = false;
        for (int j = 0; j < dublicates.size(); j++) {
            if (fabs(dublicates[j] - numbers[i]) < 0.000001) {
                is_find = true;
                break;
            }
        }
        if (is_find) {
            numbers.erase(numbers.begin() + i);
            count--;
        }
        else {
            dublicates.push_back(numbers[i]);
            i++;
        }
    }
}