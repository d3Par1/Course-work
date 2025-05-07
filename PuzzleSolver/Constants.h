/**
 * @file Constants.h
 * @brief Файл з константами для програми
 */

 #ifndef CONSTANTS_H
 #define CONSTANTS_H
 
 // Символи для відображення в консолі
 namespace ConsoleSymbols {
     const char EMPTY = ' ';              // Порожня клітина
     const char HORIZONTAL_LINE = '-';    // Горизонтальна лінія
     const char VERTICAL_LINE = '|';      // Вертикальна лінія
     const char INTERSECTION = '+';       // Перетин ліній
     const char CELL_BORDER_H = '-';      // Горизонтальна межа клітини
     const char CELL_BORDER_V = '|';      // Вертикальна межа клітини
     const char CELL_CORNER = '+';        // Кут межі клітини
 }
 
 // Максимальні розміри дошки
 namespace BoardDimensions {
  const int MIN_SIZE = 2;              // Мінімальний розмір дошки
  const int MAX_SIZE = 20;             // Максимальний розмір дошки
  const int DEFAULT_SIZE = 13;         // Змінено з 12 на 13
}
 
 // Коди кнопок для меню
 namespace MenuOptions {
     const int INPUT_MANUALLY = 1;        // Опція "Ввести вручну"
     const int USE_DEFAULT = 2;           // Опція "Використати вбудоване"
     const int EXIT = 3;                  // Опція "Вихід"
     const int SOLVE_MANUALLY = 1;        // Опція "Вирішити самостійно"
     const int SOLVE_AUTOMATICALLY = 2;   // Опція "Вирішити програмно"
     const int BACK_TO_MENU = 3;          // Опція "Повернутись до меню"
 }
 
 // Стани клітини
 namespace CellState {
     const int EMPTY = 0;                 // Порожня клітина
     const int OCCUPIED = 1;              // Клітина, зайнята лінією
     const int ENDPOINT = 2;              // Клітина з символом (початок/кінець лінії)
 }
 
 // Напрямки руху
 namespace Direction {
     const int UP = 0;                    // Вгору
     const int RIGHT = 1;                 // Вправо
     const int DOWN = 2;                  // Вниз
     const int LEFT = 3;                  // Вліво
     
     // Зміни координат для кожного напрямку
     const int DX[4] = {0, 1, 0, -1};     // Зміна x для кожного напрямку
     const int DY[4] = {-1, 0, 1, 0};     // Зміна y для кожного напрямку
 }
 
 #endif // CONSTANTS_H