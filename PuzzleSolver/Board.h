/**
 * @file Board.h
 * @brief Клас для представлення ігрової дошки
 */

 #ifndef BOARD_H
 #define BOARD_H
 
 #include <vector>
 #include <map>
 #include "Cell.h"
 #include "Symbol.h"
 #include "Line.h"
 
 /**
  * @class Board
  * @brief Клас для представлення ігрової дошки головоломки
  * 
  * Клас Board представляє ігрову дошку головоломки зі з'єднання пар.
  * Він зберігає стан клітин, символи та лінії між ними.
  */
 class Board {
 private:
     int size;                               // Розмір дошки (квадратної)
     std::vector<std::vector<Cell>> cells;   // Двовимірний масив клітин
     std::vector<Symbol> symbols;            // Вектор символів на дошці
     std::vector<Line> lines;                // Вектор ліній між символами
     
     /**
      * @brief Ініціалізувати порожню дошку
      */
     void initializeEmptyBoard();
     
     /**
      * @brief Знайти всі пари однакових символів
      */
     void findSymbolPairs();
 
 public:
     /**
      * @brief Конструктор за замовчуванням
      */
     Board();
     
     /**
      * @brief Конструктор з параметром
      * @param size Розмір дошки
      */
     Board(int size);
     
     /**
      * @brief Отримати розмір дошки
      * @return Розмір дошки
      */
     int getSize() const;
     
     /**
      * @brief Отримати клітину за координатами
      * @param row Рядок
      * @param col Стовпець
      * @return Посилання на клітину
      */
     Cell& getCell(int row, int col);
     
     /**
      * @brief Отримати клітину за координатами (const версія)
      * @param row Рядок
      * @param col Стовпець
      * @return Константне посилання на клітину
      */
     const Cell& getCell(int row, int col) const;
     
     /**
      * @brief Отримати вектор символів
      * @return Вектор символів
      */
     const std::vector<Symbol>& getSymbols() const;
     
     /**
      * @brief Отримати вектор ліній
      * @return Вектор ліній
      */
     const std::vector<Line>& getLines() const;
     
     /**
      * @brief Встановити символ у клітині
      * @param row Рядок
      * @param col Стовпець
      * @param symbol Символ
      */
     void setSymbol(int row, int col, char symbol);
     
     /**
      * @brief Додати лінію між символами
      * @param line Лінія
      * @return true, якщо лінія була успішно додана
      */
     bool addLine(const Line& line);
     
     /**
      * @brief Видалити лінію
      * @param index Індекс лінії
      */
     void removeLine(size_t index);
     
     /**
      * @brief Перевірити, чи можна провести лінію через клітину
      * @param row Рядок
      * @param col Стовпець
      * @return true, якщо лінію можна провести
      */
     bool canDrawLineThroughCell(int row, int col) const;
     
     /**
      * @brief Перевірити, чи клітини не перетинаються з іншими лініями
      * @param path Шлях лінії
      * @return true, якщо клітини не перетинаються
      */
     bool areCellsAvailable(const std::vector<std::pair<int, int>>& path) const;
     
     /**
      * @brief Знайти пару для символу
      * @param symbol Символ
      * @return Індекс парного символу або -1, якщо пари немає
      */
     int findPairForSymbol(const Symbol& symbol) const;
     
     /**
      * @brief Перевірити, чи всі символи з'єднані
      * @return true, якщо всі символи з'єднані
      */
     bool areAllSymbolsConnected() const;
     
     /**
      * @brief Завантажити дошку з файлу
      * @param filename Назва файлу
      * @return true, якщо завантаження успішне
      */
     bool loadFromFile(const std::string& filename);
     
     /**
      * @brief Завантажити стандартну дошку
      * @return true, якщо завантаження успішне
      */
     bool loadDefaultBoard();
     
     /**
      * @brief Очистити дошку
      */
     void clear();
     
     /**
      * @brief Відобразити дошку в консолі
      */
     void display() const;
 };
 
 #endif // BOARD_H