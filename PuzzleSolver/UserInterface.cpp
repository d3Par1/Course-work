/**
 * @file UserInterface.cpp
 * @brief Реалізація класу UserInterface
 */

 #include "UserInterface.h"
 #include <iostream>
 #include <limits>
 #include <cstdlib>
 
 UserInterface::UserInterface() {
     // Конструктор встановлює локаль для підтримки Unicode
     std::setlocale(LC_ALL, "");
 }
 
 UserInterface::~UserInterface() {
     // Деструктор (порожній)
 }
 
 void UserInterface::clearScreen() const {
     // Очищення екрану консолі
     #ifdef _WIN32
         system("cls");
     #else
         system("clear");
     #endif
 }
 
 void UserInterface::displayLogo() const {
     // Відображення логотипу програми
     std::cout << "===========================================" << std::endl;
     std::cout << "          ГОЛОВОЛОМКА З'ЄДНАННЯ ПАР       " << std::endl;
     std::cout << "===========================================" << std::endl;
     std::cout << std::endl;
 }
 
 void UserInterface::displayInfo() const {
     // Відображення інформації про програму
     std::cout << "Програма для вирішення головоломки зі з'єднання пар." << std::endl;
     std::cout << "Правила:" << std::endl;
     std::cout << "1. З'єднайте пари однакових символів (літер або цифр)." << std::endl;
     std::cout << "2. У кожну клітину може входити лише одна лінія." << std::endl;
     std::cout << "3. Лінії можуть йти лише по горизонталі або вертикалі." << std::endl;
     std::cout << "4. Один відрізок не може проходити через усі 4 клітини" << std::endl;
     std::cout << "   в будь-якій області 2×2." << std::endl;
     std::cout << std::endl;
 }
 
 void UserInterface::displayMainMenu() const {
     // Відображення головного меню
     clearScreen();
     displayLogo();
     displayInfo();
     
     std::cout << "ГОЛОВНЕ МЕНЮ:" << std::endl;
     std::cout << "1. Ввести головоломку вручну" << std::endl;
     std::cout << "2. Використати вбудовану головоломку" << std::endl;
     std::cout << "3. Вийти з програми" << std::endl;
     std::cout << std::endl;
     std::cout << "Виберіть опцію (1-3): ";
 }
 
 void UserInterface::displaySolutionMenu() const {
     // Відображення меню вирішення головоломки
     std::cout << std::endl;
     std::cout << "МЕНЮ ВИРІШЕННЯ:" << std::endl;
     std::cout << "1. Вирішити головоломку самостійно" << std::endl;
     std::cout << "2. Вирішити головоломку програмно" << std::endl;
     std::cout << "3. Повернутися до головного меню" << std::endl;
     std::cout << std::endl;
     std::cout << "Виберіть опцію (1-3): ";
 }
 
 void UserInterface::displayManualSolutionMenu() const {
     // Відображення меню ручного вирішення
     std::cout << std::endl;
     std::cout << "РУЧНЕ ВИРІШЕННЯ:" << std::endl;
     std::cout << "1. З'єднати два символи" << std::endl;
     std::cout << "2. Видалити з'єднання" << std::endl;
     std::cout << "3. Отримати підказку" << std::endl;
     std::cout << "4. Повернутися до головного меню" << std::endl;
     std::cout << std::endl;
     std::cout << "Виберіть опцію (1-4): ";
 }
 
 int UserInterface::getMenuChoice(int min, int max) const {
     // Отримання вибору користувача з меню
     int choice;
     
     while (true) {
         if (std::cin >> choice) {
             // Перевірка на валідність вибору
             if (choice >= min && choice <= max) {
                 return choice;
             } else {
                 std::cout << "Неправильний вибір. Виберіть від " << min << " до " << max << ": ";
             }
         } else {
             // Очищення буфера введення при помилці
             std::cin.clear();
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             std::cout << "Неправильне введення. Введіть число: ";
         }
     }
 }
 
 int UserInterface::getBoardSize() const {
     // Отримання розміру дошки від користувача
     int size;
     
     std::cout << "Введіть розмір дошки (від " << BoardDimensions::MIN_SIZE 
               << " до " << BoardDimensions::MAX_SIZE << "): ";
     
     while (true) {
         if (std::cin >> size) {
             // Перевірка на валідність розміру
             if (size >= BoardDimensions::MIN_SIZE && size <= BoardDimensions::MAX_SIZE) {
                 return size;
             } else {
                 std::cout << "Неправильний розмір. Введіть від " << BoardDimensions::MIN_SIZE 
                           << " до " << BoardDimensions::MAX_SIZE << ": ";
             }
         } else {
             // Очищення буфера введення при помилці
             std::cin.clear();
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             std::cout << "Неправильне введення. Введіть число: ";
         }
     }
 }
 
 char UserInterface::getSymbol() const {
     // Отримання символу від користувача
     char symbol;
     
     std::cout << "Введіть символ (літеру або цифру): ";
     
     while (true) {
         if (std::cin >> symbol) {
             // Перевірка на валідність символу
             if (std::isalnum(symbol)) {
                 return symbol;
             } else {
                 std::cout << "Неправильний символ. Введіть літеру або цифру: ";
             }
         } else {
             // Очищення буфера введення при помилці
             std::cin.clear();
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             std::cout << "Неправильне введення. Введіть літеру або цифру: ";
         }
     }
 }
 
 std::pair<int, int> UserInterface::getCoordinates(const Board& board, const std::string& message) const {
     // Отримання координат від користувача
     int row, col;
     
     std::cout << message << " (рядок стовпець): ";
     
     while (true) {
         if (std::cin >> row >> col) {
             // Перевірка на валідність координат
             if (row >= 0 && row < board.getSize() && col >= 0 && col < board.getSize()) {
                 return std::make_pair(row, col);
             } else {
                 std::cout << "Неправильні координати. Введіть від 0 до " << (board.getSize() - 1) << ": ";
             }
         } else {
             // Очищення буфера введення при помилці
             std::cin.clear();
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             std::cout << "Неправильне введення. Введіть два числа: ";
         }
     }
 }
 
 void UserInterface::inputBoard(Board& board) const {
     // Введення дошки вручну
     clearScreen();
     displayLogo();
     
     // Отримання розміру дошки
     int size = getBoardSize();
     
     // Створення нової дошки
     board = Board(size);
     
     std::cout << "Введення символів на дошці." << std::endl;
     std::cout << "Введіть 0 для завершення введення." << std::endl;
     
     while (true) {
         // Відображення поточного стану дошки
         board.display();
         
         // Отримання символу
         char symbol = getSymbol();
         
         // Перевірка на завершення введення
         if (symbol == '0') {
             break;
         }
         
         // Отримання координат
         std::pair<int, int> coords = getCoordinates(board, "Введіть координати для символу " + std::string(1, symbol));
         
         // Встановлення символу на дошці
         board.setSymbol(coords.first, coords.second, symbol);
         
         clearScreen();
         displayLogo();
         std::cout << "Символ " << symbol << " встановлено на позицію (" 
                   << coords.first << ", " << coords.second << ")." << std::endl;
     }
     
     clearScreen();
     displayLogo();
     std::cout << "Введення дошки завершено." << std::endl;
     board.display();
 }
 
 void UserInterface::displayMessage(const std::string& message) const {
     // Відображення повідомлення для користувача
     std::cout << message << std::endl;
 }
 
 void UserInterface::displayError(const std::string& message) const {
     // Відображення повідомлення про помилку
     std::cout << "ПОМИЛКА: " << message << std::endl;
 }
 
 void UserInterface::displayCongratulations() const {
     // Відображення вітання з вирішенням головоломки
     clearScreen();
     displayLogo();
     
     std::cout << "ВІТАЄМО!" << std::endl;
     std::cout << "Ви успішно вирішили головоломку!" << std::endl;
     std::cout << std::endl;
 }
 
 void UserInterface::waitForKeyPress() const {
     // Очікування натискання клавіші для продовження
     std::cout << "Натисніть Enter для продовження...";
     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
     std::cin.get();
 }
 
 bool UserInterface::solveManually(Board& board) const {
     // Вирішення головоломки вручну
     while (true) {
         // Відображення дошки
         clearScreen();
         displayLogo();
         board.display();
         
         // Перевірка, чи всі символи з'єднані
         if (board.areAllSymbolsConnected()) {
             displayCongratulations();
             waitForKeyPress();
             return true;
         }
         
         // Відображення меню ручного вирішення
         displayManualSolutionMenu();
         
         // Отримання вибору користувача
         int choice = getMenuChoice(1, 4);
         
         switch (choice) {
             case 1: {
                 // З'єднання двох символів
                 std::pair<int, int> start = getCoordinates(board, "Введіть координати першого символу");
                 std::pair<int, int> end = getCoordinates(board, "Введіть координати другого символу");
                 
                 // Перевірка, чи клітини містять символи
                 if (!board.getCell(start.first, start.second).hasSymbol() || 
                     !board.getCell(end.first, end.second).hasSymbol()) {
                     displayError("Обрані клітини не містять символів.");
                     waitForKeyPress();
                     continue;
                 }
                 
                 // Перевірка, чи символи однакові
                 char startSymbol = board.getCell(start.first, start.second).getContent();
                 char endSymbol = board.getCell(end.first, end.second).getContent();
                 
                 if (startSymbol != endSymbol) {
                     displayError("Обрані символи різні.");
                     waitForKeyPress();
                     continue;
                 }
                 
                 // Створення і додавання лінії між символами
                 Symbol symbolStart(startSymbol, start.first, start.second);
                 Symbol symbolEnd(endSymbol, end.first, end.second);
                 
                 Line line(symbolStart, symbolEnd);
                 
                 // TODO: Реалізувати ручне проведення лінії
                 
                 displayError("Функція ручного проведення лінії ще не реалізована.");
                 waitForKeyPress();
                 break;
             }
             
             case 2: {
                 // Видалення з'єднання
                 std::pair<int, int> coords = getCoordinates(board, "Введіть координати символу, з'єднання якого потрібно видалити");
                 
                 // TODO: Реалізувати видалення з'єднання
                 
                 displayError("Функція видалення з'єднання ще не реалізована.");
                 waitForKeyPress();
                 break;
             }
             
             case 3: {
                 // Отримання підказки
                 // TODO: Реалізувати отримання підказки
                 
                 displayMessage("Підказка: спробуйте з'єднати символи, які мають найменше можливих шляхів.");
                 waitForKeyPress();
                 break;
             }
             
             case 4: {
                 // Повернення до головного меню
                 return false;
             }
         }
     }
     
     return false;
 }