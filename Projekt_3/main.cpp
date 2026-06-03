#include <iostream>
#include "benchmark.h"
#include "hash_chaining.h"
#include "hash_open_addressing.h"
#include "hash_avl.h"

int main() {
    std::cout << "Miniprojekt 3 – Benchmarki tablic mieszajacych\n";
    std::cout << "Rozmiary n: ";
    for (int s : BENCH_SIZES) std::cout << s << " ";
    std::cout << "\nUsrednianie po " << BENCH_SEEDS.size() << " seedach.\n";

    runBenchmark<HashChaining>       ("Chaining z lista");
    runBenchmark<HashOpenAddressing> ("Open Addressing (linear probing)");
    runBenchmark<HashAVL>            ("Chaining z drzewem AVL");

    std::cout << "\nGotowe.\n";
    return 0;
}
