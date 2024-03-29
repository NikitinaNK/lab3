﻿// laba3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
#include "Header.h"

using namespace std;


vector<double>input_numbers(size_t count)
{
    cerr << "Enter numbers: ";
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}



vector<size_t>make_histogram(const vector<double>& numbers, size_t count, double min, double max)
{
    find_minmax(numbers, min, max);
    vector<size_t> bins(count);
    for (double number : numbers)
    {
        size_t bin = (size_t)((number - min) / (max - min) * count);
        if (bin == count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}


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

void
svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black")
{
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill= '" << fill <<"' />";
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
    svg_rect(50, 0, bins[0] * 10, 30, "red" );
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

    cout << "<line x1 = '" << TEXT_WIDTH << "' x2 = '" << TEXT_WIDTH+(max_count * BLOCK_WIDTH) << "' y1 = '" << top + 10 << "' y2 = '" << top + 10<<"' stroke = 'orange' stroke-width = '5'/>";
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

void show_histogram_text(vector<size_t> bins)
{

    // Вывод данных
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins)
    {
        if (bin < 100)
        {
            cout << ' ';
        }
        if (bin < 10)
        {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++)
        {
            cout << '*';
        }
        cout << '\n';
    }
}

int main()
{
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
   

    // Ввод чисел заменен вызовом функции:
    auto const numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;
     double min = numbers[0];
    double max = numbers[0];
    const auto bins = make_histogram(numbers, bin_count,min, max);
    show_histogram_svg(bins);


    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
