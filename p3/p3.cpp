#include <iostream>
#include <vector>
#include <string>
#include "show_svg_histogram.h"
#include "build_histogram.h"

using namespace std;

int main()
{
    Input data = read_input(cin, false);
    remove_duplicates(data.numbers);
    vector<string> colors = input_colors(data.bin_count);
    vector<size_t> bins = make_histogram(data);
    show_histogram_svg(bins, data.bin_count, colors);
}