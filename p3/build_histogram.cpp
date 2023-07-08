#pragma comment(lib, "libcurl.dll.a")
#include "build_histogram.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <curl\curl.h>

using namespace std;

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    size_t data_size = item_size * item_count;
    buffer->write(reinterpret_cast<char*>(items), data_size);
    return data_size;
}

Input download(const string& address) {
    stringstream buffer;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (res != 0) {
            cerr << curl_easy_strerror(res);
            exit(1);
        }
    }
    curl_easy_cleanup(curl);

    return read_input(buffer, false);
}

Input read_input(istream& in, bool prompt) {
    Input data;
    if (prompt)
        cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;
    if (prompt)
        cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);
    if (prompt)
        cerr << "Enter bin count: ";
    in >> data.bin_count;

    data.colors = input_colors(in, data.bin_count);
    return data;
}

vector<string> input_colors(istream& in, size_t count) {
    vector<string> result(count);
    string color;
    in.ignore(2);
    for (size_t i = 0; i < count; i++) {
        cerr << "Enter color: ";
        getline(in, color, '\r');
        in.ignore(1);
        while (color[0] != '#' && color.find(' ') != -1) {
            cerr << "Non-existent color. Enter other color: ";
            getline(in, color, '\r');
            in.ignore(1);
        }
        result[i] = color;
    }
    return result;
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


void remove_duplicates(vector<double>& numbers) {
    vector<double> dublicates;
    bool is_find;
    int i = 0;
    size_t count = numbers.size();
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