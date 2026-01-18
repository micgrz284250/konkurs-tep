# Framework optymalizacyjny

Projekt jest implementacją prostego framework-u do optymalizacji problemu **LCVRP**

Klasy:
* **evaluator** każda implementacja tej klasy abstrakcyjnej ma metodę evaluate, która zwraca jakość podanego rozwiązania
* **problem** każda implementacja tej klasy abstrakcyjnej ma metodę load_problem, która pozwala załadować problem przechowywany według wybranego formatu
* **optimization_algorithm** każda implementacja tej klasy abstrakcyjnej posiada metodę optimize, która zwraca wektor z najlepszym znalezionym rozwiązaniem

**Składowe, na których operuje framework (odgórne założenia)**
1. groups — liczba grup, na które można podzielić permutację
2. dimension — liczba /lokalizacji
3. 