#include "histogram.h"
#include "string"
#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({ 1, 2, 3 }, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_negative()
{
    double min = 0;
    double max = 0;
    find_minmax({ -1, -2, -3 }, min, max);
    assert(min == -3);
    assert(max == -1);
}

void same_numbers()
{
    double min = 0;
    double max = 0;
    find_minmax({ 5, 5, 5 }, min, max);
    assert(min == 5);
    assert(max == 5);
}

void one_number()
{
    double min = 0;
    double max = 0;
    find_minmax({ 1 }, min, max);
    assert(min == 1);
    assert(max == 1);

}
void empty_array()
{
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}

void gap_error()
{
    string str = "str";
    int gap = 10;
    if (gap < 2 || gap > 9)
    {
        str = "ERROR";
    }
    assert(str == "ERROR");
}

void scalling_test()
{
    bool scalling_needed = false;
    const int BLOCK_WIDTH = 10;
    const int MAX_WIDTH = 350;
    int max_count = 20;
    if ((max_count * BLOCK_WIDTH) > MAX_WIDTH)
    {
         scalling_needed = true;
    }
    assert(scalling_needed);
}

int
main() {
    test_positive();
    test_negative();
    same_numbers();
    one_number();
    empty_array();
}