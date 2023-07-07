#include "build_histogram.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


Input read_input(istream& in) {
    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter bin count: ";
    in >> data.bin_count;

    return data;
}

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

vector<size_t> make_histogram(Input &data) {
    vector<size_t> bins(data.bin_count);
    double min = 0, max = 0;
    find_minmax(data.numbers, min, max);
    double bin_size = (max - min) / data.bin_count;
    for (size_t i = 0; i < data.numbers.size(); i++) {
        bool found = false;
        size_t j;
        for (j = 0; (j < data.bin_count - 1) && !found; j++) {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= data.numbers[i]) && (data.numbers[i] < hi)) {
                bins[j]++;
                found = true;
            }
        }
        if (!found) {
            bins[data.bin_count - 1]++;
        }
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