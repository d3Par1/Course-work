/**
 * @file Game.h
 * @brief Основний клас гри
 */

 #ifndef GAME_H
 #define GAME_H
 
 #include "Board.h"
 #include "Solver.h"
 #include "UserInterface.h"
 
 /**
  * @class Game
  * @brief Основний клас гри, який керує всім процесом гри
  * 
  * Клас Game відповідає за керування грою, зокрема за ініціалізацію,
  * обробку введення користувача, відображення меню та завершення гри.
  */
 class Game {
 private:
     Board board;                  // Ігрова дошка
     Solver solver;                // Автоматичний вирішувач головоломки
     UserInterface ui;             // Інтерфейс користувача
     bool isRunning;               // Чи працює гра
     
     /**
      * @brief Обробити вибір з головного меню
      * @param choice Вибір користувача
      */
     void processMainMenuChoice(int choice);
     
     /**
      * @brief Обробити вибір з меню вирішення головоломки
      * @param choice Вибір користувача
      */
     void processSolutionMenuChoice(int choice);
     
     /**
      * @brief Ввести головоломку вручну
      */
     void inputPuzzleManually();
     
     /**
      * @brief Завантажити вбудовану головоломку
      */
     void loadDefaultPuzzle();
     
     /**
      * @brief Вирішити головоломку вручну
      */
     void solvePuzzleManually();
     
     /**
      * @brief Вирішити головоломку програмно
      */
     void solvePuzzleProgrammatically();
     
     /**
      * @brief Вийти з гри
      */
     void exitGame();
 
 public:
     /**
      * @brief Конструктор за замовчуванням
      */
     Game();
     
     /**
      * @brief Деструктор
      */
     ~Game();
     
     /**
      * @brief Запустити гру
      */
     void run();
 };
 
 #endif // GAME_H