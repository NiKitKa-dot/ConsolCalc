# ConsolCalc — Консольный калькулятор на Qt

Учебный проект по дисциплине «Программирование на C++/Qt».
Лабораторная работа №1: консольный калькулятор с использованием метаобъектной
системы Qt (сигналы и слоты).

**Индивидуальный вариант:** №13 — НОК двух чисел (базовый уровень),
CSV-парсер с вычислениями (средний уровень), CMake + CTest + CPack
(продвинутый уровень).

---

## Возможности

| Команда        | Описание                                              |
|----------------|-------------------------------------------------------|
| `add <a> <b>`  | Сложение                                              |
| `sub <a> <b>`  | Вычитание                                             |
| `mul <a> <b>`  | Умножение                                             |
| `div <a> <b>`  | Деление с проверкой деления на ноль                   |
| `lcm <a> <b>`  | НОК двух натуральных чисел (вариант 13)               |
| `csv <path>`   | Построчный разбор CSV-файла: суммы и средние значения |
| `reset`        | Сброс состояния калькулятора                          |
| `help`         | Справка по командам                                   |
| `quit` / `exit`| Выход                                                 |

Ошибочные ситуации (деление на ноль, некорректный ввод, отсутствие файла,
нечисловые токены в CSV, НОК от неположительных чисел) обрабатываются через
отдельный сигнал `errorOccurred`.

---

## Архитектура

Проект демонстрирует работу метаобъектной системы Qt:

* `Calculator` — QObject с собственными сигналами `resultReady(double)`,
  `errorOccurred(QString)` и слотами `add`, `subtract`, `multiply`, `divide`,
  `lcm`, `reset`.
* `CsvParser` — второй QObject, независимый от `Calculator`, с сигналами
  `lineProcessed`, `finished`, `errorOccurred`. Демонстрирует принцип
  «один сигнал → много слотов» и разделение бизнес-логики между классами.
* `main.cpp` — консольный интерфейс: `QCoreApplication`, `QTextStream`,
  соединения через `QObject::connect(&obj, &Class::signal, ...)`.

---

## Структура проекта
ConsolCalc/
├── .gitignore
├── README.md
├── ConsolCalc.pro # сборка через qmake
├── CMakeLists.txt # сборка через CMake
├── calculator.h
├── calculator.cpp
├── csvparser.h
├── csvparser.cpp
├── main.cpp
├── data.csv # пример входного файла для команды csv
└── tests/
├── CMakeLists.txt
└── test_calculator.cpp # юнит-тесты через QTest + QSignalSpy


---
## Требования

* **Qt 6.x** (модули Core, Test)
* **Компилятор C++17** (GCC ≥ 9, Clang ≥ 10, MSVC ≥ 2019)
* **CMake ≥ 3.16** (для CMake-сборки)
* **qmake** (для qmake-сборки, идёт в комплекте с Qt)

### Установка зависимостей

**Ubuntu / Debian:**
```bash
sudo apt install qt6-base-dev qt6-base-dev-tools cmake g++ dpkg-dev
Сборка и запуск
Вариант 1: CMake (рекомендуется)

bash
cmake -S . -B build-cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build-cmake -j$(nproc)
./build-cmake/ConsolCalc
Вариант 2: qmake

bash
mkdir build && cd build
qmake ../ConsolCalc.pro
make -j$(nproc)

./ConsolCalc
Запуск в Qt Creator
Файл → Открыть файл или проект → CMakeLists.txt (или ConsolCalc.pro).

В Проекты → Настройки запуска включите галочку
«Запускать в терминале» (Run in terminal) — иначе консольный
ввод работать не будет.

Ctrl+R для запуска.

Тестирование
Юнит-тесты написаны с использованием фреймворка QTest и QSignalSpy.
Покрывают: арифметику, деление на ноль, сброс, lcm, проверку
излучения сигнала.

bash
cd build-cmake
ctest --output-on-failure
Ожидаемый результат:

text
Test project /path/to/ConsolCalc/build-cmake
    Start 1: CalculatorTests
1/1 Test #1: CalculatorTests ..............   Passed    0.05 sec

100% tests passed, 0 tests failed out of 1
Для подробного вывода каждого теста:

bash
ctest -V
или напрямую:

bash
./build-cmake/tests/test_calculator
Упаковка
С помощью CPack создаются готовые дистрибутивы:

bash
cd build-cmake
cpack -G TGZ     # архив tar.gz
cpack -G DEB     # .deb-пакет (требуется dpkg-dev)
На выходе получится файл вида ConsolCalc-1.0.0-Linux.tar.gz.

Пример работы
text
=== Консольный калькулятор на Qt ===
Доступные команды:
  add <a> <b> - сложение
  sub <a> <b> - вычитание
  mul <a> <b> - умножение
  div <a> <b> - деление
  lcm <a> <b> - НОК двух натуральных чисел
  csv <path>  - вычислить суммы и средние построчно
  reset       - сброс
  help        - эта справка
  quit        - выход

> add 5 3
Результат: 8
> div 10 0
Ошибка: Деление на ноль невозможно!
> lcm 12 18
Результат: 36
> csv data.csv
Строка 1: сумма = 6, среднее = 2
Строка 2: сумма = 60, среднее = 20
Строка 3: сумма = 10, среднее = 5

Итого: строк = 3, сумма = 76, среднее = 12.6667
> quit
До свидания!
Файл data.csv для примера:

text
1,2,3
10,20,30
5;5
Разделители — запятая или точка с запятой.
