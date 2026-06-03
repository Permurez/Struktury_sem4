# Struktury_sem4

Zbiór projektów z przedmiotu struktury danych (sem. 4).

Foldery:
- `Projekt_1` – implementacje list/tablic (C++).
- `Projekt_2` – kolejki priorytetowe (C++).
- `Projekt_3` – benchmarki tablic mieszających (C++). Zaktualizowany `Makefile` używa `-std=c++20`.

Szybkie budowanie projektu 3 (Windows + MSYS/mingw g++):

```powershell
cd Projekt_3
C:/msys64/mingw64/bin/g++.exe -std=c++20 -O2 -Wall -Wextra main.cpp -o app.exe
./app.exe
```

Jeśli wolisz użyć `make`, zainstaluj `make` (np. przez MSYS2 lub Chocolatey) i uruchom `make` w katalogu `Projekt_3`.

Jak wypchnąć na GitHub:

1. Utwórz repo na GitHubie (np. `Struktury_sem4`).
2. W katalogu roboczym uruchom:

```bash
git remote add origin https://github.com/USERNAME/Struktury_sem4.git
git branch -M main
git push -u origin main
```

Zastąp `USERNAME` własnym loginem. Jeśli używasz `gh` CLI, możesz też utworzyć repo komendą `gh repo create`.
