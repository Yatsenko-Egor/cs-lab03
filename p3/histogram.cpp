#include "histogram.h"

#include <vector>

using namespace std;

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