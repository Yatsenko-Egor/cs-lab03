#pragma comment(lib, "libcurl.dll.a")

#include <iostream>
#include <vector>
#include <string>
#include "show_svg_histogram.h"
#include "build_histogram.h"
#include <curl\curl.h>

using namespace std;

int main(int argc,char* argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++)
            cout << argv[i] << '\n';
        return 0;
    }
    curl_global_init(CURL_GLOBAL_ALL);
    Input data = read_input(cin, false);
    remove_duplicates(data.numbers);
    vector<string> colors = input_colors(data.bin_count);
    vector<size_t> bins = make_histogram(data);
    show_histogram_svg(bins, data.bin_count, colors);
}