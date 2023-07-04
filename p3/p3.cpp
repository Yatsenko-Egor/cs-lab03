#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void removeDuplicates(vector<double>& numbers, size_t& count);
vector<double> input_numbers(size_t count);
void find_minmax(const vector<double>& numbers, double& min, double& max);
vector<size_t> make_histogram(const vector<double>& numbers, const size_t bin_count);
size_t find_max_count(const vector<size_t>& bins, const size_t bin_count);
void show_histogram_text(const vector<size_t>& bins, const size_t bin_count);
void output_numbers(const vector<double>& numbers, const size_t& count);


int main()
{
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    auto numbers = input_numbers(number_count);
    removeDuplicates(numbers, number_count);
    output_numbers(numbers, number_count);
    size_t bin_count;
    cerr << "Enter bin count: ";
    cin >> bin_count;
    vector<size_t> bins = make_histogram(numbers, bin_count);
    show_histogram_text(bins, bin_count);
}

vector<double> input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

void output_numbers(const vector<double> &numbers, const size_t &count) {
    for (size_t i = 0; i < count; i++) {
        cout << numbers[i] << ' ';
    }
    cout << '\n' << '\n';
}

void find_minmax(const vector<double>& numbers, double& min, double& max) {
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
    double min, max;
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

size_t find_max_count(const vector<size_t>& bins, const size_t bin_count) {
    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    return max_count;
}

void show_histogram_text(const vector<size_t>& bins, const size_t bin_count) {
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4;
    double scaling_factor = 1.0;
    size_t height;
    size_t max_count = find_max_count(bins, bin_count);
    if (max_count > MAX_ASTERISK)
        scaling_factor = MAX_ASTERISK / static_cast<double>(max_count);
    for (int i = 0; i < bin_count; i++) {
        if (bins[i] < 100)
            cout << ' ';
        if (bins[i] < 10)
            cout << ' ';
        cout << bins[i] << '|';
        height = static_cast<size_t>(scaling_factor * bins[i]);
        for (int j = 0; j < height; j++)
            cout << '*';
        cout << '\n';
    }
}

void removeDuplicates(vector<double>& numbers, size_t& count) {
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