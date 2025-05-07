// PuzzleSolver.h
#ifndef PUZZLE_SOLVER_H
#define PUZZLE_SOLVER_H

#include <vector>
#include <map>
#include <string>
#include "Point.h"
#include "Path.h"

class PuzzleSolver {
private:
    int rows, cols;                      // Розміри сітки
    std::vector<std::vector<char>> grid; // Сітка з символами
    std::vector<std::vector<bool>> used; // Матриця використаних клітин
    std::map<char, std::vector<Point>> symbolPositions; // Позиції символів
    std::vector<Path> paths;             // Знайдені шляхи
    
    // Приватні методи
    bool isValidPoint(int x, int y);     // Перевірка чи точка в межах сітки
    bool violates2x2Rule(const std::vector<Point>& path); // Перевірка правила 2x2
    std::vector<Point> findPath(Point start, Point end); // Пошук шляху між точками
    
public:
    // Конструктор
    PuzzleSolver(int _rows, int _cols);
    
    // Публічні методи
    void setSymbol(int x, int y, char symbol); // Встановлення символу
    bool solve();                        // Розв'язання головоломки
    void displayResult();                // Відображення результату
    
    // Геттери
    std::vector<Path> getPaths() const { return paths; }
    std::vector<std::vector<char>> getGrid() const { return grid; }
};
#endif