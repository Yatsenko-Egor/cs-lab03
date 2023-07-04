#include <iostream>
#include <vector>
#include <string>

using namespace std;

void removeDuplicates(vector<double>& numbers, size_t& count);
vector<double> input_numbers(size_t count);
void find_minmax(const vector<double>& numbers, double& min, double& max);
vector<size_t> make_histogram(const vector<double>& numbers, const size_t bin_count);
size_t find_max_count(const vector<size_t>& bins, const size_t bin_count);
void show_histogram_text(const vector<size_t>& bins, const size_t bin_count);
void output_numbers(const vector<double>& numbers, const size_t& count);

void svg_begin(double width, double height);
void svg_end();
void show_histogram_svg(const vector<size_t>& bins, const size_t &bin_count);
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black");

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
    show_histogram_svg(bins, bin_count);
}

void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end() {
    cout << "</svg>\n";
}

void show_histogram_svg(const vector<size_t>& bins, const size_t &bin_count) {
    const auto IMAGE_WIDTH = 810;
    const auto IMAGE_HEIGHT = 300;
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
    for (size_t bin : bins) {
        scaled_bin = static_cast<size_t>(scaling_factor * bin);
        const double bin_width = BLOCK_WIDTH * scaled_bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "red", "#ffeeee");
        top += BIN_HEIGHT;
    }
    svg_end();
}
void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>" << '\n';
}

void svg_rect(double x, double y, double width, double height,string stroke, string fill) {
    cout << "<rect x=' " << x << "' y=' " << y << "' width=' " << width << "' height=' " << height << "' stroke=' " << stroke << "' fill='" << fill << "'/>" << '\n';
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
        cerr << numbers[i] << ' ';
    }
    cerr << '\n' << '\n';
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