#pragma once
#include <vector>
#include <fstream>

using namespace std;

struct Input {
    vector<double> numbers;
    size_t bin_count;
    vector<string> colors;
};

void find_minmax(const vector<double> numbers, double& min, double& max);
vector<size_t> make_histogram(Input& data);
vector<double> input_numbers(istream& in, size_t count);
void output_numbers(const vector<double>& numbers, const size_t& count);
void remove_duplicates(vector<double>& numbers);
Input read_input(istream& in, bool prompt);
Input download(const string& address);
size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx);
vector<string> input_colors(istream& in, size_t count);