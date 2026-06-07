#include <iostream>
#include "benchmark.hpp"
#include "avl_tree.cpp"
#include "hash_open_addressing.cpp"
#include "hash_avl.cpp"
#include "hash_chaining.cpp"

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
