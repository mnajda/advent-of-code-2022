#include <algorithm>
#include <ranges>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <functional>
#include <deque>
#include <sstream>

using OperationFunction = std::function<std::int64_t(std::int64_t)>;

struct ThrowIndex
{
    std::size_t if_true_{};
    std::size_t if_false_{};
};

struct Throw
{
    std::size_t monkey_index_{};
    std::int64_t item_{};
};

class Monkey
{
    public:
        Monkey(std::deque<std::int64_t> items, OperationFunction operation, const std::int64_t divisor, const ThrowIndex targets)
        : items_{std::move(items)}
        , operation_{std::move(operation)}
        , divisor_{divisor}
        , targets_{targets}
        {
        }

        std::vector<Throw> InspectItems()
        {
            auto thrown = std::vector<Throw>{};
            while (!items_.empty())
            {
                ++inspected_items_;

                auto item = items_.front();
                items_.pop_front();

                auto worry_level = operation_(item) % gcd_;
                if (worry_level % divisor_ == 0)
                {
                    thrown.emplace_back(targets_.if_true_, worry_level); 
                }
                else
                {
                    thrown.emplace_back(targets_.if_false_, worry_level); 
                }
            }

            return thrown;
        }

        void AddItem(const std::int64_t item)
        {
            items_.emplace_back(item);
        }

        void SetGreatesCommonDivisor(const std::int64_t gcd)
        {
            gcd_ = gcd;
        }

        std::int64_t GetDivisor() const
        {
            return divisor_;
        }

        std::int64_t GetInspectedItemsCount() const
        {
            return inspected_items_;
        }

    private:
        std::deque<std::int64_t> items_;
        OperationFunction operation_;
        std::int64_t divisor_;
        ThrowIndex targets_;

        std::int64_t gcd_{};
        std::int64_t inspected_items_{};
};

std::deque<std::int64_t> parse_items(std::stringstream& stream)
{
    auto items = std::deque<std::int64_t>{};
    auto temp = std::string{};
    stream >> temp;
    auto item = std::int64_t{};
    stream >> item;
    items.push_back(item);

    while(stream.peek() == ',')
    {
        stream >> temp;
        stream >> item;
        items.push_back(item);
    }

    return items;
}

OperationFunction parse_operation(std::stringstream& stream)
{
    auto operation = OperationFunction{};
    auto temp = std::string{};
    stream >> temp;
    stream >> temp;
    stream >> temp;

    auto op = std::string{};
    stream >> op;

    if (op == "+")
    {
        stream >> temp;
        if (temp == "old")
        {
            operation = [](const std::int64_t old) { return old + old; };
        }
        else
        {
            auto param = std::stoi(temp);
            operation = [param](const std::int64_t old) { return old + param; };
        }
    }
    else
    {
        stream >> temp;
        if (temp == "old")
        {
            operation = [](const std::int64_t old) { return old * old; };
        }
        else
        {
            auto param = std::stoi(temp);
            operation = [param](const std::int64_t old) { return old * param; };
        }
    }
    
    return operation;
}

std::int64_t parse_divisior(std::stringstream& stream)
{
    auto divisor = std::int64_t{};

    auto temp = std::string{};
    stream >> temp;
    stream >> temp;

    stream >> divisor;

    return divisor;
}

std::vector<Monkey> load_file(const char* filepath)
{
    auto output = std::vector<Monkey>{};
    auto file = std::ifstream{filepath};
    auto input = std::string{};

    auto items = std::deque<std::int64_t>{};
    auto operation = OperationFunction{};
    auto divisor = std::int64_t{};
    auto targets = ThrowIndex{};

    while (std::getline(file, input))
    {
        if (input == std::string{})
        {
            output.emplace_back(std::move(items), std::move(operation), divisor, targets);
            targets = ThrowIndex{};
            continue;
        }

        auto stream = std::stringstream{input};

        auto temp = std::string{};
        stream >> temp;

        if (temp == "Starting")
        {
            items = parse_items(stream);
        }
        else if (temp == "Operation:")
        {
            operation = parse_operation(stream);
        }
        else if (temp == "Test:")
        {
            divisor = parse_divisior(stream);
        }
        else if (temp == "If")
        {
            auto decision = std::string{};
            stream >> decision;
            stream >> temp;
            stream >> temp;
            stream >> temp;

            auto index = std::size_t{};
            stream >> index;
            if (decision == "true:")
            {
                targets.if_true_ = index;
            }
            else
            {
                targets.if_false_ = index;
            }
        }
    }

    output.emplace_back(std::move(items), std::move(operation), divisor, targets);

    return output;
}

std::int64_t find_greatest_common_divisor(const std::vector<Monkey>& monkeys)
{
    return std::accumulate(
        monkeys.cbegin(),
        monkeys.cend(),
        std::int64_t{1},
        [](const auto acc, const auto& monkey) { return acc * monkey.GetDivisor(); });
}

void set_greates_common_divisor(std::vector<Monkey>& monkeys, const std::int64_t gcd)
{
    std::ranges::for_each(monkeys, [gcd](auto& monkey) { monkey.SetGreatesCommonDivisor(gcd); } );
}

void play(std::vector<Monkey>& monkeys)
{
    for (auto i = 0; i < 10'000; ++i)
    {
        for (auto& monkey : monkeys)
        {
            auto items = monkey.InspectItems();
            for (const auto& item : items)
            {
                monkeys[item.monkey_index_].AddItem(item.item_);
            }
        }
    } 
}

std::int64_t calculate_monkey_bussines_level(std::vector<Monkey> monkeys)
{
    auto inspected_items = std::vector<std::int64_t>{};
    std::ranges::transform(
        monkeys,
        std::back_inserter(inspected_items),
        [](const auto& monkey) { return monkey.GetInspectedItemsCount(); } );
    std::ranges::sort(inspected_items, std::ranges::greater());

    return inspected_items.at(0) * inspected_items.at(1);
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        throw std::runtime_error("Provide filepath");
    }

    auto monkeys = load_file(argv[1]);
    set_greates_common_divisor(monkeys, find_greatest_common_divisor(monkeys));

    play(monkeys);
    std::cout << "Result: " << calculate_monkey_bussines_level(std::move(monkeys)) << std::endl;
}
