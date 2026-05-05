# Logistics Optimizer (ЭКЗ ОИПМ)

Проект демонстрирует интеграцию детерминированной оптимизации (транспортная задача) и стохастического моделирования (Монте-Карло) для оценки логистических маршрутов.

## Стек
- C++17
- CMake 3.14+
- Google Test
- Git, clang-tidy, gcov

## Сборка и запуск
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
./LogisticsOptimizer ../data/balanced.csv
