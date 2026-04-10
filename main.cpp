#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

#include "DoubleLinkedList.hpp"
#include "DynamicArray.hpp"
#include "SignlyLinkedList.hpp"

constexpr int REPEAT_TIMES = 1000;
constexpr int AVG_RUNS = 30;
constexpr int BASE_SEED = 67;
constexpr int SEED_COUNT = 5;

struct TestResult {
    long long dynamicArray = 0;
    long long singlyLinked = 0;
    long long doublyLinked = 0;
};

TestResult& operator+=(TestResult& lhs, const TestResult& rhs) {
    lhs.dynamicArray += rhs.dynamicArray;
    lhs.singlyLinked += rhs.singlyLinked;
    lhs.doublyLinked += rhs.doublyLinked;
    return lhs;
}

TestResult operator/(const TestResult& value, long long divisor) {
    return {
        value.dynamicArray / divisor,
        value.singlyLinked / divisor,
        value.doublyLinked / divisor
    };
}

template <typename Func>
long long measureMicroseconds(Func func) {
    const auto start = std::chrono::high_resolution_clock::now();
    func();
    const auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

template <typename Func>
void repeatBenchmarkOperation(Func func) {
    for (int i = 0; i < REPEAT_TIMES; ++i) func(i);
}

template <typename Operation>
TestResult runSingleMeasurement(int initialSize, Operation operation) {
    DynamicArray dynamicArray;
    SinglyLinkedList singlyLinked;
    DoubleLinkedList doublyLinked;

    const int targetIndex = (initialSize > 0) ? (rand() % initialSize) : -1;
    for (int i = 0; i < initialSize; ++i) {
        const int value = (i == targetIndex) ? 42 : rand();
        dynamicArray.addBack(value);
        singlyLinked.addBack(value);
        doublyLinked.addBack(value);
    }

    return {
        measureMicroseconds([&] { operation(dynamicArray); }),
        measureMicroseconds([&] { operation(singlyLinked); }),
        measureMicroseconds([&] { operation(doublyLinked); })
    };
}

template <typename Operation>
TestResult runAverageMeasurement(int initialSize, Operation operation) {
    TestResult sum;

    for (int run = 0; run < AVG_RUNS; ++run) {
        srand(BASE_SEED + (run % SEED_COUNT));
        sum += runSingleMeasurement(initialSize, operation);
    }

    return sum / AVG_RUNS;
}

void printHeader() {
    std::cout << std::left << std::setw(24) << "Operacja"
              << std::right << std::setw(14) << "DynamicArray"
              << std::setw(14) << "SinglyLinked"
              << std::setw(14) << "DoublyLinked" << '\n'
              << std::string(66, '-') << '\n';
}

void printRow(const std::string& name, const TestResult& result) {
    std::cout << std::left << std::setw(24) << name
              << std::right << std::setw(14) << result.dynamicArray
              << std::setw(14) << result.singlyLinked
              << std::setw(14) << result.doublyLinked << '\n';
}

void runBenchmark() {
    const int sizes[] = {
        5000, 10000, 15000, 20000, 25000,
        30000, 35000, 40000, 45000, 50000,
        55000, 60000, 65000, 70000, 75000,
        80000, 85000, 90000, 95000, 100000
    };

    std::cout << "\n=== Benchmark [mikrosekundy, srednia z " << AVG_RUNS << " pomiarow] ===\n";
    std::cout << "Seed rotation: 67 68 69 70 71\n";

    for (int size : sizes) {
        std::cout << "\n--- n = " << size << " ---\n";
        printHeader();

        const auto printBenchmarkRow = [&](const std::string& operationName, auto operation) {
            printRow(operationName, runAverageMeasurement(size, operation));
        };

        printBenchmarkRow("addFront", [](auto& structure) {
            repeatBenchmarkOperation([&](int i) { structure.addFront(i); });
        });
        printBenchmarkRow("addBack", [](auto& structure) {
            repeatBenchmarkOperation([&](int i) { structure.addBack(i); });
        });
        printBenchmarkRow("addAtIndex rand", [size](auto& structure) {
            repeatBenchmarkOperation([&](int i) { structure.addAtIndex(i, rand() % size); });
        });
        std::cout << std::string(66, '-') << '\n';

        printBenchmarkRow("removeFront", [](auto& structure) {
            repeatBenchmarkOperation([&](int) { structure.removeFront(); });
        });
        printBenchmarkRow("removeBack", [](auto& structure) {
            repeatBenchmarkOperation([&](int) { structure.removeBack(); });
        });
        printBenchmarkRow("removeAtIndex rand", [size](auto& structure) {
            repeatBenchmarkOperation([&](int) { structure.removeAtIndex(rand() % (size - REPEAT_TIMES)); });
        });
        std::cout << std::string(66, '-') << '\n';

        printBenchmarkRow("find existing", [](auto& structure) {
            repeatBenchmarkOperation([&](int) { structure.find(42); });
        });
        std::cout << std::string(66, '-') << '\n';
    }

    std::cout << "\nBenchmark zakonczony.\n";
}

int main() {
    srand(BASE_SEED);

    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== MENU ===\n"
                  << "1. Uruchom benchmark\n"
                  << "0. Wyjscie\n> ";

        std::cin >> choice;

        if (choice == 1) {
            runBenchmark();
        } else if (choice != 0) {
            std::cout << "Nieznana opcja.\n";
        }
    }

    return 0;
}