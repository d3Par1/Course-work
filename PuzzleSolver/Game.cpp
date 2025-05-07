/**
 * @file Game.cpp
 * @brief Реалізація класу Game
 */

 #include "Game.h"
 #include <iostream>
 
 Game::Game() : solver(board), isRunning(true) {
     // Конструктор ініціалізує об'єкти та встановлює початковий стан гри
 }
 
 Game::~Game() {
     // Деструктор (порожній)
 }
 
 void Game::run() {
     // Головний цикл гри
     while (isRunning) {
         // Відображення головного меню
         ui.displayMainMenu();
         
         // Отримання вибору користувача
         int choice = ui.getMenuChoice(1, 3);
         
         // Обробка вибору
         processMainMenuChoice(choice);
     }
     
     std::cout << "Дякуємо за використання програми!" << std::endl;
 }
 
 void Game::processMainMenuChoice(int choice) {
     // Обробка вибору з головного меню
     switch (choice) {
         case MenuOptions::INPUT_MANUALLY:
             // Ввести головоломку вручну
             inputPuzzleManually();
             break;
         
         case MenuOptions::USE_DEFAULT:
             // Завантажити вбудовану головоломку
             loadDefaultPuzzle();
             break;
         
         case MenuOptions::EXIT:
             // Вийти з гри
             exitGame();
             break;
     }
 }
 
 void Game::processSolutionMenuChoice(int choice) {
     // Обробка вибору з меню вирішення головоломки
     switch (choice) {
         case MenuOptions::SOLVE_MANUALLY:
             // Вирішити головоломку вручну
             solvePuzzleManually();
             break;
         
         case MenuOptions::SOLVE_AUTOMATICALLY:
             // Вирішити головоломку програмно
             solvePuzzleProgrammatically();
             break;
         
         case MenuOptions::BACK_TO_MENU:
             // Повернутися до головного меню
             // Нічого не робимо, просто виходимо з функції
             break;
     }
 }
 
 void Game::inputPuzzleManually() {
     // Ввести головоломку вручну
     ui.inputBoard(board);
     
     // Відображення меню вирішення головоломки
     ui.displaySolutionMenu();
     
     // Отримання вибору користувача
     int choice = ui.getMenuChoice(1, 3);
     
     // Обробка вибору
     processSolutionMenuChoice(choice);
 }
 
 void Game::loadDefaultPuzzle() {
     // Завантажити вбудовану головоломку
     if (board.loadDefaultBoard()) {
         ui.displayMessage("Вбудована головоломка успішно завантажена.");
         board.display();
         ui.waitForKeyPress();
         
         // Відображення меню вирішення головоломки
         ui.displaySolutionMenu();
         
         // Отримання вибору користувача
         int choice = ui.getMenuChoice(1, 3);
         
         // Обробка вибору
         processSolutionMenuChoice(choice);
     } else {
         ui.displayError("Помилка завантаження вбудованої головоломки.");
         ui.waitForKeyPress();
     }
 }
 
 void Game::solvePuzzleManually() {
     // Вирішити головоломку вручну
     ui.solveManually(board);
 }
 
 void Game::solvePuzzleProgrammatically() {
     // Вирішити головоломку програмно
     ui.displayMessage("Автоматичне вирішення головоломки...");
     
     // Вирішення головоломки
     bool solved = solver.solve();
     
     if (solved) {
         // Відображення вітання
         ui.displayCongratulations();
     } else {
         // Відображення повідомлення про помилку
         ui.displayError("Не вдалося автоматично вирішити головоломку.");
     }
     
     ui.waitForKeyPress();
 }
 
 void Game::exitGame() {
     // Вийти з гри
     isRunning = false;
 }