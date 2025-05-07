/**
 * @file Solver.h
 * @brief Клас для автоматичного вирішення головоломки
 */

 #ifndef SOLVER_H
 #define SOLVER_H
 
 #include "Board.h"
 #include <vector>
 #include <utility>
 
 /**
  * @class Solver
  * @brief Клас для автоматичного вирішення головоломки зі з'єднання пар
  * 
  * Клас Solver реалізує алгоритм автоматичного вирішення головоломки
  * за допомогою алгоритму пошуку з поверненням (backtracking) та евристик.
  */
 class Solver {
 private:
     Board& board;                             // Посилання на дошку
     std::vector<std::pair<int, int>> path;    // Поточний шлях
     bool isSolved;                            // Чи вирішена головоломка
     
     /**
      * @brief Знайти найкоротший шлях між двома символами
      * @param start Початковий символ
      * @param end Кінцевий символ
      * @return Шлях між символами або пустий вектор, якщо шлях не знайдено
      */
     std::vector<std::pair<int, int>> findShortestPath(const Symbol& start, const Symbol& end);
     
     /**
      * @brief Рекурсивний алгоритм пошуку з поверненням
      * @param currentRow Поточний рядок
      * @param currentCol Поточний стовпець
      * @param endRow Кінцевий рядок
      * @param endCol Кінцевий стовпець
      * @param visited Відвідані клітини
      * @param maxDepth Максимальна глибина пошуку
      * @return true, якщо шлях знайдено
      */
     bool backtrack(int currentRow, int currentCol, int endRow, int endCol,
                    std::vector<std::vector<bool>>& visited, int maxDepth);
     
     /**
      * @brief Рекурсивний алгоритм вирішення головоломки
      * @param symbolIndex Індекс поточного символу
      * @return true, якщо головоломка вирішена
      */
     bool solvePuzzle(size_t symbolIndex);
     
     /**
      * @brief Перевірити, чи шлях перетинає область 2x2
      * @param path Шлях
      * @return true, якщо шлях перетинає область 2x2
      */
     bool pathCrosses2x2Area(const std::vector<std::pair<int, int>>& path) const;
     
     /**
      * @brief Відображення проміжного стану вирішення
      * @param step Крок вирішення
      * @param symbolIndex Індекс поточного символу
      */
     void displayIntermediateStep(int step, size_t symbolIndex) const;
 
 public:
     /**
      * @brief Конструктор
      * @param board Посилання на дошку
      */
     Solver(Board& board);
     
     /**
      * @brief Вирішити головоломку
      * @return true, якщо головоломка вирішена
      */
     bool solve();
     
     /**
      * @brief Перевірити, чи головоломка вирішена
      * @return true, якщо головоломка вирішена
      */
     bool getIsSolved() const;
     
     /**
      * @brief Вирішити один крок головоломки (для покрокового вирішення)
      * @return true, якщо крок виконаний успішно
      */
     bool solveStep();
     
     /**
      * @brief Отримати підказку для поточного стану
      * @return Повідомлення з підказкою
      */
     std::string getHint() const;
 };
 
 #endif // SOLVER_H