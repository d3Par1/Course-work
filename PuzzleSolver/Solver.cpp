/**
 * @file Solver.cpp
 * @brief Реалізація класу Solver
 */

 #include "Solver.h"
 #include <iostream>
 #include <queue>
 #include <algorithm>
 #include <chrono>
 #include <set>
 #include <thread>
 
 Solver::Solver(Board& board) : board(board), isSolved(false) {
     // Конструктор ініціалізує посилання на дошку
 }
 
 bool Solver::solve() {
     // Отримання всіх символів на дошці
     const std::vector<Symbol>& symbols = board.getSymbols();
     
     // Перевірка, чи є символи на дошці
     if (symbols.empty()) {
         std::cout << "На дошці немає символів." << std::endl;
         return false;
     }
     
     // Починаємо вирішення з першого символу
     std::cout << "Починаємо вирішення головоломки..." << std::endl;
     bool result = solvePuzzle(0);
     
     if (result) {
         std::cout << "Головоломка успішно вирішена!" << std::endl;
         isSolved = true;
     } else {
         std::cout << "Не вдалося вирішити головоломку." << std::endl;
     }
     
     return result;
 }
 
 bool Solver::getIsSolved() const {
     return isSolved;
 }
 
 bool Solver::solvePuzzle(size_t symbolIndex) {
     // Отримання всіх символів на дошці
     const std::vector<Symbol>& symbols = board.getSymbols();
     
     // Перевірка, чи всі символи з'єднані
     if (board.areAllSymbolsConnected()) {
         return true;
     }
     
     // Перевірка, чи вийшли за межі вектора символів
     if (symbolIndex >= symbols.size()) {
         return false;
     }
     
     // Отримання поточного символу
     Symbol currentSymbol = symbols[symbolIndex];
     
     // Якщо символ вже з'єднаний, переходимо до наступного
     if (currentSymbol.getIsConnected()) {
         return solvePuzzle(symbolIndex + 1);
     }
     
     // Відображення проміжного стану
     displayIntermediateStep(symbolIndex, symbolIndex);
     
     // Знаходження парного символу
     int pairIndex = board.findPairForSymbol(currentSymbol);
     if (pairIndex == -1) {
         // Якщо пара не знайдена, переходимо до наступного символу
         return solvePuzzle(symbolIndex + 1);
     }
     
     Symbol pairSymbol = symbols[pairIndex];
     
     // Знаходження найкоротшого шляху між символами
     std::vector<std::pair<int, int>> shortestPath = findShortestPath(currentSymbol, pairSymbol);
     
     // Якщо шлях не знайдений, переходимо до наступного символу
     if (shortestPath.empty()) {
         return solvePuzzle(symbolIndex + 1);
     }
     
     // Створення лінії між символами
     Line line(currentSymbol, pairSymbol);
     line.setPath(shortestPath);
     line.setIsValid(true);
     
     // Перевірка, чи лінія перетинає область 2x2
     if (pathCrosses2x2Area(shortestPath)) {
         // Якщо перетинає, переходимо до наступного символу
         return solvePuzzle(symbolIndex + 1);
     }
     
     // Додавання лінії на дошку
     if (board.addLine(line)) {
         // Якщо лінія успішно додана, переходимо до наступного символу
         if (solvePuzzle(symbolIndex + 1)) {
             return true;
         }
         
         // Якщо не вдалося вирішити головоломку, видаляємо лінію
         board.removeLine(board.getLines().size() - 1);
     }
     
     // Пробуємо інші шляхи (не реалізовано в даному прикладі)
     
     return false;
 }
 
 std::vector<std::pair<int, int>> Solver::findShortestPath(const Symbol& start, const Symbol& end) {
     // Алгоритм пошуку найкоротшого шляху між двома символами
     // Використовуємо алгоритм пошуку в ширину (BFS)
     
     // Ініціалізація відвіданих клітин
     std::vector<std::vector<bool>> visited(board.getSize(), std::vector<bool>(board.getSize(), false));
     
     // Ініціалізація черги для BFS
     std::queue<std::pair<int, int>> queue;
     
     // Ініціалізація масиву для зберігання попередніх точок
     std::vector<std::vector<std::pair<int, int>>> parent(board.getSize(), 
         std::vector<std::pair<int, int>>(board.getSize(), std::make_pair(-1, -1)));
     
     // Додавання початкової точки в чергу
     queue.push(std::make_pair(start.getRow(), start.getCol()));
     visited[start.getRow()][start.getCol()] = true;
     
     // Масив напрямків (вгору, вправо, вниз, вліво)
     const int dx[] = {0, 1, 0, -1};
     const int dy[] = {-1, 0, 1, 0};
     
     // Поки черга не порожня
     while (!queue.empty()) {
         // Отримання поточної точки
         std::pair<int, int> current = queue.front();
         queue.pop();
         
         // Якщо досягли кінцевої точки
         if (current.first == end.getRow() && current.second == end.getCol()) {
             // Відновлення шляху
             std::vector<std::pair<int, int>> path;
             std::pair<int, int> backtrack = current;
             
             while (backtrack.first != -1 && backtrack.second != -1) {
                 path.push_back(backtrack);
                 backtrack = parent[backtrack.first][backtrack.second];
             }
             
             // Перевертаємо шлях, щоб він йшов від початку до кінця
             std::reverse(path.begin(), path.end());
             
             return path;
         }
         
         // Перевірка всіх сусідніх клітин
         for (int i = 0; i < 4; ++i) {
             int newRow = current.first + dy[i];
             int newCol = current.second + dx[i];
             
             // Перевірка на валідність координат
             if (newRow < 0 || newRow >= board.getSize() || newCol < 0 || newCol >= board.getSize()) {
                 continue;
             }
             
             // Перевірка, чи клітина не відвідана
             if (visited[newRow][newCol]) {
                 continue;
             }
             
             // Перевірка, чи можна провести лінію через клітину
             if (!board.canDrawLineThroughCell(newRow, newCol) && 
                 !(newRow == end.getRow() && newCol == end.getCol())) {
                 continue;
             }
             
             // Додавання клітини в чергу
             queue.push(std::make_pair(newRow, newCol));
             visited[newRow][newCol] = true;
             parent[newRow][newCol] = current;
         }
     }
     
     // Якщо шлях не знайдений, повертаємо порожній вектор
     return std::vector<std::pair<int, int>>();
 }
 
 bool Solver::pathCrosses2x2Area(const std::vector<std::pair<int, int>>& path) const {
     // Перевірка, чи шлях перетинає всі 4 клітини будь-якої області 2x2
     
     // Якщо шляху немає або він містить менше 4 точок, то не може перетинати 2x2
     if (path.size() < 4) {
         return false;
     }
     
     // Створення множини точок для швидкого пошуку
     std::set<std::pair<int, int>> pathSet(path.begin(), path.end());
     
     // Проходимо по всіх можливих початкових точках 2x2 областей
     for (int row = 0; row < board.getSize() - 1; ++row) {
         for (int col = 0; col < board.getSize() - 1; ++col) {
             // Перевіряємо, чи всі 4 клітини області 2x2 містяться у шляху
             bool topLeft = pathSet.find(std::make_pair(row, col)) != pathSet.end();
             bool topRight = pathSet.find(std::make_pair(row, col + 1)) != pathSet.end();
             bool bottomLeft = pathSet.find(std::make_pair(row + 1, col)) != pathSet.end();
             bool bottomRight = pathSet.find(std::make_pair(row + 1, col + 1)) != pathSet.end();
             
             if (topLeft && topRight && bottomLeft && bottomRight) {
                 return true;
             }
         }
     }
     
     return false;
 }
 
 void Solver::displayIntermediateStep(int step, size_t symbolIndex) const {
     // Відображення проміжного стану вирішення
     std::cout << "Крок " << step + 1 << ": Обробка символу " 
               << board.getSymbols()[symbolIndex].getValue() 
               << " на позиції (" << board.getSymbols()[symbolIndex].getRow()
               << ", " << board.getSymbols()[symbolIndex].getCol() << ")" << std::endl;
     
     // Пауза для кращого сприйняття
     std::this_thread::sleep_for(std::chrono::milliseconds(500));
     
     // Відображення дошки
     board.display();
     
     // Пауза для кращого сприйняття
     std::this_thread::sleep_for(std::chrono::milliseconds(500));
 }
 
 bool Solver::solveStep() {
     // Реалізація покрокового вирішення
     // В даному прикладі просто викликаємо повне вирішення
     return solve();
 }
 
 std::string Solver::getHint() const {
     // Отримання підказки для поточного стану
     
     // Отримання всіх символів на дошці
     const std::vector<Symbol>& symbols = board.getSymbols();
     
     // Пошук першого незв'язаного символу
     for (size_t i = 0; i < symbols.size(); ++i) {
         if (!symbols[i].getIsConnected()) {
             // Знаходження парного символу
             int pairIndex = board.findPairForSymbol(symbols[i]);
             if (pairIndex != -1) {
                 return "Спробуйте з'єднати символ " + std::string(1, symbols[i].getValue()) + 
                        " на позиції (" + std::to_string(symbols[i].getRow()) + 
                        ", " + std::to_string(symbols[i].getCol()) + ") з таким самим символом на позиції (" + 
                        std::to_string(symbols[pairIndex].getRow()) + 
                        ", " + std::to_string(symbols[pairIndex].getCol()) + ").";
             }
         }
     }
     
     return "Всі символи вже з'єднані.";
 }