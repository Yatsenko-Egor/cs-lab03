#pragma once
#include <vector>
#include <fstream>

using namespace std;

struct Input {
    vector<double> numbers;
    size_t bin_count;
};

void find_minmax(const vector<double> numbers, double& min, double& max);
vector<size_t> make_histogram(const vector<double>& numbers, const size_t bin_count);
vector<double> input_numbers(istream& in, size_t count);
void output_numbers(const vector<double>& numbers, const size_t& count);
void remove_duplicates(vector<double>& numbers, size_t& count);
Input read_input(istream& in);