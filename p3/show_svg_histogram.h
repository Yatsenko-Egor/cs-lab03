#pragma once
#include <vector>
#include <string>

using namespace std;

void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string stroke, string fill);
size_t find_max_count(const vector<size_t>& bins, const size_t bin_count);
void show_histogram_svg(const vector<size_t>& bins, const size_t& bin_count, const vector<string>& colors);
vector<string> input_colors(size_t count);
string make_info_text();
