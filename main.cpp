#include <iostream>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <string>
 
#include "DynamicArray.hpp"
#include "SignlyLinkedList.hpp"
#include "DoubleLinkedList.hpp"

static const int REPEAT_TIMES = 10000; //10k powtorzen
static const int PREFILL = 100000; //100k elementow na start

template<typename Func>
long long measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}
template<typename Func>
void run_test(const std::string& name, Func func){// & zeby szlo przez referencje
    DynamicArray DA ; SinglyLinkedList SLL; DoubleLinkedList DLL;//initializacja struktur 
    for (int i = 0; i < PREFILL; i++)
     {
    DA.addBack(i);//IntelliSense tutaj cos halucynuje i podkreśla na czerwono, raczej jest dobrze
    SLL.addBack(i);
    DLL.addBack(i); //prefill struktur danych
    }
std::cout << std::left  << std::setw(26) << name
          << std::right << std::setw(14) << measureTime([&]{ func(DA); })
          << std::setw(14) << measureTime([&]{ func(SLL); }) // 14 miejsc na wynik measuretime wykonanych na fukncji func dla SLL
          << std::setw(14) << measureTime([&]{ func(DLL); }) << '\n';
}    



int main() {
    // jest wybrane jako ziarno zeby byla odtwarzalnosc wynikow 
srand(67);

std::cout << "\n=== Miniprojekt 1 - Pomiar czasu [mikrosekundy] ===\n\n";
    std::cout << std::left  << std::setw(26) << "Operacja"
              << std::right << std::setw(14) << "DynamicArray"
              << std::setw(14) << "SinglyLinked"
              << std::setw(14) << "DoublyLinked" << '\n';
    std::cout << std::string(68, '-') << '\n';

    //testy start
    // Przez c przekazuje dane, auto dla wygody zeby nie definiowac co przekazuje, a & zeby nie kopiowalo struktury

    run_test("addFront", [](auto& c) { 
        for(int i=0; i<REPEAT_TIMES; i++) c.addFront(i); 
    });

    run_test("addBack", [](auto& c) { 
        for(int i=0; i<REPEAT_TIMES; i++) c.addBack(i); 
    });

    run_test("addAtIndex rand", [](auto& c) { 
        for(int i=0; i<REPEAT_TIMES; i++) c.addAtIndex(i, rand() % PREFILL); 
    });

    std::cout << std::string(68, '-') << '\n';

    run_test("removeFront", [](auto& c) { 
        for(int i=0; i<REPEAT_TIMES; i++) c.removeFront(); 
    });

    run_test("removeBack", [](auto& c) { 
        for(int i=0; i<REPEAT_TIMES; i++) c.removeBack(); 
    });

    run_test("removeAtIndex random", [](auto& c) { 
        for(int i=0; i<REPEAT_TIMES; i++) c.removeAtIndex(rand() % (PREFILL - i)); 
    });

    std::cout << std::string(68, '-') << '\n';

    run_test("find worst case", [](auto& c) { 
        for(int i=0; i<REPEAT_TIMES; i++) c.find(PREFILL + 1); 
    });

    std::cout << std::string(68, '-') << '\n';
    std::cout << "\n okok, koniec mierzenia\n\n";

    return 0; 
}


