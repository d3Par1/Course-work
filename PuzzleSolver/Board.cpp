/**
 * @file Board.cpp
 * @brief Реалізація класу Board
 */

 #include "Board.h"
 #include <iostream>
 #include <fstream>
 #include <algorithm>
 #include <iomanip>
 
 Board::Board() : size(BoardDimensions::DEFAULT_SIZE) {
     // Конструктор за замовчуванням створює дошку стандартного розміру
     initializeEmptyBoard();
 }
 
 Board::Board(int size) {
     // Конструктор з параметром створює дошку заданого розміру
     if (size < BoardDimensions::MIN_SIZE) {
         size = BoardDimensions::MIN_SIZE;
     } else if (size > BoardDimensions::MAX_SIZE) {
         size = BoardDimensions::MAX_SIZE;
     }
     
     this->size = size;
     initializeEmptyBoard();
 }
 
 void Board::initializeEmptyBoard() {
     // Ініціалізація порожньої дошки з клітинами
     cells.resize(size, std::vector<Cell>(size));
     
     // Ініціалізація кожної клітини як порожньої
     for (int i = 0; i < size; ++i) {
         for (int j = 0; j < size; ++j) {
             cells[i][j] = Cell();
         }
     }
 }
 
 int Board::getSize() const {
     return size;
 }
 
 Cell& Board::getCell(int row, int col) {
     // Перевірка на валідність координат
     if (row < 0 || row >= size || col < 0 || col >= size) {
         // Якщо координати невалідні, повертаємо першу клітину
         return cells[0][0];
     }
     
     return cells[row][col];
 }
 
 const Cell& Board::getCell(int row, int col) const {
     // Перевірка на валідність координат
     if (row < 0 || row >= size || col < 0 || col >= size) {
         // Якщо координати невалідні, повертаємо першу клітину
         return cells[0][0];
     }
     
     return cells[row][col];
 }
 
 const std::vector<Symbol>& Board::getSymbols() const {
     return symbols;
 }
 
 const std::vector<Line>& Board::getLines() const {
     return lines;
 }
 
 void Board::setSymbol(int row, int col, char symbol) {
     // Перевірка на валідність координат
     if (row < 0 || row >= size || col < 0 || col >= size) {
         return;
     }
     
     // Встановлення символу в клітині
     cells[row][col].setContent(symbol);
     cells[row][col].setState(CellState::ENDPOINT);
     
     // Додавання символу до вектора символів
     symbols.push_back(Symbol(symbol, row, col));
     
     // Оновлення пар символів
     findSymbolPairs();
 }
 
 void Board::findSymbolPairs() {
     // Мапа для групування символів за значенням
     std::map<char, std::vector<Symbol>> symbolGroups;
     
     // Групування символів за значенням
     for (const Symbol& symbol : symbols) {
         symbolGroups[symbol.getValue()].push_back(symbol);
     }
     
     // Очищення вектора символів
     symbols.clear();
     
     // Додавання символів у новому порядку (групами)
     for (const auto& group : symbolGroups) {
         for (const Symbol& symbol : group.second) {
             symbols.push_back(symbol);
         }
     }
 }
 
 bool Board::addLine(const Line& line) {
     // Перевірка на валідність лінії
     if (!line.getIsValid()) {
         return false;
     }
     
     // Перевірка, чи клітини доступні
     if (!areCellsAvailable(line.getPath())) {
         return false;
     }
     
     // Перевірка, чи лінія перетинає область 2x2
     if (line.crosses2x2Area()) {
         return false;
     }
     
     // Додавання лінії
     lines.push_back(line);
     
     // Оновлення стану клітин
     for (const auto& point : line.getPath()) {
         int row = point.first;
         int col = point.second;
         
         // Пропускаємо початкову та кінцеву точки
         if ((row == line.getStart().getRow() && col == line.getStart().getCol()) ||
             (row == line.getEnd().getRow() && col == line.getEnd().getCol())) {
             continue;
         }
         
         // Встановлення стану клітини як зайнятої лінією
         cells[row][col].setState(CellState::OCCUPIED);
         
         // Визначення символу для відображення лінії (горизонтальна або вертикальна)
         if (row == point.first && col == point.second) {
             // Горизонтальна лінія
             cells[row][col].setContent(ConsoleSymbols::HORIZONTAL_LINE);
         } else {
             // Вертикальна лінія
             cells[row][col].setContent(ConsoleSymbols::VERTICAL_LINE);
         }
     }
     
     // Оновлення стану символів
     for (Symbol& symbol : symbols) {
         if ((symbol.getRow() == line.getStart().getRow() && symbol.getCol() == line.getStart().getCol()) ||
             (symbol.getRow() == line.getEnd().getRow() && symbol.getCol() == line.getEnd().getCol())) {
             symbol.setIsConnected(true);
         }
     }
     
     return true;
 }
 
 void Board::removeLine(size_t index) {
     // Перевірка на валідність індексу
     if (index >= lines.size()) {
         return;
     }
     
     // Отримання лінії для видалення
     Line line = lines[index];
     
     // Оновлення стану клітин
     for (const auto& point : line.getPath()) {
         int row = point.first;
         int col = point.second;
         
         // Пропускаємо початкову та кінцеву точки
         if ((row == line.getStart().getRow() && col == line.getStart().getCol()) ||
             (row == line.getEnd().getRow() && col == line.getEnd().getCol())) {
             continue;
         }
         
         // Встановлення стану клітини як порожньої
         cells[row][col].clear();
     }
     
     // Оновлення стану символів
     for (Symbol& symbol : symbols) {
         if ((symbol.getRow() == line.getStart().getRow() && symbol.getCol() == line.getStart().getCol()) ||
             (symbol.getRow() == line.getEnd().getRow() && symbol.getCol() == line.getEnd().getCol())) {
             symbol.setIsConnected(false);
         }
     }
     
     // Видалення лінії
     lines.erase(lines.begin() + index);
 }
 
 bool Board::canDrawLineThroughCell(int row, int col) const {
     // Перевірка на валідність координат
     if (row < 0 || row >= size || col < 0 || col >= size) {
         return false;
     }
     
     // Перевірка, чи клітина вільна
     return cells[row][col].isEmpty();
 }
 
 bool Board::areCellsAvailable(const std::vector<std::pair<int, int>>& path) const {
     // Перевірка, чи всі клітини доступні для проведення лінії
     for (const auto& point : path) {
         int row = point.first;
         int col = point.second;
         
         // Перевірка на валідність координат
         if (row < 0 || row >= size || col < 0 || col >= size) {
             return false;
         }
         
         // Клітини з символами завжди доступні
         if (cells[row][col].hasSymbol()) {
             continue;
         }
         
         // Перевірка, чи клітина вільна
         if (!cells[row][col].isEmpty()) {
             return false;
         }
     }
     
     return true;
 }
 
 int Board::findPairForSymbol(const Symbol& symbol) const {
     // Пошук парного символу
     for (size_t i = 0; i < symbols.size(); ++i) {
         if (symbols[i].getValue() == symbol.getValue() && 
             (symbols[i].getRow() != symbol.getRow() || symbols[i].getCol() != symbol.getCol())) {
             return i;
         }
     }
     
     return -1;
 }
 
 bool Board::areAllSymbolsConnected() const {
     // Перевірка, чи всі символи з'єднані
     for (const Symbol& symbol : symbols) {
         if (!symbol.getIsConnected()) {
             return false;
         }
     }
     
     return true;
 }
 
 bool Board::loadFromFile(const std::string& filename) {
     // Завантаження дошки з файлу
     std::ifstream file(filename);
     if (!file.is_open()) {
         return false;
     }
     
     // Очищення дошки
     clear();
     
     // Читання розміру дошки
     file >> size;
     if (size < BoardDimensions::MIN_SIZE || size > BoardDimensions::MAX_SIZE) {
         return false;
     }
     
     // Ініціалізація порожньої дошки
     initializeEmptyBoard();
     
     // Читання символів
     int numSymbols;
     file >> numSymbols;
     
     for (int i = 0; i < numSymbols; ++i) {
         char symbol;
         int row, col;
         file >> symbol >> row >> col;
         
         setSymbol(row, col, symbol);
     }
     
     file.close();
     return true;
 }
 
 bool Board::loadDefaultBoard() {
  // Завантаження стандартної дошки
  clear();
  size = 13; // розмір дошки з прикладу (змінено з 12 на 13)
  initializeEmptyBoard();
  
  // Розміщення символів з прикладу
  setSymbol(0, 10, 'S');
  setSymbol(1, 8, 'S');
  setSymbol(2, 10, 'R');
  setSymbol(3, 3, 'C');
  setSymbol(3, 9, 'L');
  setSymbol(4, 4, 'O');
  setSymbol(4, 11, 'N');
  setSymbol(5, 5, 'L');
  setSymbol(5, 10, 'C');
  setSymbol(6, 1, 'G');
  setSymbol(6, 7, 'G');
  setSymbol(7, 0, 'Z');
  setSymbol(7, 3, 'E');
  setSymbol(7, 7, 'N');
  setSymbol(8, 9, 'E');
  setSymbol(8, 10, 'T');
  setSymbol(9, 3, 'T');
  setSymbol(9, 5, 'R');
  setSymbol(10, 6, 'Z');
  setSymbol(10, 11, 'M');
  setSymbol(11, 6, 'M');
  
  return true;
}
 
 void Board::clear() {
     // Очищення дошки
     cells.clear();
     symbols.clear();
     lines.clear();
     
     // Ініціалізація порожньої дошки
     initializeEmptyBoard();
 }
 
 void Board::display() const {
     // Відображення дошки в консолі
     
     // Відображення верхньої межі дошки
     std::cout << "   ";
     for (int j = 0; j < size; ++j) {
         std::cout << std::setw(2) << j << ' ';
     }
     std::cout << std::endl;
     
     std::cout << "  +";
     for (int j = 0; j < size; ++j) {
         std::cout << "---";
     }
     std::cout << "+\n";
     
     // Відображення клітин
     for (int i = 0; i < size; ++i) {
         std::cout << std::setw(2) << i << '|';
         
         for (int j = 0; j < size; ++j) {
             std::cout << ' ' << cells[i][j].getDisplayChar() << ' ';
         }
         
         std::cout << "|\n";
     }
     
     // Відображення нижньої межі дошки
     std::cout << "  +";
     for (int j = 0; j < size; ++j) {
         std::cout << "---";
     }
     std::cout << "+\n";
 }