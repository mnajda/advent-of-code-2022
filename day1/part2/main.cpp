#include <algorithm>
#include <ranges>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <iostream>

std::vector<std::vector<std::int64_t>> load_file(const char* filepath)
{
    auto output = std::vector<std::vector<std::int64_t>>{};
    auto file = std::ifstream{filepath};

    auto input = std::string{};
    auto current = std::vector<std::int64_t>{};
    while (std::getline(file, input))
    {
        if (input == std::string{})
        {
            output.push_back(current);
            current.clear();
            continue;
        }

        current.emplace_back(std::stoi(input));
    }

    return output;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        throw std::runtime_error("Provide filepath");
    }

    auto input = load_file(argv[1]);
    auto calories = 
        input
        | std::views::transform([](const auto& elem) { return std::accumulate(elem.begin(), elem.end(), std::int64_t{}); });

    auto sorted_calories = std::vector<int64_t>{calories.begin(), calories.end()};
    std::ranges::sort(sorted_calories, std::ranges::greater());

    auto top_calories = sorted_calories | std::views::take(3);
    const auto result = std::accumulate(top_calories.begin(), top_calories.end(), std::int64_t{});

    std::cout << result << std::endl;
}
