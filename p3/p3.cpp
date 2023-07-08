#include <iostream>
#include <vector>
#include <string>
#include "show_svg_histogram.h"
#include "build_histogram.h"

using namespace std;

int main()
{
    string info = make_info_text();
    cout << info;
    return 0;
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    auto numbers = input_numbers(number_count);
    remove_duplicates(numbers, number_count);
    output_numbers(numbers, number_count);
    size_t bin_count;
    cerr << "Enter bin count: ";
    cin >> bin_count;
    vector<string> colors = input_colors(bin_count);
    vector<size_t> bins = make_histogram(numbers, bin_count);
    show_histogram_svg(bins, bin_count, colors);
}