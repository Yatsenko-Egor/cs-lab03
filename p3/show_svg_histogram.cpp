#pragma warning(disable : 4996)
#include <iostream>
#include <vector>
#include <string>
#include "show_svg_histogram.h"
#include <sstream>
#include <windows.h>
#include <winbase.h>

using namespace std;

void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

string make_info_text() {
    stringstream buffer;
    DWORD mask = 0x0000ffff;
    DWORD mask_major = 0x00ff;
    DWORD info = GetVersion();
    DWORD version = info & mask;
    DWORD version_major = version & mask_major;
    DWORD version_minor = version >> 8;
    DWORD platform = info >> 16;
    DWORD build = 0;
    if ((info & 0x80000000) == 0) {
        build = platform;
    }
    buffer << "Windows v" << version_major << '.' << version_minor << " (build " << build << ')' << '\n';

    char computer_name[MAX_COMPUTERNAME_LENGTH + 1];
    unsigned long size = MAX_COMPUTERNAME_LENGTH + 1;
    GetComputerNameA(computer_name, &size);
    buffer << "Computer name: " << computer_name;

    return buffer.str();
}

void svg_end() {
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>" << '\n';
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill) {
    cout << "<rect x=' " << x << "' y=' " << y << "' width=' " << width << "' height=' " << height << "' stroke=' " << stroke << "' fill='" << fill << "'/>" << '\n';
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

void show_histogram_svg(const vector<size_t>& bins, const size_t& bin_count, const vector<string>& colors, string info) {
    const auto IMAGE_WIDTH = 810;
    const auto IMAGE_HEIGHT = 600;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const size_t MAX_NUMBER_OF_CHAR = 80;
    const size_t MAX_ASTERISK = MAX_NUMBER_OF_CHAR - 4;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    double top = 0;
    double scaling_factor = 1.0;
    size_t max_count = find_max_count(bins, bin_count);
    if (max_count > MAX_ASTERISK)
        scaling_factor = MAX_ASTERISK / static_cast<double>(max_count);
    size_t scaled_bin;
    size_t bin;
    for (int i = 0; i < bin_count; i++) {
        bin = bins[i];
        scaled_bin = static_cast<size_t>(scaling_factor * bin);
        const double bin_width = BLOCK_WIDTH * scaled_bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, colors[i], colors[i]);
        top += BIN_HEIGHT;
    }
    string version = info.substr(0, info.find('\n'));
    string computer_name = info.substr(info.find('\n') + 1);
    svg_text(TEXT_LEFT, top + TEXT_BASELINE, version);
    svg_text(TEXT_LEFT, top + 2 * TEXT_BASELINE, computer_name);
    svg_end();
}