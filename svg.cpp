#include "svg.h"
#include <iostream>
#include <string>
using namespace std;

void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
    cout << "</svg>\n";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill)
{
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill= '" << fill << "' />";
}

void
svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void
show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 410;
    const auto MAX_WIDTH = 350;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    svg_begin(400, 300);
    svg_text(20, 20, to_string(bins[0]));
    svg_rect(50, 0, bins[0] * 10, 30, "red");
    double top = 0; string red = "red"; string black = "black";

    size_t gap;
    cout << "Enter gap size"; cin >> gap;

    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    const bool scaling_needed = (max_count * BLOCK_WIDTH) > MAX_WIDTH;
    for (size_t bin : bins)
    {
        const double bin_width = BLOCK_WIDTH * bin;
        size_t width = bin_width;
        if (scaling_needed) {
            const double scaling_factor = (double)MAX_WIDTH / (max_count * BLOCK_WIDTH);
            width = (bin_width * scaling_factor);
        }
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "red");
        cout << endl;
        top += BIN_HEIGHT;
    }

    cout << "<line x1 = '" << TEXT_WIDTH << "' x2 = '" << TEXT_WIDTH + (max_count * BLOCK_WIDTH) << "' y1 = '" << top + 10 << "' y2 = '" << top + 10 << "' stroke = 'orange' stroke-width = '5'/>";
    svg_text(TEXT_WIDTH, top + 25, "0");
    //const double bin_width1 = BLOCK_WIDTH * bins[0];
    //svg_text(bin_width1, top + 25, to_string(9));

    size_t final_gap;
    if (scaling_needed)
    {
        final_gap = 378;
    }
    else
    {
        final_gap = max_count * BLOCK_WIDTH;
    }

    svg_text(TEXT_WIDTH + 30, top + 25, "3");
    svg_text(final_gap, top + 25, to_string(max_count));
    svg_end();
}