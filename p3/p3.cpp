#include <iostream>
#include <vector>
#include <string>
#include "show_svg_histogram.h"
#include "build_histogram.h"

using namespace std;

int main(int argc,char* argv[]) {
    Input input;
    if (argc > 1) {
        input = download(argv[1]);
    }
    else {
        input = read_input(cin, true);
    }
    remove_duplicates(input.numbers);
    vector<string> colors = input_colors(input.bin_count);
    const auto bins = make_histogram(input);
    show_histogram_svg(bins, input.bin_count, colors);
}