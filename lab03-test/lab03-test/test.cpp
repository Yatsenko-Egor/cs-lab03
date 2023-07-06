#include "build_histogram.h"
#include "show_svg_histogram.h"

#include <cassert>

void test_find_minmax() {
    double min = 0;
    double max = 0;

    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);

    find_minmax({ 1, 2, 3 }, min, max);
    assert(min == 1);
    assert(max == 3);

    find_minmax({ -1, -2, -3 }, min, max);
    assert(min == -3);
    assert(max == -1);

    find_minmax({ 7, 7, 7 }, min, max);
    assert(min == 7);
    assert(max == 7);

}

void test_make_histogram() {

    vector<size_t> result = { 2, 2 };
    assert(make_histogram({0.7, 5.1, -3.5, 4.4}, 2) == result);
    result.assign({3, 3, 4});
    assert(make_histogram({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, 3) == result);

}
void test_remove_duplicates() {

    vector<double> mas1 = { 1, 1, 1, 1, 1, 2, 4, 4, 3, 5 };
    size_t count1 = 10;
    vector<double> result1 = { 1, 2, 4, 3, 5};
    remove_duplicates(mas1, count1);
    assert(mas1 == result1 && count1 == 5);


    vector<double> mas2 = {-1.2, 5.4, 9.2, 3.8, 5.4, -1.2, 9.921};
    size_t count2 = 7;
    vector<double> result2 = {-1.2, 5.4, 9.2, 3.8, 9.921};
    remove_duplicates(mas2, count2);
    assert(mas2 == result2 && count2 == 5);

}

void test_find_max_count() {
    assert(find_max_count({ 1, 1, 1, 2, 2, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5 }, 15) == 5);
    assert(find_max_count({}, 0) == 0);
}

void test() {
    test_find_minmax();
    test_make_histogram();
    test_remove_duplicates();
    test_find_max_count();
}


int
main() {
    test();
}