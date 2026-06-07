#include <iostream>
#include "benchmark.hpp"
#include "avl_tree.hpp"
#include "hash_open_addressing.hpp"
#include "hash_avl.hpp"
#include "hash_chaining.hpp"

int main() {
    std::cout << "Miniprojekt 3 - Benchmarki tablic mieszajacych\n";
    std::cout << "Rozmiary n: ";
    for (int s : BENCH_SIZES) std::cout << s << " ";
    std::cout << "\nUsrednianie po " << BENCH_SEEDS.size() << " seedach.\n";

    runBenchmark<HashChaining>("Chaining z lista");
    runBenchmark<HashOpenAddressing>("Open Addressing (linear probing)");
    runBenchmark<HashAVL>("Chaining z drzewem AVL");

    std::cout << "\nGotowe.\n";
    return 0;
}
