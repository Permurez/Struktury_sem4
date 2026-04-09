#include <iostream>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <fstream>

#include "DynamicArray.hpp"
#include "SignlyLinkedList.hpp"
#include "DoubleLinkedList.hpp"

const int REPEAT_TIMES = 1000; // liczba operacji na jeden pomiar
const int AVG_RUNS= 100;    // ile razy usredniamy każdy pomiar
const int SEED_COUNT = 10;   // ile seedow do usredniania (zeby nie bylo halucynacji wynikow)

// --- Infrastruktura pomiarowa ---

template<typename Func>
long long measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end   = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

struct TestResult { long long da, sll, dll; };

// Tworzy nowe struktury, wypełnia prefill losowymi elementami, mierzy czas func na każdej
template<typename Func>
TestResult run_test(int prefill, Func func) {
    DynamicArray DA; SinglyLinkedList SLL; DoubleLinkedList DLL;
    int targetIdx = (prefill > 0) ? (rand() % prefill) : -1;// czyli wiemy ze w naszym zbiorze jest element o wartosci 42,
    for (int i = 0; i < prefill; i++) {  // mamy odpowiedz na wszystkie najwazniejsze pytania w calej galaktyce
        int value = (i == targetIdx) ? 42 : rand();
        DA.addBack(value);
        SLL.addBack(value);
        DLL.addBack(value);
    }
    return { measureTime([&]{ func(DA);  }),
             measureTime([&]{ func(SLL); }),
             measureTime([&]{ func(DLL); }) };
}

// Wykonuje AVG_RUNS pomiarow i zwraca usredniony wynik
template<typename Func>
TestResult avg_test(int prefill, Func func) {
    long long da=0, sll=0, dll=0;
    for (int r = 0; r < AVG_RUNS; r++) {
        srand(67 + (r % SEED_COUNT)); // zeby bylo smiesznie to seedy ktorych uzywam to
        auto t = run_test(prefill, func);// 67 68 69 70 71 72 73 74 75 76 i potem znowu od 67, zeby miec powtarzalnosc wynikow, ale tez zeby nie bylo halucynacji
        da += t.da; sll += t.sll; dll += t.dll;
    }
    return { da/AVG_RUNS, sll/AVG_RUNS, dll/AVG_RUNS };
}

void print_header() {
    std::cout << std::left  << std::setw(24) << "Operacja"
              << std::right << std::setw(14) << "DynamicArray"
              << std::setw(14) << "SinglyLinked"
              << std::setw(14) << "DoublyLinked" << '\n'
              << std::string(66, '-') << '\n';
}

void print_row(const std::string& name, long long da, long long sll, long long dll) {
    std::cout << std::left  << std::setw(24) << name
              << std::right << std::setw(14) << da
              << std::setw(14) << sll
              << std::setw(14) << dll << '\n';
}

// --- Benchmark na 8 rozmiarach struktury ---

void run_benchmark() {
    const int sizes[] = {
        5000, 10000, 15000, 20000, 25000,
        30000, 35000, 40000, 45000, 50000,
        55000, 60000, 65000, 70000, 75000,
        80000, 85000, 90000, 95000, 100000
    };

    std::cout << "\n=== Benchmark [mikrosekundy, srednia z " << AVG_RUNS << " pomiarow] ===\n";
    std::cout << "Seed rotation: 67 68 69 70 71 72 73 74 75 76\n";

    for (int si = 0; si < 20; si++) {
        int P = sizes[si];
        std::cout << "\n--- n = " << P << " ---\n";
        print_header();

        // lambda pomocnicza: wywoluje avg_test i drukuje wiersz
        auto pr = [&](const std::string& name, auto func) {
            auto t = avg_test(P, func);
            print_row(name, t.da, t.sll, t.dll);
        };

        pr("addFront",           [](auto& c){ for(int i=0;i<REPEAT_TIMES;i++) c.addFront(i); });
        pr("addBack",            [](auto& c){ for(int i=0;i<REPEAT_TIMES;i++) c.addBack(i);  });
        pr("addAtIndex rand",    [P](auto& c){ for(int i=0;i<REPEAT_TIMES;i++) c.addAtIndex(i, rand()%P); });
        std::cout << std::string(66, '-') << '\n';
        pr("removeFront",        [](auto& c){ for(int i=0;i<REPEAT_TIMES;i++) c.removeFront(); });
        pr("removeBack",         [](auto& c){ for(int i=0;i<REPEAT_TIMES;i++) c.removeBack();  });
        // P-REPEAT_TIMES gwarantuje, że indeks nie wyjdzie poza rozmiar listy podczas usuwania
        pr("removeAtIndex rand", [P](auto& c){ for(int i=0;i<REPEAT_TIMES;i++) c.removeAtIndex(rand()%(P-REPEAT_TIMES)); });
        std::cout << std::string(66, '-') << '\n';
        pr("find existing",      [](auto& c){ for(int i=0;i<REPEAT_TIMES;i++) c.find(42); }); // szukamy elementu, który jest w zbiorze
        std::cout << std::string(66, '-') << '\n';
    }
    std::cout << "\nBenchmark zakończony.\n";
}

// --- Menu dwupoziomowe ---

template<typename T>
void structureMenu(T& s, const std::string& name) {
    int ch, val, idx;
    do {
        std::cout << "\n=== " << name << " ===\n"
                  << " 1. Dodaj na poczatku    2. Dodaj na koncu    3. Dodaj na pozycji\n"
                  << " 4. Usuń z poczatku      5. Usun z konca      6. Usun z pozycji\n"
                  << " 7. Znajdz               8. Zbuduj z pliku    9. Utworz losowo\n"
                  << "10. Wyświetl              0. Wroc\n> ";
        std::cin >> ch;
        switch (ch) {
            case 1:
                std::cout << "Wartość: "; std::cin >> val;
                s.addFront(val); break;
            case 2:
                std::cout << "Wartość: "; std::cin >> val;
                s.addBack(val); break;
            case 3:
                std::cout << "Wartość indeks: "; std::cin >> val >> idx;
                s.addAtIndex(val, idx); break;
            case 4:
                s.removeFront(); std::cout << "Usunięto z początku.\n"; break;
            case 5:
                s.removeBack(); std::cout << "Usunięto z końca.\n"; break;
            case 6:
                std::cout << "Indeks: "; std::cin >> idx;
                s.removeAtIndex(idx); break;
            case 7:
                std::cout << "Wartość: "; std::cin >> val;
                std::cout << (s.find(val) ? "Znaleziono.\n" : "Nie znaleziono.\n"); break;
            case 8: {
                // Wczytanie z pliku - najpierw czyścimy strukturę (zgodnie z założeniami)
                std::string fname;
                std::cout << "Nazwa pliku (np. dane.txt): "; std::cin >> fname;
                std::ifstream f(fname);
                if (!f) { std::cout << "Błąd: nie można otworzyć pliku.\n"; break; }
                s.clear();
                int x; while (f >> x) s.addBack(x);
                std::cout << "Wczytano z pliku.\n"; break;
            }
            case 9:
                std::cout << "Rozmiar: "; std::cin >> val;
                s.clear();
                for (int i = 0; i < val; i++) s.addBack(rand());
                std::cout << "Utworzono losowo (" << val << " elementów).\n"; break;
            case 10:
                s.display(); break;
            case 0: break;
            default:
                std::cout << "Nieznana opcja.\n";
        }
    } while (ch != 0);
}

int main() {
    srand(67); // stałe ziarno dla odtwarzalności wyników

    DynamicArray    DA;
    SinglyLinkedList SLL;
    DoubleLinkedList DLL;

    int ch;
    do {
        std::cout << "\n=== MENU GŁÓWNE ===\n"
                  << "1. Tablica dynamiczna\n"
                  << "2. Lista jednokierunkowa\n"
                  << "3. Lista dwukierunkowa\n"
                  << "4. Uruchom benchmark\n"
                  << "0. Wyjście\n> ";
        std::cin >> ch;
        switch (ch) {
            case 1: structureMenu(DA,  "Tablica dynamiczna");    break;
            case 2: structureMenu(SLL, "Lista jednokierunkowa"); break;
            case 3: structureMenu(DLL, "Lista dwukierunkowa");   break;
            case 4: run_benchmark(); break;
            case 0: break;
            default: std::cout << "Nieznana opcja.\n";
        }
    } while (ch != 0);

    return 0;
}